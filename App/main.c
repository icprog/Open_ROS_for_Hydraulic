/******************* (C) COPYRIGHT 2011 NCU-Roboteam *************************
**               				  NCU_Robot_OS_V1_0
**
** 				 		
**
** ϵͳ����:�����˲�������ϵͳ
**			 
** ϵͳ˵����
**
** �� �� �ˣ�½����
** ����ʱ�䣺2012-03-23
** ----------------------------------------------------------------------------
** �� �� �ˣ�½����
** �޸�ʱ�䣺2011-03-23
** �޸�˵����
** ----------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺2011-06-03
** �޸�˵����
** ----------------------------------------------------------------------------
*******************************************************************************/	

/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "includes.h"

#if (NCU_ROS_DEBUG >0) 
	#include <stdio.h>
	#include <ctype.h>
#endif


/* --------------------------------��ָ��-------------------------------------*/

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
** �� �� ����main
** ����������ϵͳ������
** ����˵����
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ�½����
** ����ʱ�䣺2012-03-23
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
int main(void)
{
	ROS_HY_System_Conf(); //�˺������ܷ���uCOS����ϵͳ�����У����򲻳ɹ�
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
	SubElements_PropertionalSolenoid_PWM_Control(4800,PWM_Period,&SolenoidB);//���˵����	
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


/************************* @defgroup uC/OS-II Ӧ�ò㹳�Ӻ���***********************/
#if (OS_APP_HOOKS_EN > 0)

/**
  * @brief  �˺�����һ�����񱻴���ʱ������
	* @param  ptcb: �������������TCBָ��
	* @retval : None
	* @note: ���ú���������ʱ����ر������ж�
	*/
void App_TaskCreateHook(OS_TCB *ptcb)
{

}

/**
  * @brief  �˺�����һ������ɾ��ʱ������
	* @param  ptcb: ��ɾ���������TCBָ��
	* @retval : None
	* @note: ���ú���������ʱ����ر������ж�
	*/
void App_TaskDelHook(OS_TCB *ptcb)
{
	(void)ptcb;
}

/**
  * @brief  �ú����ᱻ����������ã����������ر�ĳЩ�������CPU���͹���ģʽ
	* @param  None
	* @retval : None
	* @note: ���ú���������ʱ����ر������ж�
	*/
#if OS_VERSION >= 251
void  App_TaskIdleHook (void)
{
}
#endif

/**
  * @brief  �ú����ᱻͳ��������ã�������������ĳЩ�û���Ҫ�Ĺ���
	* @param  None
	* @retval : None
	*/
void  App_TaskStatHook (void)
{
}

/**
  * @brief  �ú�������һ�������л������б����ã�������������ĳЩ�û���Ҫ�Ĺ���
	* @param  None
	* @retval : None
	* @note (1): ���ú���������ʱ����ر������жϣ�
	*       (2): ע��ϵͳ���ǽ�������ȼ��ľ��������TCBָ�븳��ȫ�ֱ���OSTCBHighRdy��
	*            �����л��������TCBָ�븳��ȫ�ֱ���OSTCBCur��
	*/
#if OS_TASK_SW_HOOK_EN > 0
void  App_TaskSwHook (void)
{

}
#endif

/**
  * @brief  �ú�������һ��������ƿ��ʼ�������б�OS_TCBInit()���á�
	* @param  ptcb: ����ʼ���������TCBָ��
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
  * @brief  �ú�������ÿһ��ʱ�ӽ��ĵ���ʱ�����á�
	* @param  None
	* @retval : None
	* @note: ���ú���������ʱ����ر������жϣ�
	*/
#if OS_TIME_TICK_HOOK_EN > 0
void  App_TimeTickHook (void)
{

}
#endif

#endif /* #if (OS_APP_HOOKS_EN > 0) */

/******************* (C) COPYRIGHT 2011 NCU-Roboteam *****END OF FILE*************/
