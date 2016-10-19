/******************* (C) COPYRIGHT 2011 NCU-Roboteam *************************
**               		      NCU_Rotot_OS
**							NCU_ROS_ucosII.c
**
** 				 		南昌大学机器人队 - 2012
**
** 系统介绍：
**			 
** 系统说明：
**
** 文 件 名：NCU_ROS_ucosII.c
** 模 块 名：设置与ucos有关的事件块与任务
** 功能描述：设置与ucos有关的事件块与任务
** 其他说明：
** 创 建 人：陆振宇
** 创建时间：2012-02-19
** ----------------------------------------------------------------------------
** 修 改 人：陆振宇
** 修改时间：2012-02-19
** 修改说明：
** ----------------------------------------------------------------------------
** 修 改 人：陆振宇
** 修改时间：2012-02-19
** 修改说明：
** ----------------------------------------------------------------------------
*******************************************************************************/	

/* ------------------------------头文件包含-----------------------------------*/
#include "includes.h"
#include "NCU_ROS_ucosII.h"
/* --------------------------------宏指令-------------------------------------*/

/* ---------------------------------全局变量----------------------------------*/

/* ---------------------------------静态变量----------------------------------*/

/* --------------------------------uC/OS-II事件定义------------------------------------*/

/*事件标志组Stat_*/

/*依据任务的不同可以设置为不同的位，暂设为16位，即#define OS_FLAGS_NBITS 16*/
/*1为到达，0为没有到达（注意完成后的清除）*/
//OS_FLAG_GRP *Stat_Impl_Task_Xx_Posi;	//执行任务结点到达（以空间任务坐标为准）

/*信号量Sem_*/
//采集执行传感器开关
//OS_EVENT *Sem_Sens_Impl_Enco; //编码器


/*互斥信号量Mute_*/
//定义互斥信号量继承优先级为 #define PIP 10,采集位姿传感器开关
//OS_EVENT *Mute_Sens_Posi_Enco; //编码器

/*消息邮箱Sens_Data_*/
//位姿传感器数据
//OS_EVENT *Mbox_Sens_Data_Posi_Enco; //编码器

/*消息队列Cont_data*/
//机器人位姿数据
//OS_EVENT *Q_Cont_Data_Posi_Enco; //编码器位姿队列

//void *QMsg_Cont_Data_Posi_Enco[3]; //编码器位姿队列消息指针

/*内存管理块 Map_;Task_*/
//OS_MEM *Map_Mem;
//float Map[1][1];
//Map[n][k]=1为x=n、y=k处可通行，Map[n][k]=0为不可通行，Map[n][k]=2为坡道
//Map_Track[n][6]为跟踪轨迹，5个单元分别为坐标x,y,sida,控制方式，速度，点更新方式
//Task[k][4]，k为任务序号，4个单元分加为x,y,z坐标，以及执行状态

/* --------------------------------uC/OS-II任务堆栈空间------------------------------------*/
static OS_STK	OS_Task_Start_STK[OS_TASK_START_STK_SIZE];					  			
static OS_STK   OS_Task_MonitorDiagnose_STK[OS_TASK_MonitorDiagnose_STK_SIZE]; 
static OS_STK   OS_Task_ControlLawSwitch_STK[OS_TASK_ControlLawSwitch_STK_SIZE]; 
static OS_STK   OS_Task_ParameterCalibrationTuning_STK[OS_TASK_ParameterCalibrationTuning_STK_SIZE]; 
static OS_STK   OS_Task_Log_STK[OS_TASK_Log_STK_SIZE]; 
static OS_STK   OS_Task_Communication_STK[OS_TASK_Communication_STK_SIZE];
 
                       							     
/* ------------------------------函数原型声明---------------------------------*/

/********************************************************************************
** 函 数 名：void Robot_OS_Event_Create(void)
** 功能描述：uC/OS-II事件创建
** 其他说明：
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：陆振宇
** 创建时间：2012-02-19
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
void Robot_OS_Event_Create(void)
{
	/*事件标志组Stat_*/
