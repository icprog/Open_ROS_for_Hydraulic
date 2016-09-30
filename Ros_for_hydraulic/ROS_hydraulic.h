/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**						     ROS_hydraulic.h
**
** 				 		       ZJU - 2015
**
** ϵͳ���ܣ�
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic.h
** ģ �� �������ڶ���Һѹϵͳ���õ��Ľṹ��
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
#ifndef __ROS_hydraulic__
#define __ROS_hydraulic__
/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "stm32f10x.h"
#include "stm32_eval.h"
//#include "I2C.h"
#include <stdio.h>
//#include "PWM_config.h"
//#include "PID.h"
//#include "IO.h"
#include "Time_test.h"
/* --------------------------------��ָ��-------------------------------------*/
#define NCU_ROS_DEBUG 1					 //���Գ���
#define NCU_ROS_ENABLE 1		 //�����˲���ϵͳʹ��
#define UCOSII_ROS_ENABLE 1	 	 //UCOSII����ϵͳʹ��

#define ON TRUE	 	 //��״̬
#define OFF FALSE	 	 //��״̬
/* ------------------------------�ṹ�嶨��-----------------------------------*/
/*ָʾ��I/O��*/
//typedef struct	   
//{
//	uint8_t IndexLED_GPIO;
//}IndexLED_InitTypeDef;
/*ָʾ��*/
typedef struct
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef* GPIOX;

	bool IndexLED_State;
	uint8_t Flash_Method;
	uint32_t Flash_Frequency;
}IndexLED_TypeDef;

/*������I/O��*/
//typedef struct
//{
//	uint8_t Buzzer_GPIO;
//}Buzzer_InitTypeDef;
/*������*/
typedef struct
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef* GPIOX;
	bool Buzzer_State;
	uint8_t Buzz_Method;
	uint32_t Buzz_Frequency;
}Buzzer_TypeDef;
/*���������I/O��*/
//typedef struct
//{
//	uint8_t PropertionalSolenoid_GPIO;
//}PropertionalSolenoid_InitTypeDef;
/*���������*/
typedef struct
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef*  GPIOX;
	uint8_t PropertionalSolenoid_State;
	uint32_t Input_PWM_duty_radio;
	int32_t Reference_Current;
	int32_t Real_Current;
	uint32_t UpEdge_Current;
	uint32_t DownEdge_Current;
	int32_t Inductance;
	float Resistance;
	int32_t Core_Location;
	int32_t Temperature;
	uint8_t Flag;
	uint8_t Index;
}PropertionalSolenoid_TypeDef;

/*�ȵ�����*/
typedef struct
{
	uint8_t Valve_State;
	int32_t Spool_Position;
	uint32_t PPort_Pressure;
	uint32_t APort_Pressure;
	uint32_t BPort_Pressure;
	uint32_t TPort_Pressure;
	uint32_t AreaGradient;
}PilotValve_TypeDef;

/*������*/
typedef struct
{
	uint8_t Valve_State;
	int32_t Spool_Position_Ref;
	int32_t Spool_Position_Real;
	uint32_t PPort_Pressure;
	uint32_t APort_Pressure;
	uint32_t BPort_Pressure;
	uint32_t TPort_Pressure;
	uint32_t AreaGradient;
}MainValve_TypeDef;

/*LVDTλ�ƴ�����I/O��*/
//typedef struct
//{
//	uint8_t LVDT_Position_GPIO;
//}LVDT_PositionSenser_InitTypeDef;
/*LVDTλ�ƴ�����*/
typedef struct
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_TypeDef*  GPIOX;
	int32_t Position;
}LVDT_PositionSenser_TypeDef;

/*ѹ��������I/O��*/
//typedef struct
//{
//	uint8_t PressureSenser_GPIO;
//}PressureSenser_InitTypeDef;
/*ѹ��������*/
typedef struct
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_TypeDef* GPIOX;
	uint32_t Pressure;
   	uint8_t Index;
}PressureSenser_TypeDef;

/*�¶ȴ�����I/O��*/
//typedef struct
//{
//	uint8_t TemperatureSenser_GPIO;
//}TemperatureSenser_InitTypeDef;
/*�¶ȴ�����*/
typedef struct
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef*  GPIOX;
	uint32_t Temperature;
}TemperatureSenser_TypeDef;

/*��ѹ�źż���ʹ�����*/
typedef struct
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef*  GPIOX;
	uint32_t Voltage;
}VoltageSenser_TypeDef;

/*��ƽ�źż���ͽӿ�*/
typedef struct
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef*  GPIOX;
	uint8_t Voltage_Level;
}VoltageLevel_TypeDef;


/*PID�����㷨*/
typedef struct
{
	int32_t	*Reference;	//�趨�ο�ֵ
	int32_t	*Real;		//��ǰ��ʵֵ
	
	float	KP;			//��������
	float	KI;			//���ֳ���
	float	KD;			//΢�ֳ���

	int32_t Error;		 //��ǰ���
	int32_t	LastError;   // Error[-1]  ǰһ�����
	int32_t PreError;    // Error[-2]  ǰ�������
	int32_t	SumError;	 //��ƫ��֮��
	int32_t	DError;		 //ƫ��΢��
		
	int32_t	KP_error;
	int32_t KI_error;
	int32_t KD_error;
	         
	float	Output;
}PID_ControlParameters_TypeDef;

/*���ݱ���*/
typedef struct
{
	int32_t X[100];	 //��С����
	int32_t Y[100];	 //��С����
	int32_t Z[100][100];
}Mesh_TypeDef;

/*Kalmanfilter�ṹ�嶨�壬����*/
typedef struct
{
	int32_t X[2];	 //��С����
	int32_t P[2][2];	 //��С����
}Kalmanfilter_TypeDef;

/* ------------------------------ȫ�ֱ���-----------------------------------*/


#endif




