/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_PeriphChip.h
**
** 				 		      ZJU - 2015
**
** 系统介绍：XXXXXXXXXXXXXXXXXXXXXX
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_Init_for_STM32.h
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
#ifndef __ROS_hydraulic_Init_for_PeriphChip__
#define __ROS_hydraulic_Init_for_PeriphChip__
/* ------------------------------头文件包含-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* --------------------------------函数申明-------------------------------------*/
	#if(NCU_ROS_DEBUG>0) 
		void Init_Debug_Conf(void);
	#endif

#define  	AD_DATABUS				    0xFF
#define     AD_HBEN        	 		GPIO_Pin_3                                  // PA3
#define     AD_CS         		   	GPIO_Pin_4                                  // PA4
#define     AD_WR         		  	GPIO_Pin_6                                  // PA6
#define     AD_RD         		  	GPIO_Pin_7                                  // PA7
#define     AD_INT         		  	GPIO_Pin_5                                  // PA5

#define	    MAX197SendData(dat)		GPIO_ResetBits(GPIOC,AD_DATABUS); GPIO_SetBits(GPIOC,dat&AD_DATABUS)

#define     Set_CS_High()		GPIO_SetBits(GPIOA,AD_CS)
#define     Clr_CS_Low()		GPIO_ResetBits(GPIOA,AD_CS)

#define     Set_HBEN_High()		GPIO_SetBits(GPIOA,AD_HBEN)
#define     Clr_HBEN_Low()		GPIO_ResetBits(GPIOA,AD_HBEN)

#define     Set_WR_High()		GPIO_SetBits(GPIOA,AD_WR)
#define     Clr_WR_Low()		GPIO_ResetBits(GPIOA,AD_WR)

#define     Set_RD_High()		GPIO_SetBits(GPIOA,AD_RD)
#define     Clr_RD_Low()		GPIO_ResetBits(GPIOA,AD_RD)
	


void MAX197_Init(void);
void MAX197Write_cmd(uint8_t ch);
int32_t MAX197Read_data(void);
int32_t ADCfilters(int32_t Weiyi[],int8_t N);
int32_t Read_MAX197(uint8_t ch);
int32_t Read_Port(uint8_t ch);
void DelayNs(uint8_t t);
void ROS_HY_Init_PeriphChip(void);

#endif
