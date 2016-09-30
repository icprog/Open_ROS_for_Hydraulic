/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_SubElements.c
**
** 				 		      ZJU - 2015
**
** 系统介绍：XXXXXXXXXXXXXXXXXXXXXX
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_SubElements.c
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

/* ------------------------------头文件包含-----------------------------------*/
#include "ROS_hydraulic_SubElements.h"
/* --------------------------------宏指令-------------------------------------*/

/* ---------------------------------全局变量----------------------------------*/

/* ---------------------------------静态变量----------------------------------*/

/* ----------------------------------函数-------------------------------------*/

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：XXXXxxxxxxx
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
void PropertionalSolenoid_PWM_Output(int32_t PWM_duty_radio,PropertionalSolenoid_TypeDef *Solenoid)
{
	if(Solenoid->Flag==1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_12);  
	    GPIO_ResetBits(GPIOC,GPIO_Pin_11); 
      	TIM_SetCompare3(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000); //A电磁铁得电
	}
	else if(Solenoid->Flag==0)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare4(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000);//B电磁铁得电
	}
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：XXXXxxxxxxx
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
void PropertionalSolenoid_PWM_Output2(int32_t PWM_duty_radio,PropertionalSolenoid_TypeDef *Solenoid)
{
	if(Solenoid->Flag==1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_12);  
	    GPIO_ResetBits(GPIOC,GPIO_Pin_11); 
      	TIM_SetCompare3(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000); //A电磁铁得电
		TIM_SetCompare4(TIM3,0);
	}
	else if(Solenoid->Flag==0)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare4(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000);//B电磁铁得电
		TIM_SetCompare3(TIM3,0);
	}
	else if (Solenoid->Flag==2)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare4(TIM3,PWM_duty_radio*PWM_Period/10000);	//B电磁铁得电
		TIM_SetCompare3(TIM3,PWM_duty_radio*PWM_Period/10000); 	//A电磁铁得电
	}
}
/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：XXXXxxxxxxx
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
** 函 数 名：XXXXXXXXXXX
** 功能描述：XXXXxxxxxxx
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
** 函 数 名：
** 功能描述：PWM占空比控制电磁铁输出,与定时器硬件相关
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
void SubElements_PropertionalSolenoid_PWM_Control(int32_t PWM_duty_radio,int32_t PWM_Period,PropertionalSolenoid_TypeDef *Solenoid)
{
	switch(Solenoid->Index)
	{
		case 1:
	      	TIM_SetCompare3(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000); //A电磁铁得电
			Solenoid->Input_PWM_duty_radio=PWM_duty_radio;
			break;
		case 0:
			TIM_SetCompare4(TIM3,(int32_t) PWM_duty_radio*PWM_Period/10000); //B电磁铁得电
			Solenoid->Input_PWM_duty_radio=PWM_duty_radio;
			break;
		default: break;	
	}
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：电磁铁电流采集
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
void SubElements_PropertionalSolenoid_Current_Filter_Acquisition(PropertionalSolenoid_TypeDef *Solenoid)
{
	Solenoid->Real_Current = Read_Port(Solenoid->Index)*114/100;   	//单位为mA
}

void SubElements_PropertionalSolenoid_Current_Acquisition(PropertionalSolenoid_TypeDef *Solenoid)
{
	Solenoid->Real_Current = Read_MAX197(Solenoid->Index)*114/100;	 //单位为mA
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：LVDT位移传感器采集
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
//void SubElements_LVDTPosition_Acquisition(int32_t LVDT_Sensor)
//{
//	LVDT_Sensor = Read_Port(4);
//}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：压力传感器采集
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
void SubElements_PressureSensor_Acquisition(PressureSenser_TypeDef* PressureSensor)
{
	PressureSensor->Pressure = Read_Port(PressureSensor->Index);//  PressureSensor->Index=5;6;7
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：压力传感器采集
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
void SubElements_IOLevel_Acquisition(VoltageLevel_TypeDef* Input_IO)
{	
	Input_IO->Voltage_Level=GPIO_ReadInputDataBit(Input_IO->GPIOX, Input_IO->GPIO_InitStructure.GPIO_Pin);//  PressureSensor->Index=5;6;7
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：电磁铁电流控制跟踪
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
void SubElements_PropertionalSolenoid_Current_PIDTrack(PID_ControlParameters_TypeDef* PID_Solenoid)
{
	ControlAlgorithm_PositionPID(PID_Solenoid);			
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：电磁铁电感，即电流导数计算
** 其他说明：需要配合PWM定时发生器进行设置
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
void SubElements_PropertionalSolenoid_GetInductance(PropertionalSolenoid_TypeDef *Solenoid)
{
	int32_t Stable_Current=(Solenoid->DownEdge_Current+Solenoid->UpEdge_Current)/2;	//单位mA
	int32_t delta_Current=Solenoid->DownEdge_Current-Solenoid->UpEdge_Current;	//单位mA
	int32_t delta_Time=0.5*Solenoid->Input_PWM_duty_radio;	//PWM_Period(周期)*Solenoid->Input_PWM_duty_radio; 单位1e-4ms
	float Inductance_Voltage=Supply_Voltage*1000-Stable_Current*Solenoid->Resistance;	//单位mV
	Solenoid->Inductance=Inductance_Voltage*delta_Time/delta_Current/1000; //注意计器数值的获取以便计算时间	单位0.1mH	
}