//	INT8U err;
//	Stat_Impl_Task_Xx_Posi=OSFlagCreate(0x0000,&err); //创建执行任务结点到达标志
	
	/*信号量Sem_*/
//	Sem_Sens_Impl_Enco=OSSemCreate(0);

	/*互斥信号量Mute_*/
//	Mute_Sens_Posi_Enco=OSMutexCreate(PIP,&err);

    /*消息邮箱Sens_Data_*/
	//位姿传感器数据
//	Mbox_Sens_Data_Posi_Enco=OSMboxCreate((void*)0);

	
	/*消息队列Cont_data*/
	//机器人位姿数据
//	Q_Cont_Data_Posi_Enco=OSQCreate(&QMsg_Cont_Data_Posi_Enco[0],3);
	
	/*内存管理块 Map_;Task_*/
//	Map_Mem=OSMemCreate(&Map[1][1],1,1,&err);
}
/********************************************************************************
** 函 数 名：int Robot_OS_Main(void)
** 功能描述： 系统Main函数
** 其他说明：
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：陆振宇
** 创建时间：2012-02-19
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
int Robot_OS_Main(void)
{
	uint8_t  os_err;	
/*
 * 注意: 此时MCU已在启动文件startup_stm32f10x_xx.s中通过调用system_stm32f10x.c
 * 中的SystemInit()函数对CPU时钟和总线时钟进行了初始化，如需改动初始时钟配置
 * 请到system_stm32f10x.c文件的相应处修改。
 */
 	
	/* 关闭所有中断 */
	BSP_IntDisAll();
	
	/* 初始化操作系统 */
	OSInit();
	
	/* 创建系统启动任务 */
	os_err = OSTaskCreateExt((void (*)(void *)) OS_Task_Start,
	                         (void          * ) 0,
	                         (OS_STK        * )&OS_Task_Start_STK[OS_TASK_START_STK_SIZE - 1],
	                         (uint8_t         ) OS_TASK_START_PRIO,
	                         (uint16_t        ) OS_TASK_START_PRIO,
	                         (OS_STK        * )&OS_Task_Start_STK[0],
	                         (uint32_t        ) OS_TASK_START_STK_SIZE,
	                         (void          * )0,
	                         (uint16_t        )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
	
#if (OS_TASK_NAME_SIZE >= 11)
	OSTaskNameSet(OS_TASK_START_PRIO, (uint8_t *)"Start Task", &os_err);
#endif
	
	/* 启动操作系统。注意启动操作系统前必须创建至少一个任务 */
	OSStart();
	return (0);
}

/********************************************************************************
**                          Rtask_TaskStart 任务
**
** 任务功能：启动任务
** 任务说明：启动整个系统，并进行系统初始化和创建系统的必要任务和事件
** 系统资源：
**
** 创 建 人：陆振宇
** 创建时间：2012-03-26
** ------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_Start(void *P_arg)
{			   
	(void)P_arg;

	/* 基本硬件的初始化 */
//	ROS_HY_System_Conf(); //此函数不能放在uCOS操作系统中运行，否则不成功
	
	/* 配置系统节拍定时器 */
  	BSP_SysTickConfig(); 

	/* 如果使能了统计任务则初始化统计任务 */
#if (OS_TASK_STAT_EN > 0)
  	OSStatInit();
#endif
	
	/* 创建所有事件和用户任务 */
   	Robot_OS_Event_Create();
  	Robot_OS_Tasks_Create();
  
#ifdef DEBUG
  	printf("\rRtask_Task        : start!\n");
