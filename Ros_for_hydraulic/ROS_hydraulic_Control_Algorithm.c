/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Control_Algorithm.c
**
** 				 		      ZJU - 2015
**
** 系统介绍：XXXXXXXXXXXXXXXXXXXXXX
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_Control_Algorithm.c
** 模 块 名：XXXXXXXXXXXXXXXXXXXX
** 功能描述：XXXXXXXXXXXXXXXX
** 其他说明：
** 创 建 人：陆振宇
** 创建时间：2015-05-31
** ----------------------------------------------------------------------------
** 修 改 人：陆振宇
** 修改时间：2015-05-31
** 修改说明：
** ----------------------------------------------------------------------------
** 修 改 人：陆振宇
** 修改时间：2015-05-31
** 修改说明：
** ----------------------------------------------------------------------------
*******************************************************************************/	

/* ------------------------------头文件包含-----------------------------------*/
#include "ROS_hydraulic_Control_Algorithm.h"
/* --------------------------------宏指令-------------------------------------*/

/* ---------------------------------全局变量----------------------------------*/

/* ---------------------------------静态变量----------------------------------*/

/* ----------------------------------函数-------------------------------------*/

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：PID参数初始化
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：陆振宇
** 创建时间：2015-05-31
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
void ControlAlgorithm_PIDParmeters_Init(PID_ControlParameters_TypeDef* PID_Parameters)
{	
	PID_Parameters->KP=0;			//比例常数
	PID_Parameters->KI=0;			//积分常数
	PID_Parameters->KD=0;			//微分常数
	
	PID_Parameters->Error=0;		 //当前误差
	PID_Parameters->LastError=0;   // Error[-1]  前一拍误差
	PID_Parameters->PreError=0;    // Error[-2]  前两拍误差
	PID_Parameters->SumError=0;	 //总偏差之和
	PID_Parameters->DError=0;		 //偏差微分
	
	PID_Parameters->KP_error=0;
	PID_Parameters->KI_error=0;
	PID_Parameters->KD_error=0;
}


