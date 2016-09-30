/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**						     ROS_hydraulic_conf.c
**
** 				 		       ZJU - 2015
**
** ϵͳ���ܣ�
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_conf.h
** ģ �� �������������ض�Һѹϵͳ�еĿ���Ӳ���ṹ������ȫ�ֱ���������ֵ
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
/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* --------------------------------��ָ��-------------------------------------*/

/* ---------------------------------ȫ�ֱ���----------------------------------*/

/*��������*/
IndexLED_TypeDef IndexLED_POWER;	/*����ָʾ��*/
IndexLED_TypeDef IndexLED_A;	/*A������ϵ�ָʾ��*/
IndexLED_TypeDef IndexLED_B;	/*B������ϵ�ָʾ��*/
IndexLED_TypeDef IndexLED_Window;	/*����ƫ�� �� ���򣨻�ɫ��*/
IndexLED_TypeDef IndexLED_Err;	/*����ָʾ*/
IndexLED_TypeDef IndexLED_Dx[5];  /*����������ָʾ*/

Buzzer_TypeDef Buzzer_Alarm;	/*������*/

PropertionalSolenoid_TypeDef SolenoidA;	/*���������A*/
PropertionalSolenoid_TypeDef SolenoidB;	/*���������B*/

PilotValve_TypeDef PilotValve;	/*�ȵ�����*/
MainValve_TypeDef MainValve;	/*������*/
//LVDT_PositionSenser_TypeDef  MainValve_LVDT;
PressureSenser_TypeDef PressureSenser[3]; /*ѹ��������*/

//TemperatureSenser_TypeDef TemperatureSenser; /*�¶ȴ�����*/

VoltageLevel_TypeDef InputSignal_Flag;

/*���Ʋ���*/
PID_ControlParameters_TypeDef PID_SolenoidA_Current; /*PID���Ʋ���*/
PID_ControlParameters_TypeDef PID_SolenoidB_Current; /*PID���Ʋ���*/
PID_ControlParameters_TypeDef PID_MainValve_Position; /*PID���Ʋ���*/


int32_t Init_PWM_duty_radio=3100;	//3100=31%
int32_t Init_Solenoid_Current=2000;	//mA
int32_t PWM_Period=36000;//500;//14400~5kHz,36000~2kHz;
int32_t Supply_Voltage=24;//����������ѹ

/* ---------------------------------��̬����----------------------------------*/

