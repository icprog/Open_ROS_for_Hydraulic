/******************* (C) COPYRIGHT 2011 NCU-Roboteam *************************
**               		      NCU_Rotot_OS
**							NCU_ROS_ucosII.c
**
** 				 		�ϲ���ѧ�����˶� - 2012
**
** ϵͳ���ܣ�
**			 
** ϵͳ˵����
**
** �� �� ����NCU_ROS_ucosII.c
** ģ �� ����������ucos�йص��¼���������
** ����������������ucos�йص��¼���������
** ����˵����
** �� �� �ˣ�½����
** ����ʱ�䣺2012-02-19
** ----------------------------------------------------------------------------
** �� �� �ˣ�½����
** �޸�ʱ�䣺2012-02-19
** �޸�˵����
** ----------------------------------------------------------------------------
** �� �� �ˣ�½����
** �޸�ʱ�䣺2012-02-19
** �޸�˵����
** ----------------------------------------------------------------------------
*******************************************************************************/	

/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "includes.h"
#include "NCU_ROS_ucosII.h"
/* --------------------------------��ָ��-------------------------------------*/

/* ---------------------------------ȫ�ֱ���----------------------------------*/

/* ---------------------------------��̬����----------------------------------*/

/* --------------------------------uC/OS-II�¼�����------------------------------------*/

/*�¼���־��Stat_*/

/*��������Ĳ�ͬ��������Ϊ��ͬ��λ������Ϊ16λ����#define OS_FLAGS_NBITS 16*/
/*1Ϊ���0Ϊû�е��ע����ɺ�������*/
//OS_FLAG_GRP *Stat_Impl_Task_Xx_Posi;	//ִ�������㵽��Կռ���������Ϊ׼��

/*�ź���Sem_*/
//�ɼ�ִ�д���������
//OS_EVENT *Sem_Sens_Impl_Enco; //������


/*�����ź���Mute_*/
//���廥���ź����̳����ȼ�Ϊ #define PIP 10,�ɼ�λ�˴���������
//OS_EVENT *Mute_Sens_Posi_Enco; //������

/*��Ϣ����Sens_Data_*/
//λ�˴���������
//OS_EVENT *Mbox_Sens_Data_Posi_Enco; //������

/*��Ϣ����Cont_data*/
//������λ������
//OS_EVENT *Q_Cont_Data_Posi_Enco; //������λ�˶���

//void *QMsg_Cont_Data_Posi_Enco[3]; //������λ�˶�����Ϣָ��

/*�ڴ����� Map_;Task_*/
//OS_MEM *Map_Mem;
//float Map[1][1];
//Map[n][k]=1Ϊx=n��y=k����ͨ�У�Map[n][k]=0Ϊ����ͨ�У�Map[n][k]=2Ϊ�µ�
//Map_Track[n][6]Ϊ���ٹ켣��5����Ԫ�ֱ�Ϊ����x,y,sida,���Ʒ�ʽ���ٶȣ�����·�ʽ
//Task[k][4]��kΪ������ţ�4����Ԫ�ּ�Ϊx,y,z���꣬�Լ�ִ��״̬

/* --------------------------------uC/OS-II�����ջ�ռ�------------------------------------*/
static OS_STK	OS_Task_Start_STK[OS_TASK_START_STK_SIZE];					  			
static OS_STK   OS_Task_MonitorDiagnose_STK[OS_TASK_MonitorDiagnose_STK_SIZE]; 
static OS_STK   OS_Task_ControlLawSwitch_STK[OS_TASK_ControlLawSwitch_STK_SIZE]; 
static OS_STK   OS_Task_ParameterCalibrationTuning_STK[OS_TASK_ParameterCalibrationTuning_STK_SIZE]; 
static OS_STK   OS_Task_Log_STK[OS_TASK_Log_STK_SIZE]; 
static OS_STK   OS_Task_Communication_STK[OS_TASK_Communication_STK_SIZE];
 
                       							     
/* ------------------------------����ԭ������---------------------------------*/

