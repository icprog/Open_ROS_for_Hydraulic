/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_STM32.h
**
** 				 		      ZJU - 2015
**
** ϵͳ���ܣ�XXXXXXXXXXXXXXXXXXXXXX
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_Init_for_STM32.h
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
#ifndef __ROS_hydraulic_Init_for_STM32__
#define __ROS_hydraulic_Init_for_STM32__
/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* --------------------------------��������-------------------------------------*/
	#if(NCU_ROS_DEBUG>0) 
		void Init_Debug_Conf(void);
	#endif
void GPIO_EnergySaving_Init(void);
void IO_GPIO_Config(void);
void NVIC_Configuration(void);
void ROS_HY_Init_STM32(void);
void TIM2_Configuration(void);
void TIM2_IRQHandler_Init(void);
void TIM3_IRQHandler_Init(void);
void EXTI9_5_IRQ_Init(void);
void EXTI9_5_Pin8_IRQ_Init(void);
void EXTI9_5_Pin9_IRQ_Init(void);
void TIM2_NVIC_Configuration(void);
static void TIM3_GPIO_Config(void);
static void TIM3_Mode_Config(void);
void TIM3_PWM_Init(void);

#endif
