/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Control_Algorithm.h
**
** 				 		      ZJU - 2015
**
** 系统介绍：XXXXXXXXXXXXXXXXXXXXXX
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_Control_Algorithm.h
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
#ifndef __ROS_hydraulic_Control_Algorithm__
#define __ROS_hydraulic_Control_Algorithm__
/* ------------------------------头文件包含-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* ------------------------------结构体定义-----------------------------------*/
///*PID控制算法*/
//typedef struct
//{
//	int32_t	*Reference;	//设定参考值
//	int32_t	*Real;		//当前真实值
//	
//	float	KP;			//比例常数
//	float	KI;			//积分常数
//	float	KD;			//微分常数
//
//	int32_t Error;		 //当前误差
//	int32_t	LastError;   // Error[-1]  前一拍误差
//	int32_t PreError;    // Error[-2]  前两拍误差
//	int32_t	SumError;	 //总偏差之和
//	int32_t	DError;		 //偏差微分
//		
//	int32_t	KP_error;
//	int32_t KI_error;
//	int32_t KD_error;
//	         
//	float	Output;
//}PID_ControlParameters_TypeDef;
/* --------------------------------函数申明-------------------------------------*/
	#if(NCU_ROS_DEBUG>0) 
		void Init_Debug_Conf(void);
	#endif

//void PropertionalSolenoid_PWM_Output(int32_t PWM_duty_radio,PropertionalSolenoid_TypeDef *Solenoid);
void ControlAlgorithm_PositionPID(PID_ControlParameters_TypeDef* PID);	
void ControlAlgorithm_AddPID(PID_ControlParameters_TypeDef* PID);
void ControlAlgorithm_PIDParmeters_Init(PID_ControlParameters_TypeDef* PID_Parameters);
int32_t ControlAlgorithm_Griddata(Mesh_TypeDef*Mesh,int32_t X_index,int32_t Y_index);
Kalmanfilter_TypeDef ControlAlgorithm_KalmanFilter(int32_t Measurement_Z[2],Kalmanfilter_TypeDef Kalman_pre,int32_t U_input);

#endif
