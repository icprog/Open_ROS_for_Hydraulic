/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_SubElements.h
**
** 				 		      ZJU - 2015
**
** ϵͳ���ܣ�XXXXXXXXXXXXXXXXXXXXXX
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_SubElements.h
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
#ifndef __ROS_hydraulic_SubElements__
#define __ROS_hydraulic_SubElements__
/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* ------------------------------�ṹ�嶨��-----------------------------------*/
///*ָʾ��*/
//typedef struct
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_TypeDef* GPIOX;
//	uint8_t IndexLED_State;
//	uint8_t Flash_Method;
//	uint32_t Flash_Frequency;
//}IndexLED_TypeDef;
///*������*/
//typedef struct
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_TypeDef* GPIOX;
//	uint8_t Buzzer_State;
//	uint8_t Buzz_Method;
//	uint32_t Buzz_Frequency;
//}Buzzer_TypeDef;
///*���������*/
//typedef struct
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_TypeDef*  GPIOX;
//	uint8_t PropertionalSolenoid_State;
//	uint32_t Input_PWM_duty_radio;
//	int32_t Reference_Current;
//	int32_t Real_Current;
//	uint32_t Inductance;
//	uint32_t Resistance;
//	int32_t Core_Location;
//	int32_t Temperature;
//	uint8_t Flag;
//	uint8_t Index;
//}PropertionalSolenoid_TypeDef;
//
///*LVDTλ�ƴ�����*/
//typedef struct
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_TypeDef*  GPIOX;
//	int32_t Position;
//}LVDT_PositionSenser_TypeDef;
//
///*ѹ��������*/
//typedef struct
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_TypeDef* GPIOX;
//	uint32_t Pressure;
//}PressureSenser_TypeDef;
//
///*�¶ȴ�����I/O��*/
//typedef struct
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_TypeDef*  GPIOX;
//	uint32_t Temperature;
//}TemperatureSenser_TypeDef;
//
///*��ѹ�źż���ʹ�����*/
//typedef struct
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_TypeDef*  GPIOX;
//	uint32_t Voltage;
//}VoltageSenser_TypeDef;

/* --------------------------------��������-------------------------------------*/
	#if(NCU_ROS_DEBUG>0) 
		void Init_Debug_Conf(void);
	#endif

void PropertionalSolenoid_PWM_Output(int32_t PWM_duty_radio,PropertionalSolenoid_TypeDef *Solenoid);
void PropertionalSolenoid_PWM_Output2(int32_t PWM_duty_radio,PropertionalSolenoid_TypeDef *Solenoid);
void SubElements_IndexLED_Output(bool State,IndexLED_TypeDef *LED);
//void SubElements_LVDTPosition_Acquisition(int32_t *LVDT_Sensor);
void SubElements_PropertionalSolenoid_Current_Acquisition(PropertionalSolenoid_TypeDef *Solenoid);
void SubElements_PropertionalSolenoid_Current_Filter_Acquisition(PropertionalSolenoid_TypeDef *Solenoid);
void SubElements_PressureSensor_Acquisition(PressureSenser_TypeDef* PressureSensor);
void SubElements_PropertionalSolenoid_PWM_Control(int32_t PWM_duty_radio,int32_t PWM_Period,PropertionalSolenoid_TypeDef *Solenoid);
void SubElements_IOLevel_Acquisition(VoltageLevel_TypeDef* Input_IO);
void SubElements_PropertionalSolenoid_Current_PIDTrack(PID_ControlParameters_TypeDef* PID_Solenoid);
void SubElements_PropertionalSolenoid_GetInductance(PropertionalSolenoid_TypeDef *Solenoid);
void SubElements_Buzzer_Output(bool State,Buzzer_TypeDef *Buzzer);
#endif
