/******************* (C) COPYRIGHT 2011 NCU-Roboteam *************************
**               		      NCU_Rotot_OS
**							 NCU_ROS_ucosII.h
**
** 				 		南昌大学机器人队 - 2012
**
** 系统介绍：
**			 
** 系统说明：
**
** 文 件 名：NCU_ROS_ucosII.h
** 模 块 名：机器人操作系统配置文件
** 功能描述：配置UCOSII的相关变量
** 其他说明：
**
** 创 建 人：陆振宇
** 创建时间：2012-03-23
** ----------------------------------------------------------------------------
** 修 改 人：陆振宇
** 修改时间：2012-03-23
** 修改说明：
** ----------------------------------------------------------------------------
** 修 改 人：陆振宇
** 修改时间：2012-03-23
** 修改说明：
** ----------------------------------------------------------------------------
*******************************************************************************/	
#ifndef __NCU_ROS_ucosII__
#define __NCU_ROS_ucosII__

/* ------------------------------头文件包含-----------------------------------*/
//#include "includes.h"
#include "ucos_ii.h"
#include "NCU_ROS_ucosII_cfg.h"
/* ------------------------------宏定义-----------------------------------*/
/*基本常量*/
//#define PI 3.1415926


/*事件标志组*/

//执行任务结点到达（以空间任务坐标为准）
//#define FlAG_TASK_1_GET 0x0001


/*互斥信号量Mute_*/
//#define PIP 10	//定义互斥信号量继承优先级为 #define PIP 10,


/* ------------------------------结构体定义-----------------------------------*/
//typedef struct	 //位姿结构体
//{
//	float X;
//	float Y;
//	float Sida;
//}ROS_PosiTypeDef;

/* ------------------------------全局变量-----------------------------------*/


/* --------------------------------uC/OS-II事件定义------------------------------------*/

/*事件标志组Stat_*/

/*依据任务的不同可以设置为不同的位，暂设为16位，即#define OS_FLAGS_NBITS 16*/
/*1为到达，0为没有到达（注意完成后的清除）*/
//extern OS_FLAG_GRP *Stat_Impl_Task_Xx_Posi;	//执行任务结点到达（以空间任务坐标为准）


/*消息队列Cont_data*/
//机器人位姿数据
//extern OS_EVENT *Q_Cont_Data_Posi_Enco; //编码器位姿队列


/*内存管理块 Map_;Task_*/
//extern OS_MEM *Map_Mem;
//extern float Map[1][1];

/* --------------------------------uC/OS-II任务堆栈空间------------------------------------*/				  			
//extern static OS_STK  	OS_Task_Manm_Inter_STK[OS_TASK_MANM_INTER_STK_SIZE];                        

/* --------------------------------uC/OS-II任务函数申明------------------------------------*/
int Robot_OS_Main(void);//系统启动Main函数
void Robot_OS_Event_Create(void);// 创建任务事件
void Robot_OS_Tasks_Create(void);//创建所有任务



/*--------------------------------uC/OS-II任务申明------------------------------------*/
/*系统初始*/
void OS_Task_Start(void *P_arg);//系统启动任务
void OS_Task_MonitorDiagnose(void *P_arg);
void OS_Task_ControlLawSwitch(void *P_arg);
void OS_Task_ParameterCalibrationTuning(void *P_arg);
void OS_Task_Log(void *P_arg);
void OS_Task_Communication(void *P_arg);
#endif