/********************************************************************************
** �� �� ����void Robot_OS_Event_Create(void)
** ����������uC/OS-II�¼�����
** ����˵����
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ�½����
** ����ʱ�䣺2012-02-19
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
void Robot_OS_Event_Create(void)
{
	/*�¼���־��Stat_*/
//	INT8U err;
//	Stat_Impl_Task_Xx_Posi=OSFlagCreate(0x0000,&err); //����ִ�������㵽���־
	
	/*�ź���Sem_*/
//	Sem_Sens_Impl_Enco=OSSemCreate(0);

	/*�����ź���Mute_*/
//	Mute_Sens_Posi_Enco=OSMutexCreate(PIP,&err);

    /*��Ϣ����Sens_Data_*/
	//λ�˴���������
//	Mbox_Sens_Data_Posi_Enco=OSMboxCreate((void*)0);

	
	/*��Ϣ����Cont_data*/
	//������λ������
//	Q_Cont_Data_Posi_Enco=OSQCreate(&QMsg_Cont_Data_Posi_Enco[0],3);
	
	/*�ڴ����� Map_;Task_*/
//	Map_Mem=OSMemCreate(&Map[1][1],1,1,&err);
}
/********************************************************************************
** �� �� ����int Robot_OS_Main(void)
** ���������� ϵͳMain����
** ����˵����
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ�½����
** ����ʱ�䣺2012-02-19
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
int Robot_OS_Main(void)
{
	uint8_t  os_err;	
/*
 * ע��: ��ʱMCU���������ļ�startup_stm32f10x_xx.s��ͨ������system_stm32f10x.c
 * �е�SystemInit()������CPUʱ�Ӻ�����ʱ�ӽ����˳�ʼ��������Ķ���ʼʱ������
 * �뵽system_stm32f10x.c�ļ�����Ӧ���޸ġ�
 */
 	
	/* �ر������ж� */
	BSP_IntDisAll();
	
	/* ��ʼ������ϵͳ */
	OSInit();
	
	/* ����ϵͳ�������� */
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
	
	/* ��������ϵͳ��ע����������ϵͳǰ���봴������һ������ */
	OSStart();
	return (0);
}

/********************************************************************************
**                          Rtask_TaskStart ����
**
** �����ܣ���������
** ����˵������������ϵͳ��������ϵͳ��ʼ���ʹ���ϵͳ�ı�Ҫ������¼�
** ϵͳ��Դ��
**
** �� �� �ˣ�½����
** ����ʱ�䣺2012-03-26
** ------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_Start(void *P_arg)
{			   
	(void)P_arg;

	/* ����Ӳ���ĳ�ʼ�� */
//	ROS_HY_System_Conf(); //�˺������ܷ���uCOS����ϵͳ�����У����򲻳ɹ�
	
	/* ����ϵͳ���Ķ�ʱ�� */
  	BSP_SysTickConfig(); 

	/* ���ʹ����ͳ���������ʼ��ͳ������ */
#if (OS_TASK_STAT_EN > 0)
  	OSStatInit();
#endif
	
	/* ���������¼����û����� */
   	Robot_OS_Event_Create();
  	Robot_OS_Tasks_Create();
  
#ifdef DEBUG
  	printf("\rRtask_Task        : start!\n");
