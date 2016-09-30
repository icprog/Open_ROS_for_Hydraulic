/******************* (C) COPYRIGHT 2011 NCU-Roboteam *************************
**               				  NCU_Robot_OS_V1_0
**
** 				 		
**
** 系统介绍:机器人操作控制系统
**			 
** 系统说明：
**
** 创 建 人：陆振宇
** 创建时间：2012-03-23
** ----------------------------------------------------------------------------
** 修 改 人：陆振宇
** 修改时间：2011-03-23
** 修改说明：
** ----------------------------------------------------------------------------
** 修 改 人：
** 修改时间：2011-06-03
** 修改说明：
** ----------------------------------------------------------------------------
*******************************************************************************/	

/* ------------------------------头文件包含-----------------------------------*/
#include "includes.h"

#if (NCU_ROS_DEBUG >0) 
	#include <stdio.h>
	#include <ctype.h>
#endif


/* --------------------------------宏指令-------------------------------------*/

//#ifdef __GNUC__
//	#define PUTXHAR_PROTOTYPE int__io_putchar(int ch)
//	#define GETCHAR_PROTOTYPE int__io_getchar(void)
//#else
//	#define PUTCHAR_PROTOTYPE int fputc(int ch,FILE*f)
//	#define GETCHAR_PROTOTYPE int fgetc(FILE*f)	
//#endif/*__GNUC__*/


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#define GETCHAR_PROTOTYPE int fgetc(FILE*f)	
#endif /* __GNUC__ */

/* ------------------------------------------------------------------------- */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

GETCHAR_PROTOTYPE
{
	uint16_t ch;
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);
	ch=USART_ReceiveData(USART1);
	if(isprint(ch)||(ch=='\r'))
	{
		if(ch=='\r')
			USART_SendData(USART1,'\n');
		else
			USART_SendData(USART1,(uint8_t)ch);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	}
	return ch;
}																	
/********************************************************************************
** 函 数 名：main
** 功能描述：系统主函数
** 其他说明：
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：陆振宇
** 创建时间：2012-03-23
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
int main(void)
{
	ROS_HY_System_Conf(); //此函数不能放在uCOS操作系统中运行，否则不成功
	SubElements_IndexLED_Output(ON,&IndexLED_POWER);
 	SubElements_IndexLED_Output(OFF,&IndexLED_Err);
	SubElements_IndexLED_Output(OFF,&IndexLED_A);
	SubElements_IndexLED_Output(OFF,&IndexLED_B);
	SubElements_IndexLED_Output(OFF,&IndexLED_Window);
	SubElements_IndexLED_Output(OFF,&IndexLED_Dx[0]);
	SubElements_IndexLED_Output(OFF,&IndexLED_Dx[1]);
	SubElements_IndexLED_Output(OFF,&IndexLED_Dx[2]);	
	SubElements_IndexLED_Output(OFF,&IndexLED_Dx[3]);
	SubElements_IndexLED_Output(OFF,&IndexLED_Dx[4]);
	SubElements_Buzzer_Output(OFF,&Buzzer_Alarm);
	SubElements_PropertionalSolenoid_PWM_Control(0,PWM_Period,&SolenoidA);
	SubElements_PropertionalSolenoid_PWM_Control(4800,PWM_Period,&SolenoidB);//接了电磁铁	
	Robot_OS_Main();
//	while(1)
//	{
////		printf("ROS_HY");
//
////		USART_SendData(USART1,0x05);
////		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
//
////		SubElements_IndexLED_Output(ON,&IndexLED_A);
////		if(IndexLED_A.IndexLED_State==OFF)SubElements_IndexLED_Output(ON,&IndexLED_A);
//		
////		while(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)==RESET)
////		{
////			SubElements_IndexLED_Output(!IndexLED_Dx[0].IndexLED_State,&IndexLED_Dx[0]);
////			printf("Update\n");		
////		};
////		while(TIM_GetFlagStatus(TIM3,TIM_FLAG_CC4)==RESET)
////		{
////			SubElements_IndexLED_Output(!IndexLED_Dx[0].IndexLED_State,&IndexLED_Dx[0]);
////			printf("CC4\n");
////		};		 
////		while(TIM_GetFlagStatus(TIM3,TIM_FLAG_CC3)==RESET)
////		{
////			SubElements_IndexLED_Output(!IndexLED_Dx[0].IndexLED_State,&IndexLED_Dx[0]);
////			printf("CC3\n");	
////		};
//	}; 
}


/************************* @defgroup uC/OS-II 应用层钩子函数***********************/
#if (OS_APP_HOOKS_EN > 0)

/**
  * @brief  此函数在一个任务被创建时被调用
	* @param  ptcb: 被创建的任务的TCB指针
	* @retval : None
	* @note: 当该函数被调用时必须关闭所有中断
	*/
void App_TaskCreateHook(OS_TCB *ptcb)
{

}

/**
  * @brief  此函数在一个任务被删除时被调用
	* @param  ptcb: 被删除的任务的TCB指针
	* @retval : None
	* @note: 当该函数被调用时必须关闭所有中断
	*/
void App_TaskDelHook(OS_TCB *ptcb)
{
	(void)ptcb;
}

/**
  * @brief  该函数会被空闲任务调用，可以用来关闭某些外设或至CPU至低功耗模式
	* @param  None
	* @retval : None
	* @note: 当该函数被调用时必须关闭所有中断
	*/
#if OS_VERSION >= 251
void  App_TaskIdleHook (void)
{
}
#endif

/**
  * @brief  该函数会被统计任务调用，可以用来增加某些用户需要的功能
	* @param  None
	* @retval : None
	*/
void  App_TaskStatHook (void)
{
}

/**
  * @brief  该函数会在一个任务切换过程中被调用，可以用来增加某些用户需要的功能
	* @param  None
	* @retval : None
	* @note (1): 当该函数被调用时必须关闭所有中断；
	*       (2): 注意系统总是将最高优先级的就绪任务的TCB指针赋给全局变量OSTCBHighRdy，
	*            将被切换的任务的TCB指针赋给全局变量OSTCBCur。
	*/
#if OS_TASK_SW_HOOK_EN > 0
void  App_TaskSwHook (void)
{

}
#endif

/**
  * @brief  该函数会在一个任务控制块初始化过程中被OS_TCBInit()调用。
	* @param  ptcb: 被初始化的任务的TCB指针
	* @retval : None
	* @note: Interrupts may or may not be ENABLED during this call.
	*/
#if OS_VERSION >= 204
void  App_TCBInitHook (OS_TCB *ptcb)
{
	(void)ptcb;
}
#endif

/**
  * @brief  该函数会在每一个时钟节拍到来时被调用。
	* @param  None
	* @retval : None
	* @note: 当该函数被调用时必须关闭所有中断；
	*/
#if OS_TIME_TICK_HOOK_EN > 0
void  App_TimeTickHook (void)
{

}
#endif

#endif /* #if (OS_APP_HOOKS_EN > 0) */

/******************* (C) COPYRIGHT 2011 NCU-Roboteam *****END OF FILE*************/
