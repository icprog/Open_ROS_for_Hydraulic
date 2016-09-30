/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Actuator_Output.h
**
** 				 		      ZJU - 2015
**
** 系统介绍：XXXXXXXXXXXXXXXXXXXXXX
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_Actuator_Output.h
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
#ifndef __ROS_hydraulic_Actuator_Output__
#define __ROS_hydraulic_Actuator_Output__
/* ------------------------------头文件包含-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* --------------------------------函数申明-------------------------------------*/
	#if(NCU_ROS_DEBUG>0) 
		void Init_Debug_Conf(void);
	#endif

//void PropertionalSolenoid_PWM_Output(int32_t PWM_duty_radio,PropertionalSolenoid_TypeDef *Solenoid);


#endif
