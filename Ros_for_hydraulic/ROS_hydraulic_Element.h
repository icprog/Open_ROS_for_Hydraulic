/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Element.h
**
** 				 		      ZJU - 2015
**
** ϵͳ���ܣ�XXXXXXXXXXXXXXXXXXXXXX
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_Element.h
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
#ifndef __ROS_hydraulic_Element__
#define __ROS_hydraulic_Element__
/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* ------------------------------�ṹ�嶨��-----------------------------------*/
///*�ȵ�����*/
//typedef struct
//{
//	uint8_t Valve_State;
//	int32_t Spool_Position;
//	uint32_t PPort_Pressure;
//	uint32_t APort_Pressure;
//	uint32_t BPort_Pressure;
//	uint32_t TPort_Pressure;
//	uint32_t AreaGradient;
//}PilotValve_TypeDef;
//
///*������*/
//typedef struct
//{
//	uint8_t Valve_State;
//	int32_t Spool_Position;
//	uint32_t PPort_Pressure;
//	uint32_t APort_Pressure;
//	uint32_t BPort_Pressure;
//	uint32_t TPort_Pressure;
//	uint32_t AreaGradient;
//}MainValve_TypeDef;

/* --------------------------------��������-------------------------------------*/
	#if(NCU_ROS_DEBUG>0) 
		void Init_Debug_Conf(void);
	#endif

//void PropertionalSolenoid_PWM_Output(int32_t PWM_duty_radio,PropertionalSolenoid_TypeDef *Solenoid);
void Elements_MainValvePosition_Acquisition(MainValve_TypeDef *MainValve);
#endif
