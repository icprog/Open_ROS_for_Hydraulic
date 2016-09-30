/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_Communication.c
**
** 				 		      ZJU - 2015
**
** 系统介绍：XXXXXXXXXXXXXXXXXXXXXX
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_Init_for_Communication.c
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
#include "ROS_hydraulic_Init_for_Communication.h"
/* --------------------------------宏指令-------------------------------------*/

/* ---------------------------------全局变量----------------------------------*/

/* ---------------------------------静态变量----------------------------------*/

/* ----------------------------------函数-------------------------------------*/
/********************************************************************************
** 函 数 名：ROS_HY_Init_Communication()
** 功能描述：控制主芯片相关总体初始化
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
void ROS_HY_Init_Communication(void)
{
	/*RS232通信接口初始化*/
	RS232_Init();

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
void RS232_Init(void)
{
 	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
  	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  	USART_InitStructure.USART_StopBits = USART_StopBits_1;
  	USART_InitStructure.USART_Parity = USART_Parity_No;
  	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	 
  	STM_EVAL_COMInit(COM1, &USART_InitStructure);
		/*   打开串口的接收中断 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		/*   串口打开  */
	USART_Cmd(USART1,ENABLE);
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
** 修改说明： 引用自stm3210e_eval.c文件
** -------------------------------------------------------------------------------
**********************************************************************************/
//void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;
//
//  /* Enable GPIO clock */
//  RCC_APB2PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM] | RCC_APB2Periph_AFIO, ENABLE);
//
//  /* Enable UART clock */
//  if (COM == COM1)
//  {
//    RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE); 
//  }
//  else
//  {
//    RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
//  }
//
//  /* Configure USART Tx as alternate function push-pull */
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
//
//  /* Configure USART Rx as input floating */
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
//  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);
//
//  /* USART configuration */
//  USART_Init(COM_USART[COM], USART_InitStruct);
//    
//  /* Enable USART */
//  USART_Cmd(COM_USART[COM], ENABLE);
//}
