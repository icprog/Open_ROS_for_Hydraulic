/******************* (C) COPYRIGHT 2011 NCU-Roboteam *************************
**               		      NCU_Rotot_OS
**							 NCU_ROS_ucosII_cfg.h
**
** 				 		�ϲ���ѧ�����˶� - 2012
**
** ϵͳ���ܣ�
**			 
** ϵͳ˵����
**
** �� �� ����NCU_ROS_ucosII_cfg.h
** ģ �� ���������˲���ϵͳ�����ļ�
** ��������������UCOSII����ر���
** ����˵����
**
** �� �� �ˣ�½����
** ����ʱ�䣺2012-03-26
** ----------------------------------------------------------------------------
** �� �� �ˣ�½����
** �޸�ʱ�䣺2012-03-26
** �޸�˵����
** ----------------------------------------------------------------------------
** �� �� �ˣ�½����
** �޸�ʱ�䣺2012-03-26
** �޸�˵����
** ----------------------------------------------------------------------------
*******************************************************************************/

#ifndef  __NCU_Ros_ucosII_cfg__
#define  __NCU_Ros_ucosII_cfg__

/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/

#define  APP_OS_PROBE_EN                         DEF_DISABLED
#define  APP_PROBE_COM_EN                        DEF_DISABLED

#ifndef  NCU_ROS_DEBUG
#define	 NCU_ROS_DEBUG 1
#endif
/*
*********************************************************************************************************
*                                              TASKS NAMES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/		

#define	 OS_TASK_START_PRIO					  			(OS_LOWEST_PRIO - 9)
#define  OS_TASK_MonitorDiagnose_PRIO                   (OS_LOWEST_PRIO - 7)
#define  OS_TASK_ControlLawSwitch_PRIO                  (OS_LOWEST_PRIO - 8)
#define  OS_TASK_ParameterCalibrationTuning_PRIO        (OS_LOWEST_PRIO - 6)
#define  OS_TASK_Log_PRIO								(OS_LOWEST_PRIO - 5)
#define  OS_TASK_Communication_PRIO						(OS_LOWEST_PRIO - 4)


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/
#define	 OS_TASK_START_STK_SIZE						  			128
#define  OS_TASK_MonitorDiagnose_STK_SIZE		                128
#define  OS_TASK_ControlLawSwitch_STK_SIZE                      128
#define  OS_TASK_ParameterCalibrationTuning_STK_SIZE            128
#define  OS_TASK_Log_STK_SIZE									128
#define  OS_TASK_Communication_STK_SIZE							128


/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/

#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED


#endif
