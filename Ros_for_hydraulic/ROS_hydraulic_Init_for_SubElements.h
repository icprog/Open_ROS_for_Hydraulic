/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_SubElements.h
**
** 				 		      ZJU - 2015
**
** ϵͳ���ܣ�XXXXXXXXXXXXXXXXXXXXXX
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_Init_for_SubElements.h
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
#ifndef __ROS_hydraulic_Init_for_SubElements__
#define __ROS_hydraulic_Init_for_SubElements__
/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* --------------------------------��������-------------------------------------*/
	#if(NCU_ROS_DEBUG>0) 
		void Init_Debug_Conf(void);
	#endif
void IndexLED_Init(uint32_t GPIO_CLK,IndexLED_TypeDef *IndexLED);
void Buzzer_Init(uint32_t GPIO_CLK,Buzzer_TypeDef *Buzzer);
void PropertionalSolenoid_Init(uint32_t GPIO_CLK,PropertionalSolenoid_TypeDef *Solenoid);
//void LVDT_PositionSenser_Init(GPIO_TypeDef *GPIOx,LVDT_PositionSenser_TypeDef *LVDT_PositionSenser);
//void PressureSenser_Init(uint32_t GPIO_CLK,PressureSenser_TypeDef *PressureSenser);
//void VoltageSenser_Init(uint32_t GPIO_CLK,VoltageSenser_TypeDef *VoltageSenser);
void VoltageLevel_Input_Init(uint32_t GPIO_CLK,VoltageLevel_TypeDef *Input);
void ROS_HY_Init_SubElements(void);


#endif
