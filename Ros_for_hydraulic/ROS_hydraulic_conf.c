/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**						     ROS_hydraulic_conf.c
**
** 				 		       ZJU - 2015
**
** ÏµÍ³½éÉÜ£º
**			 
** ÏµÍ³ËµÃ÷£º
**
** ÎÄ ¼þ Ãû£ºROS_hydraulic_conf.h
** Ä£ ¿é Ãû£ºÓÃÓÚÅäÖÃÌØ¶¨ÒºÑ¹ÏµÍ³ÖÐµÄ¿ØÖÆÓ²¼þ½á¹¹¼°Æ÷¼þÈ«¾Ö±äÁ¿²¢¸³³õÖµ
** ¹¦ÄÜÃèÊö£ºxxxxxxxxxxxxxxxx
** ÆäËûËµÃ÷£º
**
** ´´ ½¨ ÈË£ºÂ½ÕñÓî
** ´´½¨Ê±¼ä£º2015-05-31
** ----------------------------------------------------------------------------
** ÐÞ ¸Ä ÈË£ºÂ½ÕñÓî
** ÐÞ¸ÄÊ±¼ä£º2015-05-31
** ÐÞ¸ÄËµÃ÷£º
** ----------------------------------------------------------------------------
** ÐÞ ¸Ä ÈË£ºÂ½ÕñÓî
** ÐÞ¸ÄÊ±¼ä£º2015-05-31
** ÐÞ¸ÄËµÃ÷£º
** ----------------------------------------------------------------------------
*******************************************************************************/	
/* ------------------------------Í·ÎÄ¼þ°üº¬-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* --------------------------------ºêÖ¸Áî-------------------------------------*/

/* ---------------------------------È«¾Ö±äÁ¿----------------------------------*/

/*ÎïÀíÆ÷¼þ*/
IndexLED_TypeDef IndexLED_POWER;	/*¹©µçÖ¸Ê¾µÆ*/
IndexLED_TypeDef IndexLED_A;	/*Aµç´ÅÌúÉÏµçÖ¸Ê¾µÆ*/
IndexLED_TypeDef IndexLED_B;	/*Bµç´ÅÌúÉÏµçÖ¸Ê¾µÆ*/
IndexLED_TypeDef IndexLED_Window;	/*¿ØÖÆÆ«²î ¡Ý ÇøÓò£¨»ÆÉ«£©*/
IndexLED_TypeDef IndexLED_Err;	/*³ö´íÖ¸Ê¾*/
IndexLED_TypeDef IndexLED_Dx[5];  /*¶þ½øÖÆÊý×ÖÖ¸Ê¾*/

Buzzer_TypeDef Buzzer_Alarm;	/*·äÃùÆ÷*/

PropertionalSolenoid_TypeDef SolenoidA;	/*±ÈÀýµç´ÅÌúA*/
PropertionalSolenoid_TypeDef SolenoidB;	/*±ÈÀýµç´ÅÌúB*/

PilotValve_TypeDef PilotValve;	/*ÏÈµ¼·§Ìå*/
MainValve_TypeDef MainValve;	/*Ö÷·§Ìå*/
//LVDT_PositionSenser_TypeDef  MainValve_LVDT;
PressureSenser_TypeDef PressureSenser[3]; /*Ñ¹Á¦´«¸ÐÆ÷*/

//TemperatureSenser_TypeDef TemperatureSenser; /*ÎÂ¶È´«¸ÐÆ÷*/

VoltageLevel_TypeDef InputSignal_Flag;

/*¿ØÖÆ²ÎÊý*/
PID_ControlParameters_TypeDef PID_SolenoidA_Current; /*PID¿ØÖÆ²ÎÊý*/
PID_ControlParameters_TypeDef PID_SolenoidB_Current; /*PID¿ØÖÆ²ÎÊý*/
PID_ControlParameters_TypeDef PID_MainValve_Position; /*PID¿ØÖÆ²ÎÊý*/


int32_t Init_PWM_duty_radio=3100;	//3100=31%
int32_t Init_Solenoid_Current=2000;	//mA
int32_t PWM_Period=36000;//500;//14400~5kHz,36000~2kHz;
int32_t Supply_Voltage=24;//µç´ÅÌú¹©µçµçÑ¹

/* ---------------------------------¾²Ì¬±äÁ¿----------------------------------*/