#endif	    
  /* 删除自己 */
  	OSTaskDel(OS_PRIO_SELF);

}
/********************************************************************************
** 函 数 名：Robot_OS_Tasks_Create()
** 功能描述：创建所有用户任务
** 其他说明：
** 创建任务： 
**           
** 调用函数：OSTaskCreateExt, OSTaskNameSet
** 入口参数：
** 出口参数：
**
** 作    者：陆振宇
** 创建时间：2011-04-17
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
static void Robot_OS_Tasks_Create(void)
{
  uint8_t  os_err;
//	/* 创建人监测与诊断口任务，优先级为(OS_LOWEST_PRIO - 10) */
//  	os_err = OSTaskCreateExt((void (*)(void *)) OS_Task_MonitorDiagnose,
//                           (void          * ) 0,
//                           (OS_STK        * )&OS_Task_MonitorDiagnose_STK[OS_TASK_MonitorDiagnose_STK_SIZE-1],
//                           (uint8_t         ) OS_TASK_MonitorDiagnose_PRIO ,
//                           (uint16_t        ) OS_TASK_MonitorDiagnose_PRIO,
//                           (OS_STK        * )&OS_Task_MonitorDiagnose_STK[0],
//                           (uint32_t        ) OS_TASK_MonitorDiagnose_STK_SIZE,
//                           (void          * ) 0,
//                           (uint16_t        )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
//
//#if (OS_TASK_NAME_SIZE >= 13)
//	OSTaskNameSet(RTASK_KEYBOARD_PRIO, "KeyBoard Task", &os_err);
//#endif
//	/* 创建控制策略调整与切换任务，优先级为(OS_LOWEST_PRIO - 10) */
//  	os_err = OSTaskCreateExt((void (*)(void *)) OS_Task_ControlLawSwitch,
//                           (void          * ) 0,
//                           (OS_STK        * )&OS_Task_ControlLawSwitch_STK[OS_TASK_ControlLawSwitch_STK_SIZE-1],
//                           (uint8_t         ) OS_TASK_ControlLawSwitch_PRIO ,
//                           (uint16_t        ) OS_TASK_ControlLawSwitch_PRIO,
//                           (OS_STK        * )&OS_Task_ControlLawSwitch_STK[0],
//                           (uint32_t        ) OS_TASK_ControlLawSwitch_STK_SIZE,
//                           (void          * ) 0,
//                           (uint16_t        )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
//
//#if (OS_TASK_NAME_SIZE >= 13)
//	OSTaskNameSet(RTASK_KEYBOARD_PRIO, "KeyBoard Task", &os_err);
//#endif
	/* 创建参数标定任务，优先级为(OS_LOWEST_PRIO - 10) */
  	os_err = OSTaskCreateExt((void (*)(void *)) OS_Task_ParameterCalibrationTuning,
                           (void          * ) 0,
                           (OS_STK        * )&OS_Task_ParameterCalibrationTuning_STK[OS_TASK_ParameterCalibrationTuning_STK_SIZE-1],
                           (uint8_t         ) OS_TASK_ParameterCalibrationTuning_PRIO ,
                           (uint16_t        ) OS_TASK_ParameterCalibrationTuning_PRIO,
                           (OS_STK        * )&OS_Task_ParameterCalibrationTuning_STK[0],
                           (uint32_t        ) OS_TASK_ParameterCalibrationTuning_STK_SIZE,
                           (void          * ) 0,
                           (uint16_t        )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

#if (OS_TASK_NAME_SIZE >= 13)
	OSTaskNameSet(RTASK_KEYBOARD_PRIO, "KeyBoard Task", &os_err);
#endif
//	/* 创建日志记录任务，优先级为(OS_LOWEST_PRIO - 10) */
//  	os_err = OSTaskCreateExt((void (*)(void *)) OS_Task_Log,
//                           (void          * ) 0,
//                           (OS_STK        * )&OS_Task_Log_STK[OS_TASK_Log_STK_SIZE-1],
//                           (uint8_t         ) OS_TASK_Log_PRIO ,
//                           (uint16_t        ) OS_TASK_Log_PRIO,
//                           (OS_STK        * )&OS_Task_Log_STK[0],
//                           (uint32_t        ) OS_TASK_Log_STK_SIZE,
//                           (void          * ) 0,
//                           (uint16_t        )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
//
//#if (OS_TASK_NAME_SIZE >= 13)
//	OSTaskNameSet(RTASK_KEYBOARD_PRIO, "KeyBoard Task", &os_err);
//#endif
	/* 创建通信任务，优先级为(OS_LOWEST_PRIO - 10) */
  	os_err = OSTaskCreateExt((void (*)(void *)) OS_Task_Communication,
                           (void          * ) 0,
                           (OS_STK        * )&OS_Task_Communication_STK[OS_TASK_Communication_STK_SIZE-1],
                           (uint8_t         ) OS_TASK_Communication_PRIO ,
                           (uint16_t        ) OS_TASK_Communication_PRIO,
                           (OS_STK        * )&OS_Task_Communication_STK[0],
                           (uint32_t        ) OS_TASK_Communication_STK_SIZE,
                           (void          * ) 0,
                           (uint16_t        )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

#if (OS_TASK_NAME_SIZE >= 13)
	OSTaskNameSet(RTASK_KEYBOARD_PRIO, "KeyBoard Task", &os_err);
#endif
}

/********************************************************************************
**                          OS_Task_MonitorDiagnose 任务
**
** 任务功能：监测与诊断任务
** 任务说明：监测与诊断任务
** 系统资源：
**
** 创 建 人：陆振宇
** 创建时间：2012-03-26
** ------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_MonitorDiagnose(void *P_arg)
{
	/* 变量定义 */
	uint8_t err;
	(void)P_arg;
		
	/* 超级循环*/
	while (DEF_TRUE)
	{
//		OSSchedLock();
//		#if (NCU_ROS_DEBUG>0)
//			printf("MonitorDiagnose      : start!\n");
//		#endif
    	OS_CPU_SR  cpu_sr;
		OS_ENTER_CRITICAL();
		SubElements_IndexLED_Output(!IndexLED_Dx[3].IndexLED_State,&IndexLED_Dx[3]);
//		printf("MonitorDiagnose: start!\n");
		OS_EXIT_CRITICAL(); 
//		OSSchedUnlock();
		OSTimeDlyHMSM(0, 0, 0, 1000);
	
	};	
}