/* ----------------------------------����-------------------------------------*/
/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ������������ʼ���ض�Һѹ����ϵͳ���������ư�����
** ����˵����XXXXXXXXXXXXXXXXXXXX
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ�½����
** ����ʱ�䣺2015-05-31
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
void ROS_HY_SubElements_Conf(void)
{
	int i;

   	IndexLED_POWER.GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	IndexLED_POWER.GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
	IndexLED_POWER.GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	IndexLED_POWER.GPIOX=GPIOC;
	IndexLED_POWER.IndexLED_State=OFF;
	IndexLED_POWER.Flash_Method=0;
	IndexLED_POWER.Flash_Frequency=0;

	IndexLED_A.GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	IndexLED_A.GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
	IndexLED_A.GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	IndexLED_A.GPIOX=GPIOA;
	IndexLED_A.IndexLED_State=OFF;
	IndexLED_A.Flash_Method=0;
	IndexLED_A.Flash_Frequency=0;

	IndexLED_B.GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	IndexLED_B.GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
	IndexLED_B.GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	IndexLED_B.GPIOX=GPIOA;
	IndexLED_B.IndexLED_State=OFF;
	IndexLED_B.Flash_Method=0;
	IndexLED_B.Flash_Frequency=0;

	IndexLED_Window.GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	IndexLED_Window.GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
	IndexLED_Window.GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	IndexLED_Window.GPIOX=GPIOB;
	IndexLED_Window.IndexLED_State=OFF;
	IndexLED_Window.Flash_Method=0;
	IndexLED_Window.Flash_Frequency=0;

	IndexLED_Err.GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	IndexLED_Err.GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	
	IndexLED_Err.GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	IndexLED_Err.GPIOX=GPIOA;
	IndexLED_Err.IndexLED_State=OFF;
	IndexLED_Err.Flash_Method=0;
	IndexLED_Err.Flash_Frequency=0;

	IndexLED_Dx[0].GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	IndexLED_Dx[0].GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
	IndexLED_Dx[0].GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	IndexLED_Dx[0].GPIOX=GPIOB;
	IndexLED_Dx[0].IndexLED_State=OFF;
	IndexLED_Dx[0].Flash_Method=0;
	IndexLED_Dx[0].Flash_Frequency=0;
	
	IndexLED_Dx[1].GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	IndexLED_Dx[1].GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
	IndexLED_Dx[1].GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	IndexLED_Dx[1].GPIOX=GPIOC;
	IndexLED_Dx[1].IndexLED_State=OFF;
	IndexLED_Dx[1].Flash_Method=0;
	IndexLED_Dx[1].Flash_Frequency=0;	

	IndexLED_Dx[2].GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	IndexLED_Dx[2].GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	
	IndexLED_Dx[2].GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	IndexLED_Dx[2].GPIOX=GPIOC;
	IndexLED_Dx[2].IndexLED_State=OFF;
	IndexLED_Dx[2].Flash_Method=0;
	IndexLED_Dx[2].Flash_Frequency=0;
		
	IndexLED_Dx[3].GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	IndexLED_Dx[3].GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
	IndexLED_Dx[3].GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	IndexLED_Dx[3].GPIOX=GPIOD;
	IndexLED_Dx[3].IndexLED_State=OFF;
	IndexLED_Dx[3].Flash_Method=0;
	IndexLED_Dx[3].Flash_Frequency=0;	

	IndexLED_Dx[4].GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	IndexLED_Dx[4].GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
	IndexLED_Dx[4].GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	IndexLED_Dx[4].GPIOX=GPIOB;
	IndexLED_Dx[4].IndexLED_State=OFF;
	IndexLED_Dx[4].Flash_Method=0;
	IndexLED_Dx[4].Flash_Frequency=0;	
	
	Buzzer_Alarm.GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	Buzzer_Alarm.GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
	Buzzer_Alarm.GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	Buzzer_Alarm.GPIOX=GPIOB;
	Buzzer_Alarm.Buzzer_State=OFF;
	Buzzer_Alarm.Buzz_Method=0;
	Buzzer_Alarm.Buzz_Frequency=0;

	SolenoidA.GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	SolenoidA.GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
	SolenoidA.GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	SolenoidA.GPIOX=GPIOC;
	SolenoidA.PropertionalSolenoid_State=0;
	SolenoidA.Input_PWM_duty_radio=0;
	SolenoidA.Reference_Current=0;
	SolenoidA.Real_Current=0;
	SolenoidA.UpEdge_Current=0;
	SolenoidA.DownEdge_Current=0;
	SolenoidA.Inductance=0;
	SolenoidA.Resistance=2.8;
	SolenoidA.Core_Location=0;
	SolenoidA.Temperature=0;
	SolenoidA.Flag=1;
	SolenoidA.Index=1;

	SolenoidB.GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	SolenoidB.GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
	SolenoidB.GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	SolenoidB.GPIOX=GPIOC;
	SolenoidB.PropertionalSolenoid_State=0;
	SolenoidB.Input_PWM_duty_radio=0;
	SolenoidB.Reference_Current=0;
	SolenoidB.Real_Current=0;
	SolenoidB.UpEdge_Current=0;
	SolenoidB.DownEdge_Current=0;
	SolenoidB.Inductance=0;
	SolenoidB.Resistance=2.8;
	SolenoidB.Core_Location=0;
	SolenoidB.Temperature=0;
	SolenoidB.Flag=0;
	SolenoidB.Index=0;

	PilotValve.Valve_State=0;
	PilotValve.Spool_Position=0;
	PilotValve.PPort_Pressure=0;
	PilotValve.APort_Pressure=0;
	PilotValve.BPort_Pressure=0;
	PilotValve.TPort_Pressure=0;
	PilotValve.AreaGradient=0;

	MainValve.Valve_State=0;
	MainValve.Spool_Position_Ref=0;
	MainValve.Spool_Position_Real=0;
	MainValve.PPort_Pressure=0;
	MainValve.APort_Pressure=0;
	MainValve.BPort_Pressure=0;
	MainValve.TPort_Pressure=0;
	MainValve.AreaGradient=0;

//	MainValve_LVDT.Position=0;

	InputSignal_Flag.GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
	InputSignal_Flag.GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
	InputSignal_Flag.GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	InputSignal_Flag.GPIOX=GPIOB;
	InputSignal_Flag.Voltage_Level=0;

	for(i=0;i<3;i++)
	{
		PressureSenser[i].Pressure=0;	
	};
	PressureSenser[0].Index=5;
	PressureSenser[1].Index=6;
	PressureSenser[2].Index=7;

//	TemperatureSenser.GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//	TemperatureSenser.GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	
//	TemperatureSenser.GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	TemperatureSenser.GPIOX=GPIOC;
//	TemperatureSenser.Temperature=0;

	PID_SolenoidA_Current.Reference=&SolenoidA.Reference_Current;	//�趨�ο�ֵ
	PID_SolenoidA_Current.Real=&SolenoidA.Real_Current;		//��ǰ��ʵֵ
	ControlAlgorithm_PIDParmeters_Init(&PID_SolenoidA_Current);

	PID_SolenoidA_Current.Reference=&SolenoidB.Reference_Current;	//�趨�ο�ֵ
	PID_SolenoidA_Current.Real=&SolenoidB.Real_Current;		//��ǰ��ʵ�
	ControlAlgorithm_PIDParmeters_Init(&PID_SolenoidB_Current);

	PID_MainValve_Position.Reference=&MainValve.Spool_Position_Ref;	//�趨�ο�ֵ
	PID_MainValve_Position.Real=&MainValve.Spool_Position_Real;		//��ǰ��ʵֵ
	ControlAlgorithm_PIDParmeters_Init(&PID_MainValve_Position);
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ������������ʼ���ض�Һѹ����ϵͳ���������ư�����
** ����˵����XXXXXXXXXXXXXXXXXXXX
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ�½����
** ����ʱ�䣺2015-05-31
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
void ROS_HY_System_Conf(void)
{ 	
	/*STM32����оƬ����(�жϼ���ʱ,IO��,PWM��)*/																	
	ROS_HY_Init_STM32();

	/*��������ӿ��������ó�ʼ��*/
	ROS_HY_SubElements_Conf();	//ϵͳ��������
	ROS_HY_Init_SubElements();	//ϵͳ������ʼ��
//	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_POWER);
//	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_A);
//	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_B);	
//	Buzzer_Init(RCC_APB2Periph_GPIOB,&Buzzer_Alarm);
//	PropertionalSolenoid_Init(RCC_APB2Periph_GPIOC,&SolenoidB);
//	PropertionalSolenoid_Init(RCC_APB2Periph_GPIOC,&SolenoidA);
	
	/*ͨ�Žӿڳ�ʼ��*/
	ROS_HY_Init_Communication();

	/*�������оƬ����*/
	ROS_HY_Init_PeriphChip();

	/*�����־�ļ�����*/
	ROS_HY_Init_Log();

	/*�ⲿ���߽ӿڼ��*/
	SubElements_IOLevel_Acquisition(&InputSignal_Flag);
};



