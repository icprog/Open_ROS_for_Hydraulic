/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Element.h
**
** 				 		      ZJU - 2015
**
** 系统介绍：XXXXXXXXXXXXXXXXXXXXXX
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_Element.h
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
#ifndef __ROS_hydraulic_Element__
#define __ROS_hydraulic_Element__
/* ------------------------------头文件包含-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* ------------------------------结构体定义-----------------------------------*/
///*先导阀体*/
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
///*主阀体*/
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

/* --------------------------------函数申明-------------------------------------*/
	#if(NCU_ROS_DEBUG>0) 
		void Init_Debug_Conf(void);
	#endif

//void PropertionalSolenoid_PWM_Output(int32_t PWM_duty_radio,PropertionalSolenoid_TypeDef *Solenoid);
void Elements_MainValvePosition_Acquisition(MainValve_TypeDef *MainValve);
#endif