/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：位置PID算法
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：陆振宇
** 创建时间：2015-05-31
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
void ControlAlgorithm_PositionPID(PID_ControlParameters_TypeDef* PID)
{
	PID->PreError = PID->LastError;
	PID->LastError = PID->Error;
	PID->Error =*(PID->Reference)- *(PID->Real);
	PID->SumError = PID->Error+PID->SumError;
	PID->DError = PID->Error - PID->LastError;//当前偏差
	
	PID->KP_error = PID->KP * PID->Error;
	PID->KI_error = PID->KI * PID->SumError;
	PID->KD_error = PID->KD * PID->DError;

	PID->Output=PID->KP_error+PID->KI_error+PID->KD_error; 
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：增量式PID算法
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：陆振宇
** 创建时间：2015-05-31
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
void ControlAlgorithm_AddPID(PID_ControlParameters_TypeDef* PID)
{
	PID->PreError = PID->LastError;
	PID->LastError = PID->Error;
	PID->Error =*(PID->Reference)- *(PID->Real);
	PID->SumError = PID->Error+PID->SumError;
	PID->DError = PID->Error - PID->LastError;//当前偏差
	
	PID->KP_error = PID->KP * PID->DError;
	PID->KI_error = PID->KI * PID->Error;
	PID->KD_error = PID->KD * (PID->Error-2*PID->LastError+PID->PreError);

	PID->Output=PID->KP_error+PID->KI_error+PID->KD_error; 	
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：二维MAP图插值
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：陆振宇
** 创建时间：2015-05-31
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
int32_t ControlAlgorithm_Griddata(Mesh_TypeDef*Mesh,int32_t X_index,int32_t Y_index)
{
	int i;
	int index[2];
	int32_t Z_index;
	for(i=0;i<100;i++)
	{
		if(X_index>(Mesh->X)[i])
		{
			index[0]=i;
			break;	
		};		
	};
	for(i=0;i<100;i++)
	{
		if(Y_index>(Mesh->Y)[i])
		{
			index[1]=i;
			break;	
		};		
	};
	Z_index=(Mesh->Z)[index[0]][index[1]];	
	return Z_index;	
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：Kalman filter
** 其他说明：用于二阶质量块的系统的位置融合
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：陆振宇
** 创建时间：2015-05-31
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
Kalmanfilter_TypeDef ControlAlgorithm_KalmanFilter(int32_t Measurement_Z[2],Kalmanfilter_TypeDef Kalman_pre,int32_t U_input)
{
	Kalmanfilter_TypeDef Kalman;
	int32_t Update_Y[2];
	int32_t Update_K[2][2];
	int32_t K_sp=1;
	int32_t B_p=1;
	int32_t m_p=1;
	int32_t K_so=1;
	int32_t delta_t=1;
	int32_t sigma_a=1;//平方差
	int32_t sigma_z=1;//平方差
	int32_t K_mat[2][2];
	int32_t den_P;

	K_mat[0][0]=(1-K_sp/m_p*delta_t*delta_t/2);
	K_mat[0][1]=(delta_t-B_p/m_p*delta_t*delta_t/2);
	K_mat[1][0]=(-K_sp/m_p*delta_t);
	K_mat[1][1]=(-B_p/m_p*delta_t+1);

	Kalman.X[0]=K_mat[0][0]*Kalman_pre.X[0]+K_mat[0][1]*Kalman_pre.X[1]+(delta_t*delta_t*K_so/m_p/2)*U_input;
	Kalman.X[1]=K_mat[1][0]*Kalman_pre.X[0]+K_mat[1][1]*Kalman_pre.X[1]+(delta_t*K_so/m_p)*U_input;

	Kalman.P[0][0]=K_mat[0][0]*K_mat[0][0]*Kalman_pre.P[0][0]+K_mat[0][1]*K_mat[0][0]*Kalman_pre.P[0][1]+
				K_mat[0][0]*K_mat[0][1]*Kalman_pre.P[1][0]+K_mat[0][1]*K_mat[0][1]*Kalman_pre.P[1][1]+
				delta_t*delta_t*delta_t*delta_t/4*sigma_a;
	Kalman.P[0][1]=K_mat[1][0]*K_mat[0][0]*Kalman_pre.P[0][0]+K_mat[1][1]*K_mat[0][0]*Kalman_pre.P[0][1]+
				K_mat[1][0]*K_mat[0][1]*Kalman_pre.P[1][0]+K_mat[1][1]*K_mat[0][1]*Kalman_pre.P[1][1]+
				delta_t*delta_t*delta_t/2*sigma_a;
	Kalman.P[1][0]=K_mat[0][0]*K_mat[1][0]*Kalman_pre.P[0][0]+K_mat[0][1]*K_mat[1][0]*Kalman_pre.P[0][1]+
				K_mat[0][0]*K_mat[1][1]*Kalman_pre.P[1][0]+K_mat[0][1]*K_mat[1][1]*Kalman_pre.P[1][1]+
				delta_t*delta_t*delta_t/2*sigma_a;
	Kalman.P[1][1]=K_mat[1][0]*K_mat[1][0]*Kalman_pre.P[0][0]+K_mat[1][1]*K_mat[1][0]*Kalman_pre.P[0][1]+
				K_mat[1][0]*K_mat[1][1]*Kalman_pre.P[1][0]+K_mat[1][1]*K_mat[1][1]*Kalman_pre.P[1][1]+
				delta_t*delta_t*sigma_a;

	Update_Y[0]=1*Measurement_Z[0]-Kalman_pre.X[0];
	Update_Y[1]=1*Measurement_Z[1]-Kalman_pre.X[1];

	den_P= (Kalman.P[0][0]+sigma_z)*(Kalman.P[1][1]+sigma_a*delta_t*delta_t)+Kalman.P[0][1]*Kalman.P[1][0];
	Update_K[0][0]=(Kalman.P[0][0]*(Kalman.P[1][1]+sigma_a*delta_t*delta_t)-Kalman.P[0][0]*Kalman.P[1][0])/den_P;
	Update_K[0][1]=(Kalman.P[0][1]*(Kalman.P[0][0]+sigma_z)-Kalman.P[0][0]*Kalman.P[0][1])/den_P;
	Update_K[1][0]=(Kalman.P[1][0]*(Kalman.P[1][1]+sigma_a*delta_t*delta_t)-Kalman.P[1][1]*Kalman.P[1][0])/den_P;
	Update_K[1][1]=(Kalman.P[1][1]*(Kalman.P[0][0]+sigma_z)-Kalman.P[1][0]*Kalman.P[0][1])/den_P;

	Kalman.X[0]=Kalman.X[0]+Update_K[0][0]*Update_Y[0]+Update_K[0][1]*Update_Y[1];
	Kalman.X[1]=Kalman.X[1]+Update_K[1][0]*Update_Y[0]+Update_K[1][1]*Update_Y[1];

	Kalman.P[0][0]=Kalman.P[0][0]*(1-Update_K[0][0]);
	Kalman.P[0][1]=Kalman.P[0][1]*(1-Update_K[0][1]);
	Kalman.P[1][0]=Kalman.P[1][0]*(1-Update_K[1][0]);
	Kalman.P[1][1]=Kalman.P[1][1]*(1-Update_K[1][1]);

	return Kalman;
};