#endif	    
  /* ɾ���Լ� */
  	OSTaskDel(OS_PRIO_SELF);

}
/********************************************************************************
** �� �� ����Robot_OS_Tasks_Create()
** �������������������û�����
** ����˵����
** �������� 
**           
** ���ú�����OSTaskCreateExt, OSTaskNameSet
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ�½����
** ����ʱ�䣺2011-04-17
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
static void Robot_OS_Tasks_Create(void)
{
  uint8_t  os_err;
	/* �����˼������Ͽ��������ȼ�Ϊ(OS_LOWEST_PRIO - 10) */
  	os_err = OSTaskCreateExt((void (*)(void *)) OS_Task_MonitorDiagnose,
                           (void          * ) 0,
                           (OS_STK        * )&OS_Task_MonitorDiagnose_STK[OS_TASK_MonitorDiagnose_STK_SIZE-1],
                           (uint8_t         ) OS_TASK_MonitorDiagnose_PRIO ,
                           (uint16_t        ) OS_TASK_MonitorDiagnose_PRIO,
                           (OS_STK        * )&OS_Task_MonitorDiagnose_STK[0],
                           (uint32_t        ) OS_TASK_MonitorDiagnose_STK_SIZE,
                           (void          * ) 0,
                           (uint16_t        )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

#if (OS_TASK_NAME_SIZE >= 13)
	OSTaskNameSet(RTASK_KEYBOARD_PRIO, "KeyBoard Task", &os_err);
#endif
	/* �������Ʋ��Ե������л��������ȼ�Ϊ(OS_LOWEST_PRIO - 10) */
  	os_err = OSTaskCreateExt((void (*)(void *)) OS_Task_ControlLawSwitch,
                           (void          * ) 0,
                           (OS_STK        * )&OS_Task_ControlLawSwitch_STK[OS_TASK_ControlLawSwitch_STK_SIZE-1],
                           (uint8_t         ) OS_TASK_ControlLawSwitch_PRIO ,
                           (uint16_t        ) OS_TASK_ControlLawSwitch_PRIO,
                           (OS_STK        * )&OS_Task_ControlLawSwitch_STK[0],
                           (uint32_t        ) OS_TASK_ControlLawSwitch_STK_SIZE,
                           (void          * ) 0,
                           (uint16_t        )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));

#if (OS_TASK_NAME_SIZE >= 13)
	OSTaskNameSet(RTASK_KEYBOARD_PRIO, "KeyBoard Task", &os_err);
#endif
//	/* ���������궨�������ȼ�Ϊ(OS_LOWEST_PRIO - 10) */
//  	os_err = OSTaskCreateExt((void (*)(void *)) OS_Task_ParameterCalibrationTuning,
//                           (void          * ) 0,
//                           (OS_STK        * )&OS_Task_ParameterCalibrationTuning_STK[OS_TASK_ParameterCalibrationTuning_STK_SIZE],
//                           (uint8_t         ) OS_TASK_ParameterCalibrationTuning_PRIO ,
//                           (uint16_t        ) OS_TASK_ParameterCalibrationTuning_PRIO,
//                           (OS_STK        * )&OS_Task_ParameterCalibrationTuning_STK[0],
//                           (uint32_t        ) OS_TASK_ParameterCalibrationTuning_STK_SIZE,
//                           (void          * ) 0,
//                           (uint16_t        )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
//
//#if (OS_TASK_NAME_SIZE >= 13)
//	OSTaskNameSet(RTASK_KEYBOARD_PRIO, "KeyBoard Task", &os_err);
//#endif
//	/* ������־��¼�������ȼ�Ϊ(OS_LOWEST_PRIO - 10) */
//  	os_err = OSTaskCreateExt((void (*)(void *)) OS_Task_Log,
//                           (void          * ) 0,
//                           (OS_STK        * )&OS_Task_Log_STK[OS_TASK_Log_STK_SIZE],
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
//	/* ����ͨ���������ȼ�Ϊ(OS_LOWEST_PRIO - 10) */
//  	os_err = OSTaskCreateExt((void (*)(void *)) OS_Task_Communication,
//                           (void          * ) 0,
//                           (OS_STK        * )&OS_Task_Communication_STK[OS_TASK_Communication_STK_SIZE],
//                           (uint8_t         ) OS_TASK_Communication_PRIO ,
//                           (uint16_t        ) OS_TASK_Communication_PRIO,
//                           (OS_STK        * )&OS_Task_Communication_STK[0],
//                           (uint32_t        ) OS_TASK_Communication_STK_SIZE,
//                           (void          * ) 0,
//                           (uint16_t        )(OS_TASK_OPT_STK_CLR | OS_TASK_OPT_STK_CHK));
//
//#if (OS_TASK_NAME_SIZE >= 13)
//	OSTaskNameSet(RTASK_KEYBOARD_PRIO, "KeyBoard Task", &os_err);
//#endif
}

