/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Function_Realization.h
**
** 				 		      ZJU - 2015
**
** ϵͳ���ܣ�XXXXXXXXXXXXXXXXXXXXXX
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_Function_Realization.h
** ģ �� ����XXXXXXXXXXXXXXXXXXXX
** ��������������ض��Ŀ�������·������IO�ڼ�����
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
#ifndef __ROS_hydraulic_Function_Realization__
#define __ROS_hydraulic_Function_Realization__
 
/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* --------------------------------��������-------------------------------------*/
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
