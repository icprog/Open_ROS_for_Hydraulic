/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**						     ROS_hydraulic_conf.h
**
** 				 		       ZJU - 2015
**
** ϵͳ���ܣ�
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_conf.h
** ģ �� �������������ض�Һѹϵͳ�е�����ȫ�ֱ���
** ����������xxxxxxxxxxxxxxxx
** ����˵����
**
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
#ifndef __ROS_hydraulic_conf__
#define __ROS_hydraulic_conf__
/* ------------------------------ͷ�ļ�����-----------------------------------*/
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


/* ------------------------------ȫ�ֱ���-----------------------------------*/
/*��������*/
extern IndexLED_TypeDef IndexLED_POWER;	/*����ָʾ��*/
extern IndexLED_TypeDef IndexLED_A;	/*A������ϵ�ָʾ��*/
extern IndexLED_TypeDef IndexLED_B;	/*B������ϵ�ָʾ��*/
extern IndexLED_TypeDef IndexLED_Window;	/*����ƫ�� �� ���򣨻�ɫ��*/
extern IndexLED_TypeDef IndexLED_Err;	/*����ָʾ*/
extern IndexLED_TypeDef IndexLED_Dx[5];  /*����������ָʾ*/

extern Buzzer_TypeDef Buzzer_Alarm;	/*������*/

extern PropertionalSolenoid_TypeDef SolenoidA;	/*���������A*/
extern PropertionalSolenoid_TypeDef SolenoidB;	/*���������B*/

extern PilotValve_TypeDef PilotValve;	/*�ȵ�����*/
extern MainValve_TypeDef MainValve;	/*������*/

extern PressureSenser_TypeDef PressureSenser[3]; /*ѹ��������*/

//extern TemperatureSenser_TypeDef TemperatureSenser; /*�¶ȴ�����*/

extern VoltageLevel_TypeDef InputSignal_Flag;

/*���Ʋ���*/
extern PID_ControlParameters_TypeDef PID_SolenoidA_Current; /*PID���Ʋ���*/
extern PID_ControlParameters_TypeDef PID_SolenoidB_Current; /*PID���Ʋ���*/
extern PID_ControlParameters_TypeDef PID_MainValve_Position; /*PID���Ʋ���*/
extern int32_t Init_PWM_duty_radio;	//3100=31%
extern int32_t Init_Solenoid_Current;	//mA
extern int32_t PWM_Period;
extern int32_t Supply_Voltage;

void ROS_HY_SubElements_Conf(void);
void ROS_HY_System_Conf(void);

#endif