/* ----------------------------------º¯Êý-------------------------------------*/
/********************************************************************************
** º¯ Êý Ãû£ºXXXXXXXXXXX
** ¹¦ÄÜÃèÊö£º³õÊ¼»¯ÌØ¶¨ÒºÑ¹¿ØÖÆÏµÍ³Æ÷¼þ¼°¿ØÖÆ°åÆ÷¼þ
** ÆäËûËµÃ÷£ºXXXXXXXXXXXXXXXXXXXX
** È«¾Ö±äÁ¿£º
** µ÷ÓÃº¯Êý£º
** Èë¿Ú²ÎÊý£º
** ³ö¿Ú²ÎÊý£º
**
** ×÷    Õß£ºÂ½ÕñÓî
** ´´½¨Ê±¼ä£º2015-05-31
** -------------------------------------------------------------------------------
** ÐÞ ¸Ä ÈË£º
** ÐÞ¸ÄÊ±¼ä£º
** ÐÞ¸ÄËµÃ÷£º
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

	PID_SolenoidA_Current.Reference=&SolenoidA.Reference_Current;	//Éè¶¨²Î¿¼Öµ
	PID_SolenoidA_Current.Real=&SolenoidA.Real_Current;		//µ±Ç°ÕæÊµÖµ
	ControlAlgorithm_PIDParmeters_Init(&PID_SolenoidA_Current);

	PID_SolenoidA_Current.Reference=&SolenoidB.Reference_Current;	//Éè¶¨²Î¿¼Öµ
	PID_SolenoidA_Current.Real=&SolenoidB.Real_Current;		//µ±Ç°ÕæÊµµ
	ControlAlgorithm_PIDParmeters_Init(&PID_SolenoidB_Current);

	PID_MainValve_Position.Reference=&MainValve.Spool_Position_Ref;	//Éè¶¨²Î¿¼Öµ
	PID_MainValve_Position.Real=&MainValve.Spool_Position_Real;		//µ±Ç°ÕæÊµÖµ
	ControlAlgorithm_PIDParmeters_Init(&PID_MainValve_Position);
}

/********************************************************************************
** º¯ Êý Ãû£ºXXXXXXXXXXX
** ¹¦ÄÜÃèÊö£º³õÊ¼»¯ÌØ¶¨ÒºÑ¹¿ØÖÆÏµÍ³Æ÷¼þ¼°¿ØÖÆ°åÆ÷¼þ
** ÆäËûËµÃ÷£ºXXXXXXXXXXXXXXXXXXXX
** È«¾Ö±äÁ¿£º
** µ÷ÓÃº¯Êý£º
** Èë¿Ú²ÎÊý£º
** ³ö¿Ú²ÎÊý£º
**
** ×÷    Õß£ºÂ½ÕñÓî
** ´´½¨Ê±¼ä£º2015-05-31
** -------------------------------------------------------------------------------
** ÐÞ ¸Ä ÈË£º
** ÐÞ¸ÄÊ±¼ä£º
** ÐÞ¸ÄËµÃ÷£º
** -------------------------------------------------------------------------------
**********************************************************************************/
void ROS_HY_System_Conf(void)
{ 	
	/*STM32Ö÷¿ØÐ¾Æ¬ÅäÖÃ(ÖÐ¶Ï¼°¶¨Ê±,IO¿Ú,PWMµÈ)*/																	
	ROS_HY_Init_STM32();

	/*¿ØÖÆÆ÷°å½Ó¿ÚÆ÷¼þÅäÖÃ³õÊ¼»¯*/
	ROS_HY_SubElements_Conf();	//ÏµÍ³Æ÷¼þÅäÖÃ
	ROS_HY_Init_SubElements();	//ÏµÍ³Æ÷¼þ³õÊ¼»¯
//	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_POWER);
//	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_A);
//	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_B);	
//	Buzzer_Init(RCC_APB2Periph_GPIOB,&Buzzer_Alarm);
//	PropertionalSolenoid_Init(RCC_APB2Periph_GPIOC,&SolenoidB);
//	PropertionalSolenoid_Init(RCC_APB2Periph_GPIOC,&SolenoidA);
	
	/*Í¨ÐÅ½Ó¿Ú³õÊ¼»¯*/
	ROS_HY_Init_Communication();

	/*Ïà¹ØÍâÉèÐ¾Æ¬ÅäÖÃ*/
	ROS_HY_Init_PeriphChip();

	/*Ïà¹ØÈÕÖ¾ÎÄ¼þÅäÖÃ*/
	ROS_HY_Init_Log();

	/*Íâ²¿ÌøÏß½Ó¿Ú¼ì²é*/
	SubElements_IOLevel_Acquisition(&InputSignal_Flag);
};