/********************************************************************************
**                          OS_Task_MonitorDiagnose ����
**
** �����ܣ�������������
** ����˵����������������
** ϵͳ��Դ��
**
** �� �� �ˣ�½����
** ����ʱ�䣺2012-03-26
** ------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_MonitorDiagnose(void *P_arg)
{
	/* �������� */
	uint8_t err;
	(void)P_arg;
		
	/* ����ѭ��*/
	while (DEF_TRUE)
	{
//		OSSchedLock();
//		#if (NCU_ROS_DEBUG>0)
//			printf("MonitorDiagnose      : start!\n");
//		#endif
    	OS_CPU_SR  cpu_sr;
		OS_ENTER_CRITICAL();
		SubElements_IndexLED_Output(!IndexLED_Dx[3].IndexLED_State,&IndexLED_Dx[3]);
		printf("MonitorDiagnose: start!\n");
		OS_EXIT_CRITICAL(); 
//		OSSchedUnlock();
		OSTimeDlyHMSM(0, 0, 0, 1000);
	
	};	
}

/********************************************************************************
**                          OS_Task_ControlLawSwitch ����
**
** �����ܣ����Ʋ��Ե������л�
** ����˵�������Ʋ��Ե������л�
** ϵͳ��Դ��
**
** �� �� �ˣ�½����
** ����ʱ�䣺2012-03-26
** ------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_ControlLawSwitch(void *P_arg)
{
	/* �������� */
	uint8_t err;
	(void)P_arg;
		
	/* ����ѭ��*/
	while (DEF_TRUE)
	{
//		OSSchedLock();
    	OS_CPU_SR  cpu_sr;
		OS_ENTER_CRITICAL();
//		#if (NCU_ROS_DEBUG>0)
			printf("ControlLawSwitch: start!\n");
//		#endif
		SubElements_IndexLED_Output(!IndexLED_Dx[4].IndexLED_State,&IndexLED_Dx[4]);
//		OSSchedUnlock();
		OS_EXIT_CRITICAL(); 
		OSTimeDlyHMSM(0, 0, 0,500);	
	};	
}

/********************************************************************************
**                          OS_Task_ParameterCalibrationTuning ����
**
** �����ܣ����ܲ����궨����Ʋ���������
** ����˵�������ܲ����궨����Ʋ���������
** ϵͳ��Դ��
**
** �� �� �ˣ�½����
** ����ʱ�䣺2012-03-26
** ------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_ParameterCalibrationTuning(void *P_arg)
{
	/* �������� */
	uint8_t err;
	(void)P_arg;
		
	/* ����ѭ��*/
	while (DEF_TRUE)
	{
//		#if (NCU_ROS_DEBUG>0)
//			printf("ParameterCalibrationTuning      : start!\n");
//		#endif
		SubElements_IndexLED_Output(!IndexLED_Dx[2].IndexLED_State,&IndexLED_Dx[2]);
		OSTimeDlyHMSM(0, 0, 0, 500);	
	};	
}

/********************************************************************************
**                          OS_Task_Log ����
**
** �����ܣ���־��¼����
** ����˵������־��¼����
** ϵͳ��Դ��
**
** �� �� �ˣ�½����
** ����ʱ�䣺2012-03-26
** ------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_Log(void *P_arg)
{
	/* �������� */
	uint8_t err;
	(void)P_arg;
		
	/* ����ѭ��*/
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
**                          OS_Task_Communication ����
**
** �����ܣ�ͨ�Ž�������
** ����˵����ͨ�Ž�������
** ϵͳ��Դ��
**
** �� �� �ˣ�½����
** ����ʱ�䣺2012-03-26
** ------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** ------------------------------------------------------------------------------
*********************************************************************************/
static void OS_Task_Communication(void *P_arg)
{
	/* �������� */
	uint8_t err;
	(void)P_arg;
		
	/* ����ѭ��*/
	while (DEF_TRUE)
	{
//		#if (NCU_ROS_DEBUG>0)
//			printf("Communication      : start!\n");
//		#endif
		SubElements_IndexLED_Output(!IndexLED_Dx[4].IndexLED_State,&IndexLED_Dx[4]);
		OSTimeDlyHMSM(0, 0, 0, 500);	
	};	
}
