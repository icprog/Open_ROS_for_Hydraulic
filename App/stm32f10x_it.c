/**
  ******************************************************************************
  * @file    USART/Printf/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "ROS_hydraulic_Function_Realization.h"


/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_Printf
  * @{
  */ 
extern volatile u32 tim;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}


/******************************************************************************/
/* 串口中断入口函数    */   
/******************************************************************************/
void USART1_IRQHandler(void)
{
	u8 c;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 			  
		c=USART1->DR;
	} 	 
}
/**
  * @brief  This function handles TIM2 interrupt request.
  * @param  None
  * @retval : None
  */
void TIM2_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);    
		SubElements_IndexLED_Output(!IndexLED_A.IndexLED_State,&IndexLED_A);
				
		if	(SolenoidA.Flag==2) //保证电感计算时，已采集下降沿电流
		{
			SubElements_PropertionalSolenoid_GetInductance(&SolenoidA);
		};
		if	(SolenoidB.Flag==2)
		{
			SubElements_PropertionalSolenoid_GetInductance(&SolenoidB);
		};
		printf("B_up:%d\n",SolenoidB.UpEdge_Current);
		printf("B_down:%d\n",SolenoidB.DownEdge_Current);
		printf("B_L:%d\n",SolenoidB.Inductance);
//		printf("A_L");
	}		 	
}

void TIM3_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET ) 
	{	
		SubElements_IndexLED_Output(!IndexLED_Dx[0].IndexLED_State,&IndexLED_Dx[0]);

		SubElements_PropertionalSolenoid_Current_Acquisition(&SolenoidA);
		SolenoidA.UpEdge_Current=SolenoidA.Real_Current;
		SolenoidA.Flag=1;
		SubElements_PropertionalSolenoid_Current_Acquisition(&SolenoidB);
		SolenoidB.UpEdge_Current=SolenoidB.Real_Current;
		SolenoidB.Flag=1;
		TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);    
	}		 	
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	{
		SubElements_IndexLED_Output(!IndexLED_Dx[1].IndexLED_State,&IndexLED_Dx[1]);
		SubElements_PropertionalSolenoid_Current_Acquisition(&SolenoidB);
		SolenoidB.DownEdge_Current=SolenoidB.Real_Current;
		SolenoidB.Flag=2;
		/* Clear the Key Button EXTI line pending bit */
		EXTI_ClearITPendingBit(EXTI_Line9);
	}

	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		SubElements_IndexLED_Output(!IndexLED_Dx[2].IndexLED_State,&IndexLED_Dx[2]);
		SubElements_PropertionalSolenoid_Current_Acquisition(&SolenoidA);
		SolenoidA.DownEdge_Current=SolenoidA.Real_Current;
		SolenoidA.Flag=2;
		/* Clear the Key Button EXTI line pending bit */
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
