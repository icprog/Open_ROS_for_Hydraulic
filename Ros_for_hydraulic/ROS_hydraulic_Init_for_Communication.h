/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_Communication.h
**
** 				 		      ZJU - 2015
**
** ϵͳ���ܣ�XXXXXXXXXXXXXXXXXXXXXX
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_Init_for_Communication.h
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
#ifndef __ROS_hydraulic_Init_for_Communication__
#define __ROS_hydraulic_Init_for_Communication__
/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* --------------------------------��������-------------------------------------*/
	#if(NCU_ROS_DEBUG>0) 
		void Init_Debug_Conf(void);
	#endif
void ROS_HY_Init_Communication(void);
void RS232_Init(void);
void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);

#endif
