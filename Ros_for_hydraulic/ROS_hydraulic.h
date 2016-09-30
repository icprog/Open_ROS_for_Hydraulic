/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**						     ROS_hydraulic.h
**
** 				 		       ZJU - 2015
**
** 系统介绍：
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic.h
** 模 块 名：用于定义液压系统中用到的结构体
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
#ifndef __ROS_hydraulic__
#define __ROS_hydraulic__
/* ------------------------------头文件包含-----------------------------------*/
#include "stm32f10x.h"
#include "stm32_eval.h"
//#include "I2C.h"
#include <stdio.h>
//#include "PWM_config.h"
//#include "PID.h"
//#include "IO.h"
#include "Time_test.h"
/* --------------------------------宏指令-------------------------------------*/
#define NCU_ROS_DEBUG 1					 //调试程序
#define NCU_ROS_ENABLE 1		 //机器人操作系统使能
#define UCOSII_ROS_ENABLE 1	 	 //UCOSII操作系统使能

#define ON TRUE	 	 //开状态
#define OFF FALSE	 	 //关状态
/* ------------------------------结构体定义-----------------------------------*/
/*指示灯I/O口*/
//typedef struct	   
//{
//	uint8_t IndexLED_GPIO;
//}IndexLED_InitTypeDef;
/*指示灯*/
typedef struct
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef* GPIOX;

	bool IndexLED_State;
	uint8_t Flash_Method;
	uint32_t Flash_Frequency;
}IndexLED_TypeDef;

/*蜂鸣器I/O口*/
//typedef struct
//{
//	uint8_t Buzzer_GPIO;
//}Buzzer_InitTypeDef;
/*蜂鸣器*/
typedef struct
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef* GPIOX;
	bool Buzzer_State;
	uint8_t Buzz_Method;
	uint32_t Buzz_Frequency;
}Buzzer_TypeDef;
/*比例电磁铁I/O口*/
//typedef struct
//{
//	uint8_t PropertionalSolenoid_GPIO;
//}PropertionalSolenoid_InitTypeDef;
/*比例电磁铁*/
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

/*先导阀体*/
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

/*主阀体*/
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

/*LVDT位移传感器I/O口*/
//typedef struct
//{
//	uint8_t LVDT_Position_GPIO;
//}LVDT_PositionSenser_InitTypeDef;
/*LVDT位移传感器*/
typedef struct
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_TypeDef*  GPIOX;
	int32_t Position;
}LVDT_PositionSenser_TypeDef;

/*压力传感器I/O口*/
//typedef struct
//{
//	uint8_t PressureSenser_GPIO;
//}PressureSenser_InitTypeDef;
/*压力传感器*/
typedef struct
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_TypeDef* GPIOX;
	uint32_t Pressure;
   	uint8_t Index;
}PressureSenser_TypeDef;

/*温度传感器I/O口*/
//typedef struct
//{
//	uint8_t TemperatureSenser_GPIO;
//}TemperatureSenser_InitTypeDef;
/*温度传感器*/
typedef struct
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef*  GPIOX;
	uint32_t Temperature;
}TemperatureSenser_TypeDef;

/*电压信号检测型传感器*/
typedef struct
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef*  GPIOX;
	uint32_t Voltage;
}VoltageSenser_TypeDef;

/*电平信号检测型接口*/
typedef struct
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_TypeDef*  GPIOX;
	uint8_t Voltage_Level;
}VoltageLevel_TypeDef;


/*PID控制算法*/
typedef struct
{
	int32_t	*Reference;	//设定参考值
	int32_t	*Real;		//当前真实值
	
	float	KP;			//比例常数
	float	KI;			//积分常数
	float	KD;			//微分常数

	int32_t Error;		 //当前误差
	int32_t	LastError;   // Error[-1]  前一拍误差
	int32_t PreError;    // Error[-2]  前两拍误差
	int32_t	SumError;	 //总偏差之和
	int32_t	DError;		 //偏差微分
		
	int32_t	KP_error;
	int32_t KI_error;
	int32_t KD_error;
	         
	float	Output;
}PID_ControlParameters_TypeDef;

/*数据表定义*/
typedef struct
{
	int32_t X[100];	 //从小到大
	int32_t Y[100];	 //从小到大
	int32_t Z[100][100];
}Mesh_TypeDef;

/*Kalmanfilter结构体定义，二阶*/
typedef struct
{
	int32_t X[2];	 //从小到大
	int32_t P[2][2];	 //从小到大
}Kalmanfilter_TypeDef;

/* ------------------------------全局变量-----------------------------------*/


#endif