/********************************************************************************
**                          OS_Task_ControlLawSwitch 任务
**
** 任务功能：控制策略调整与切换
** 任务说明：控制策略调整与切换
** 系统资源：
**
** 创 建 人：陆振宇
** 创建时间：2012-03-26
** ------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_ControlLawSwitch(void *P_arg)
{
	/* 变量定义 */
	uint8_t err;
	(void)P_arg;
		
	/* 超级循环*/
	while (DEF_TRUE)
	{
//		OSSchedLock();
    	OS_CPU_SR  cpu_sr;
		OS_ENTER_CRITICAL();
//		#if (NCU_ROS_DEBUG>0)
//			printf("ControlLawSwitch: start!\n");
//		#endif
		SubElements_IndexLED_Output(!IndexLED_Dx[4].IndexLED_State,&IndexLED_Dx[4]);
//		OSSchedUnlock();
		OS_EXIT_CRITICAL(); 
		OSTimeDlyHMSM(0, 0, 0,500);	
	};	
}

/********************************************************************************
**                          OS_Task_ParameterCalibrationTuning 任务
**
** 任务功能：智能参数标定与控制参数自整定
** 任务说明：智能参数标定与控制参数自整定
** 系统资源：
**
** 创 建 人：陆振宇
** 创建时间：2012-03-26
** ------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_ParameterCalibrationTuning(void *P_arg)
{
	/* 变量定义 */
	uint8_t err;
	int PWM_Duty_Step=1;

	//继电反馈PID自整定相关变量
	int Relay_Enable=1;//继电控制使能
	int Relay_Done=0;//继电控制参数辨识完成
	int32_t Relay_Amp_Up=0;//继电输出上限
	int32_t Relay_Amp_Down=0;//继电输出下限
	int Relay_Period_Flag=0;//继电周期标记，分为0周期与1周期，以作稳定判断
	int Relay_Flag=0;//继电输出位置标记
	int Pre_Relay_Flag=0;//继电输出位置标记
	int Relay=0; //继电输出位置
	int Pre_Relay=0; //上一刻继电输出位置
	int32_t Solenoid_Current_Peak[2]={0,0};//继电控制电磁铁电流上限值
	int32_t Solenoid_Current_Valley[2]={1500,1500};//继电控制电磁铁电流下限值
	int32_t Solenoid_Current_Peak2Peak[2]={0,0};//继电控制电磁铁电流峰峰值
	int32_t Pre_Solenoid_Current_Peak2Peak[2]={0,0};//继电控制电磁铁电流上时刻峰峰值
	int32_t Time_Solenoid_Current_ZCrossing=0;//继电控制电磁铁电流上限值时刻
	int32_t Pre_Time_Solenoid_Current_ZCrossing=0;//继电控制电磁铁电流上时刻上限值时刻
	int32_t Relay_Tu=0;
	int32_t Relay_Ku=0;
	int32_t Relay_d=0;
	int32_t Relay_a=0;
	//电流环PID优化整定
	int32_t PID_Tuning_Object=0;
	int32_t PID_Tuning_Time;

	(void)P_arg;		
	/* 超级循环*/

	while (DEF_TRUE)
	{
//		#if (NCU_ROS_DEBUG>0)
//			printf("ParameterCalibrationTuning      : start!\n");
//		#endif
		SubElements_IndexLED_Output(!IndexLED_Dx[2].IndexLED_State,&IndexLED_Dx[2]);
	   	/*读取命令字符串*/
		if (Flag_New_Receive_Data==1)
		{
			sscanf(RecieveDataBuffer,"%[^_]_%[^_]_%[^@]@%d",Comm_Working_Mode,Comm_Function_Type,Comm_Parameter_Name,&Comm_Parameter_Value);
			Flag_New_Receive_Data=0;
			printf("%s@_@%s@_@%s@_@%d\n",Comm_Working_Mode,Comm_Function_Type,Comm_Parameter_Name,Comm_Parameter_Value);
		}

		/*作变PWM信号的电磁铁阶跃实验*/
		if ((strcmp(Comm_Working_Mode, "DE")==0) && (strcmp(Comm_Function_Type,"SE")==0) && (strcmp(Comm_Parameter_Name,"SPST")==0))
		{
//		 	SubElements_PropertionalSolenoid_PWM_Control(500*PWM_Duty_Step,PWM_Period,&SolenoidB);//接了电磁铁
			SolenoidA.Input_PWM_duty_radio=500*PWM_Duty_Step;
			OSTimeDlyHMSM(0, 0, 0, 1000);//阶跃沿时时间,1秒钟
//			SubElements_PropertionalSolenoid_PWM_Control(0,PWM_Period,&SolenoidB);//接了电磁铁
			SolenoidA.Input_PWM_duty_radio=0;
			OSTimeDlyHMSM(0, 0, 0, 1000);//PWM输出0沿时时间,1秒钟
			PWM_Duty_Step++;
			if(PWM_Duty_Step>=20)
			{
			 	PWM_Duty_Step=0;
				sprintf(Comm_Working_Mode,"RE");		
			};
			//记录稳态电流值到占空比-电流特征表 
		}

		/*电流环PID自动整定*/
  		else if ((strcmp(Comm_Working_Mode, "ST")==0) && (strcmp(Comm_Function_Type,"SE")==0) && (strcmp(Comm_Parameter_Name,"SPID")==0))
		{
			/*继电反馈控制*/
			if(Relay_Enable==1)
			{
				//反馈控制
				SolenoidA.Reference_Current=1500;//继电参考控制电流为1.5A,可根据电流特征表自动赋值
				if ((SolenoidA.Reference_Current-SolenoidA.Real_Current)>0)
				{
					SolenoidA.Input_PWM_duty_radio=Relay_Amp_Up;//Relay_Amp_Up对应的电1.5A电流占空比上限
					Pre_Relay=Relay; //上一刻继电输出位置
					Relay=1; //继电输出位置
					if ((Relay-Pre_Relay)!=0)
					{
						Pre_Relay_Flag=Relay_Flag;
						Relay_Flag=Relay-Pre_Relay;//2
						if (Relay_Period_Flag==0)Relay_Period_Flag=1;//标记继电周期标志
						else Relay_Period_Flag=0;
						Pre_Time_Solenoid_Current_ZCrossing=Time_Solenoid_Current_ZCrossing;
						Time_Solenoid_Current_ZCrossing=OSTimeGet();//记录Time_Solenoid_Current_ZCrossing,单位ms				
					};
				}
				else
				{
					SolenoidA.Input_PWM_duty_radio=Relay_Amp_Down;//Relay_Amp_Down对应的电1.5A电流占空比下限
					Pre_Relay=Relay; //上一刻继电输出位置
					Relay=-1; //继电输出位置
					if ((Relay-Pre_Relay)!=0)
					{
						Pre_Relay_Flag=Relay_Flag;
						Relay_Flag=Relay-Pre_Relay;//-2
						//记录Time_Solenoid_Current_ZCrossing				
					};
				};
				//判断继电控制到达稳定条件及其峰值与周期统计，采用过零时刻判断
				switch (Relay_Flag)
				{
					case 2://继电器输出处于正位置
						{
							if (SolenoidA.Real_Current>Solenoid_Current_Peak[Relay_Period_Flag])
								{
									Solenoid_Current_Peak[Relay_Period_Flag]=SolenoidA.Real_Current;
								};					
						};break;
					case -2://继电器输出处于负位置
						{
							if (SolenoidA.Real_Current<Solenoid_Current_Valley[Relay_Period_Flag])
								{
									Solenoid_Current_Valley[Relay_Period_Flag]=SolenoidA.Real_Current;
								};						
						};break;
					default:break;
				}
				//判断是否达到稳定条件，达到则记录相关数值，并采用Z-N关系式设计电流环初始PID参数
				if((Solenoid_Current_Peak[1]-Solenoid_Current_Peak[0])<0.01*Solenoid_Current_Peak[1])
				{
					Relay_Tu=Time_Solenoid_Current_ZCrossing-Pre_Time_Solenoid_Current_ZCrossing;//单位ms					
					Relay_d=Relay_Amp_Up-Relay_Amp_Down;
					Relay_a=Solenoid_Current_Peak[1]-Solenoid_Current_Valley[1];
					Relay_Ku=4*Relay_d/(PI*Relay_a);
										
					Relay_Enable=0;
					SolenoidA.Input_PWM_duty_radio=0;
					SolenoidB.Input_PWM_duty_radio=0;
					Relay_Done=1;	  
				};
			};
			//电流阶跃控制			
			//给定PID初始参数值(采用继电反馈法确定初始值，程序中需要加入时间量)
			if (Relay_Enable==0 && Relay_Done==1)
			{
				PID_SolenoidA_Current.KP=0.6*Relay_Ku;
				PID_SolenoidA_Current.KI=2*PID_SolenoidA_Current.KP/Relay_Tu;
				PID_SolenoidA_Current.KD=PID_SolenoidA_Current.KP*Relay_Tu/8;
				SubElements_PropertionalSolenoid_Current_PIDTrack(&PID_SolenoidA_Current,&SolenoidA);//控制电磁铁电流到指定值(这个控制循环应在单独的一个任务或中断中完成)
				//目标函数计算
				PID_Tuning_Object=PID_Tuning_Object+PID_Tuning_Time*abs(SolenoidA.Reference_Current-SolenoidA.Real_Current);								
			};



				//电流阶跃特征目标函数值是否满足要求。是：停止自整定，记录PID参数；否：修改PID参数。
					//采用梯度法修改PID参数		
		}

		/*死区电流表征检测*/
//		else if ((strcmp(Comm_Working_Mode, "ST")==0) && (strcmp(Comm_Function_Type,"EL")==0) && (strcmp(Comm_Parameter_Name,"PVDT")==0))
//		{
//			Elements_MainValvePosition_Acquisition(&MainValve);//采集主阀位移信号
//			MainValve->Spool_Position_Real;//采集主阀位移信号
//						
//			SubElements_PropertionalSolenoid_Current_Filter_Acquisition(&SolenoidA); //采集电磁铁电流信号
//			Solenoid->Real_Current;//采集电磁铁电流信号
//			
//			SubElements_PropertionalSolenoid_Current_PIDTrack(&PID_SolenoidA_Current,&SolenoidA);//控制电磁铁电流到指定值(这个控制循环应在单独的一个任务或中断中完成)	
//			SolenoidA->Reference_Current=0;//控制电磁铁电流到指定值

			//判断主阀是否在中位。是：开始标定；否：返回错识或指示。
			//缓慢增大A电磁铁电流值，此时为电流环控制模式
			//观察主阀位移是否超过阈值。是：记录电流数据；否：继续增大电流值。
			//记录电流值到中位P口死区变量PR。
			//控制主阀位移在主阀中位死区设定值，此时为位置环控制模式，并判断电流值稳定
			//缓慢减小A电磁铁电流值，此时为电流环控制模式
			//观察主阀位移是否超过阈值。是：记录电流数据；否：继续减小电流值。
			//记录电流值到中位T口死区变量TR。

			//判断主阀是否在中位。是：开始标定；否：返回错识或指示。
			//缓慢增大B电磁铁电流值，此时为电流环控制模式
			//观察主阀位移是否超过阈值。是：记录电流数据；否：继续增大电流值。
			//记录电流值到中位P口死区变量PL。
			//控制主阀位移在主阀中位死区设定值，此时为位置环控制模式，并判断电流值稳定
			//缓慢减小A电磁铁电流值，此时为电流环控制模式
			//观察主阀位移是否超过阈值。是：记录电流数据；否：继续减小电流值。
			//记录电流值到中位T口死区变量TL。
//		}

		OSTimeDlyHMSM(0, 0, 0, 200);	
	};	
}

