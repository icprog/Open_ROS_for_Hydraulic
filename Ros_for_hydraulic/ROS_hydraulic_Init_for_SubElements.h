/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_SubElements.h
**
** 				 		      ZJU - 2015
**
** 系统介绍：XXXXXXXXXXXXXXXXXXXXXX
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_Init_for_SubElements.h
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
#ifndef __ROS_hydraulic_Init_for_SubElements__
#define __ROS_hydraulic_Init_for_SubElements__
/* ------------------------------头文件包含-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* --------------------------------函数申明-------------------------------------*/
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
