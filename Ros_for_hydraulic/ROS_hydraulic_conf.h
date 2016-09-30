/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**						     ROS_hydraulic_conf.h
**
** 				 		       ZJU - 2015
**
** 系统介绍：
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_conf.h
** 模 块 名：用于配置特定液压系统中的器件全局变量
** 功能描述：xxxxxxxxxxxxxxxx
** 其他说明：
**
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
#ifndef __ROS_hydraulic_conf__
#define __ROS_hydraulic_conf__
/* ------------------------------头文件包含-----------------------------------*/
#include "stm32f10x.h"
#include "stm32_eval.h"
//#include "stm3210e_eval.h"
//#include "I2C.h"
#include <stdio.h>
//#include "PWM_config.h"
//#include "PID.h"
//#include "IO.h"
#include "Time_test.h"
#include "ROS_hydraulic.h"
//#include "ROS_hydraulic_Init_for_STM32.h"
//#include "ROS_hydraulic_Init_for_PeriphChip.h"
//#include "ROS_hydraulic_Senser_Acquisition.h"
//#include "ROS_hydraulic_Actuator_Output.h"
//#include "ROS_hydraulic_Control_Law.h"
//#include "ROS_hydraulic_Function_Packaging.h"
#include "ROS_hydraulic_Init_for_STM32.h"
#include "ROS_hydraulic_Init_for_PeriphChip.h"
#include "ROS_hydraulic_Init_for_SubElements.h"
#include "ROS_hydraulic_Init_for_Communication.h"
#include "ROS_hydraulic_Init_for_LogRAM.h"
#include "ROS_hydraulic_SubElements.h"
#include "ROS_hydraulic_Element.h"
#include "ROS_hydraulic_Control_Algorithm.h"
#include "ROS_hydraulic_Input_Signal.h"
#include "ROS_hydraulic_Log.h"
#include "ROS_hydraulic_Communication.h"
#include "ROS_hydraulic_conf.h"
#include "ROS_hydraulic_Function_Realization.h"


/* ------------------------------全局变量-----------------------------------*/
/*物理器件*/
extern IndexLED_TypeDef IndexLED_POWER;	/*供电指示灯*/
extern IndexLED_TypeDef IndexLED_A;	/*A电磁铁上电指示灯*/
extern IndexLED_TypeDef IndexLED_B;	/*B电磁铁上电指示灯*/
extern IndexLED_TypeDef IndexLED_Window;	/*控制偏差 ≥ 区域（黄色）*/
extern IndexLED_TypeDef IndexLED_Err;	/*出错指示*/
extern IndexLED_TypeDef IndexLED_Dx[5];  /*二进制数字指示*/

extern Buzzer_TypeDef Buzzer_Alarm;	/*蜂鸣器*/

extern PropertionalSolenoid_TypeDef SolenoidA;	/*比例电磁铁A*/
extern PropertionalSolenoid_TypeDef SolenoidB;	/*比例电磁铁B*/

extern PilotValve_TypeDef PilotValve;	/*先导阀体*/
extern MainValve_TypeDef MainValve;	/*主阀体*/

extern PressureSenser_TypeDef PressureSenser[3]; /*压力传感器*/

//extern TemperatureSenser_TypeDef TemperatureSenser; /*温度传感器*/

extern VoltageLevel_TypeDef InputSignal_Flag;

/*控制参数*/
extern PID_ControlParameters_TypeDef PID_SolenoidA_Current; /*PID控制参数*/
extern PID_ControlParameters_TypeDef PID_SolenoidB_Current; /*PID控制参数*/
extern PID_ControlParameters_TypeDef PID_MainValve_Position; /*PID控制参数*/
extern int32_t Init_PWM_duty_radio;	//3100=31%
extern int32_t Init_Solenoid_Current;	//mA
extern int32_t PWM_Period;
extern int32_t Supply_Voltage;

void ROS_HY_SubElements_Conf(void);
void ROS_HY_System_Conf(void);

#endif




