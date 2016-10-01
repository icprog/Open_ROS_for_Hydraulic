/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**						     ROS_hydraulic_conf.c
**
** 				 		       ZJU - 2015
**
** 系统介绍：
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_conf.h
** 模 块 名：用于配置特定液压系统中的控制硬件结构及器件全局变量并赋初值
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
/* ------------------------------头文件包含-----------------------------------*/
#include "ROS_hydraulic_conf.h"
/* --------------------------------宏指令-------------------------------------*/

/* ---------------------------------全局变量----------------------------------*/

/*物理器件*/
IndexLED_TypeDef IndexLED_POWER;	/*供电指示灯*/
IndexLED_TypeDef IndexLED_A;	/*A电磁铁上电指示灯*/
IndexLED_TypeDef IndexLED_B;	/*B电磁铁上电指示灯*/
IndexLED_TypeDef IndexLED_Window;	/*控制偏差 ≥ 区域（黄色）*/
IndexLED_TypeDef IndexLED_Err;	/*出错指示*/
IndexLED_TypeDef IndexLED_Dx[5];  /*二进制数字指示*/

Buzzer_TypeDef Buzzer_Alarm;	/*蜂鸣器*/

PropertionalSolenoid_TypeDef SolenoidA;	/*比例电磁铁A*/
PropertionalSolenoid_TypeDef SolenoidB;	/*比例电磁铁B*/

PilotValve_TypeDef PilotValve;	/*先导阀体*/
MainValve_TypeDef MainValve;	/*主阀体*/
//LVDT_PositionSenser_TypeDef  MainValve_LVDT;
PressureSenser_TypeDef PressureSenser[3]; /*压力传感器*/

//TemperatureSenser_TypeDef TemperatureSenser; /*温度传感器*/

VoltageLevel_TypeDef InputSignal_Flag;

/*控制参数*/
PID_ControlParameters_TypeDef PID_SolenoidA_Current; /*PID控制参数*/
PID_ControlParameters_TypeDef PID_SolenoidB_Current; /*PID控制参数*/
PID_ControlParameters_TypeDef PID_MainValve_Position; /*PID控制参数*/


int32_t Init_PWM_duty_radio=3100;	//3100=31%
int32_t Init_Solenoid_Current=2000;	//mA
int32_t PWM_Period=36000;//500;//14400~5kHz,36000~2kHz;
int32_t Supply_Voltage=24;//电磁铁供电电压
/*通信参数*/
char SendDataBuffer[20];//STM32发出数据缓冲
char RecieveDataBuffer[20];//STM32接受数据缓冲


/* ---------------------------------静态变量----------------------------------*/

/* ----------------------------------函数-------------------------------------*/
/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：初始化特定液压控制系统器件及控制板器件
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：陆振宇
** 创建时间：2015-05-31
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
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

	PID_SolenoidA_Current.Reference=&SolenoidA.Reference_Current;	//设定参考值
	PID_SolenoidA_Current.Real=&SolenoidA.Real_Current;		//当前真实值
	ControlAlgorithm_PIDParmeters_Init(&PID_SolenoidA_Current);

	PID_SolenoidA_Current.Reference=&SolenoidB.Reference_Current;	//设定参考值
	PID_SolenoidA_Current.Real=&SolenoidB.Real_Current;		//当前真实�
	ControlAlgorithm_PIDParmeters_Init(&PID_SolenoidB_Current);

	PID_MainValve_Position.Reference=&MainValve.Spool_Position_Ref;	//设定参考值
	PID_MainValve_Position.Real=&MainValve.Spool_Position_Real;		//当前真实值
	ControlAlgorithm_PIDParmeters_Init(&PID_MainValve_Position);
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：初始化特定液压控制系统器件及控制板器件
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：陆振宇
** 创建时间：2015-05-31
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
void ROS_HY_System_Conf(void)
{ 	
	/*STM32主控芯片配置(中断及定时,IO口,PWM等)*/																	
	ROS_HY_Init_STM32();

	/*控制器板接口器件配置初始化*/
	ROS_HY_SubElements_Conf();	//系统器件配置
	ROS_HY_Init_SubElements();	//系统器件初始化
//	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_POWER);
//	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_A);
//	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_B);	
//	Buzzer_Init(RCC_APB2Periph_GPIOB,&Buzzer_Alarm);
//	PropertionalSolenoid_Init(RCC_APB2Periph_GPIOC,&SolenoidB);
//	PropertionalSolenoid_Init(RCC_APB2Periph_GPIOC,&SolenoidA);
	
	/*通信接口初始化*/
	ROS_HY_Init_Communication();

	/*相关外设芯片配置*/
	ROS_HY_Init_PeriphChip();

	/*相关日志文件配置*/
	ROS_HY_Init_Log();

	/*外部跳线接口检查*/
	SubElements_IOLevel_Acquisition(&InputSignal_Flag);
};



