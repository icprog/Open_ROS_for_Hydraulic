/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Control_Algorithm.h
**
** 				 		      ZJU - 2015
**
** ϵͳ���ܣ�XXXXXXXXXXXXXXXXXXXXXX
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_Control_Algorithm.h
** ģ �� ����XXXXXXXXXXXXXXXXXXXX
** ����������XXXXXXXXXXXXXXXX
** ����˵����
** �� �� �ˣ�½����
** ����ʱ�䣺2015-05-31
** ----------------------------------------------------------------------------
** �� �� �ˣ�½����
** �޸�ʱ�䣺2015-05-31
** �޸�˵����
** ----------------------------------------------------------------------------
** �� �� �ˣ�½����
** �޸�ʱ�䣺2015-05-31
** �޸�˵����
** ----------------------------------------------------------------------------
*******************************************************************************/		
#ifndef __ROS_hydraulic_Control_Algorithm__
#define __ROS_hydraulic_Control_Algorithm__
/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* ------------------------------�ṹ�嶨��-----------------------------------*/
///*PID�����㷨*/
//typedef struct
//{
//	int32_t	*Reference;	//�趨�ο�ֵ
//	int32_t	*Real;		//��ǰ��ʵֵ
//	
//	float	KP;			//��������
//	float	KI;			//���ֳ���
//	float	KD;			//΢�ֳ���
//
//	int32_t Error;		 //��ǰ���
//	int32_t	LastError;   // Error[-1]  ǰһ�����
//	int32_t PreError;    // Error[-2]  ǰ�������
//	int32_t	SumError;	 //��ƫ��֮��
//	int32_t	DError;		 //ƫ��΢��
//		
//	int32_t	KP_error;
//	int32_t KI_error;
//	int32_t KD_error;
//	         
//	float	Output;
//}PID_ControlParameters_TypeDef;
/* --------------------------------��������-------------------------------------*/
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
