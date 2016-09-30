/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Function_Realization.h
**
** 				 		      ZJU - 2015
**
** 系统介绍：XXXXXXXXXXXXXXXXXXXXXX
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_Function_Realization.h
** 模 块 名：XXXXXXXXXXXXXXXXXXXX
** 功能描述：针对特定的控制器电路板配置IO口及定义
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
#ifndef __ROS_hydraulic_Function_Realization__
#define __ROS_hydraulic_Function_Realization__
 
/* ------------------------------头文件包含-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* --------------------------------函数申明-------------------------------------*/
	#if(NCU_ROS_DEBUG>0) 
		void Init_Debug_Conf(void);
	#endif
void ProportionalValve_Alarm(void);
void ProportionalValve_Communication(void);
void ProportionalValve_DetectionDiagnosis(void);
void ProportionalValve_Log(void);
void ProportionalValve_MainSpool_PositionTrack_Control(void);
void ProportionalValve_PilotPort_Control(void);
void ProportionalValve_PilotSpool_ONOFF_Control(void);
void ProportionalValve_PilotSpool_PositionTrack_Control(void);




#endif
