/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_SubElements.c
**
** 				 		      ZJU - 2015
**
** ϵͳ���ܣ�XXXXXXXXXXXXXXXXXXXXXX
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_SubElements.c
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

/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "ROS_hydraulic_SubElements.h"
/* --------------------------------��ָ��-------------------------------------*/

/* ---------------------------------ȫ�ֱ���----------------------------------*/

/* ---------------------------------��̬����----------------------------------*/

/* ----------------------------------����-------------------------------------*/

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������XXXXxxxxxxx
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
void PropertionalSolenoid_PWM_Output(int32_t PWM_duty_radio,PropertionalSolenoid_TypeDef *Solenoid)
{
	if(Solenoid->Flag==1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_12);  
	    GPIO_ResetBits(GPIOC,GPIO_Pin_11); 
      	TIM_SetCompare3(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000); //A������õ�
	}
	else if(Solenoid->Flag==0)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare4(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000);//B������õ�
	}
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������XXXXxxxxxxx
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
void PropertionalSolenoid_PWM_Output2(int32_t PWM_duty_radio,PropertionalSolenoid_TypeDef *Solenoid)
{
	if(Solenoid->Flag==1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_12);  
	    GPIO_ResetBits(GPIOC,GPIO_Pin_11); 
      	TIM_SetCompare3(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000); //A������õ�
		TIM_SetCompare4(TIM3,0);
	}
	else if(Solenoid->Flag==0)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare4(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000);//B������õ�
		TIM_SetCompare3(TIM3,0);
	}
	else if (Solenoid->Flag==2)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare4(TIM3,PWM_duty_radio*PWM_Period/10000);	//B������õ�
		TIM_SetCompare3(TIM3,PWM_duty_radio*PWM_Period/10000); 	//A������õ�
	}
}
/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������XXXXxxxxxxx
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
void SubElements_IndexLED_Output(bool State,IndexLED_TypeDef *LED)
{
	switch(State)
	{
		case ON:
			GPIO_ResetBits(LED->GPIOX,LED->GPIO_InitStructure.GPIO_Pin);
			LED->IndexLED_State=ON; 
			break;
		case OFF:
			GPIO_SetBits(LED->GPIOX,LED->GPIO_InitStructure.GPIO_Pin);
			LED->IndexLED_State=OFF;
			break;
		default: break; 	
	};
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������XXXXxxxxxxx
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
void SubElements_Buzzer_Output(bool State,Buzzer_TypeDef *Buzzer)
{
	switch(State)
	{
		case OFF:
			GPIO_ResetBits(Buzzer->GPIOX,Buzzer->GPIO_InitStructure.GPIO_Pin);
			Buzzer->Buzzer_State=OFF; 
			break;
		case ON:
			GPIO_SetBits(Buzzer->GPIOX,Buzzer->GPIO_InitStructure.GPIO_Pin);
			Buzzer->Buzzer_State=ON;
			break;
		default: break; 	
	};
}

/********************************************************************************
** �� �� ����
** ����������PWMռ�ձȿ��Ƶ�������,�붨ʱ��Ӳ�����
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
void SubElements_PropertionalSolenoid_PWM_Control(int32_t PWM_duty_radio,int32_t PWM_Period,PropertionalSolenoid_TypeDef *Solenoid)
{
	switch(Solenoid->Index)
	{
		case 1:
	      	TIM_SetCompare3(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000); //A������õ�
			Solenoid->Input_PWM_duty_radio=PWM_duty_radio;
			break;
		case 0:
			TIM_SetCompare4(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000); //B������õ�
			Solenoid->Input_PWM_duty_radio=PWM_duty_radio;
			break;
		default: break;	
	}
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ��������������������ɼ�
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
void SubElements_PropertionalSolenoid_Current_Filter_Acquisition(PropertionalSolenoid_TypeDef *Solenoid)
{
	Solenoid->Real_Current = Read_Port(Solenoid->Index)*114/100;   	//��λΪmA
}

void SubElements_PropertionalSolenoid_Current_Acquisition(PropertionalSolenoid_TypeDef *Solenoid)
{
	Solenoid->Real_Current = Read_MAX197(Solenoid->Index)*114/100;	 //��λΪmA
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������LVDTλ�ƴ������ɼ�
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
//void SubElements_LVDTPosition_Acquisition(int32_t LVDT_Sensor)
//{
//	LVDT_Sensor = Read_Port(4);
//}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������ѹ���������ɼ�
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
void SubElements_PressureSensor_Acquisition(PressureSenser_TypeDef* PressureSensor)
{
	PressureSensor->Pressure = Read_Port(PressureSensor->Index);//  PressureSensor->Index=5;6;7
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������ѹ���������ɼ�
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
void SubElements_IOLevel_Acquisition(VoltageLevel_TypeDef* Input_IO)
{	
	Input_IO->Voltage_Level=GPIO_ReadInputDataBit(Input_IO->GPIOX, Input_IO->GPIO_InitStructure.GPIO_Pin);//  PressureSensor->Index=5;6;7
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������������������Ƹ���
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
void SubElements_PropertionalSolenoid_Current_PIDTrack(PID_ControlParameters_TypeDef* PID_Solenoid)
{
	ControlAlgorithm_PositionPID(PID_Solenoid);			
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** �����������������У���������������
** ����˵������Ҫ���PWM��ʱ��������������
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
void SubElements_PropertionalSolenoid_GetInductance(PropertionalSolenoid_TypeDef *Solenoid)
{
	int32_t Stable_Current=(Solenoid->DownEdge_Current+Solenoid->UpEdge_Current)/2;	//��λmA
	int32_t delta_Current=Solenoid->DownEdge_Current-Solenoid->UpEdge_Current;	//��λmA
	int32_t delta_Time=0.5*Solenoid->Input_PWM_duty_radio;	//PWM_Period(����)*Solenoid->Input_PWM_duty_radio; ��λ1e-4ms
	float Inductance_Voltage=Supply_Voltage*1000-Stable_Current*Solenoid->Resistance;	//��λmV
	Solenoid->Inductance=Inductance_Voltage*delta_Time/delta_Current/1000; //ע�������ֵ�Ļ�ȡ�Ա����ʱ��	��λ0.1mH	
}