/********************************************************************************
**                          OS_Task_Log 任务
**
** 任务功能：日志记录任务
** 任务说明：日志记录任务
** 系统资源：
**
** 创 建 人：陆振宇
** 创建时间：2012-03-26
** ------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_Log(void *P_arg)
{
	/* 变量定义 */
	uint8_t err;
	(void)P_arg;
		
	/* 超级循环*/
	while (DEF_TRUE)
	{
//		#if (NCU_ROS_DEBUG>0)
//			printf("Log     : start!\n");
//		#endif
		SubElements_IndexLED_Output(!IndexLED_Dx[3].IndexLED_State,&IndexLED_Dx[3]);
		OSTimeDlyHMSM(0, 0, 0, 500);	
	};	
}

/********************************************************************************
**                          OS_Task_Communication 任务
**
** 任务功能：通信交互任务
** 任务说明：通信交互任务
** 系统资源：
**
** 创 建 人：陆振宇
** 创建时间：2016-10-10
** ------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_Communication(void *P_arg)
{
	/* 变量定义 */
	uint8_t err;
	(void)P_arg;
		
	/* 超级循环*/
	while (DEF_TRUE)
	{
//		#if (NCU_ROS_DEBUG>0)
//			printf("Communication      : start!\n");
//		#endif
//		printf("R_Data:%s \n",RecieveDataBuffer);
//		printf("R_Data:");
//		Communication_sprintf(RecieveDataBuffer);
//		printf("\n");
//		printf("B_up:%d ",SolenoidB.UpEdge_Current);
//		printf("B_down:%d ",SolenoidB.DownEdge_Current);
//		printf("B_L:%d ",SolenoidB.Inductance);
//		printf("\n ");
		SubElements_IndexLED_Output(!IndexLED_Dx[4].IndexLED_State,&IndexLED_Dx[4]);
		OSTimeDlyHMSM(0, 0, 0, 500);	
	};	
}

