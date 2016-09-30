/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_Communication.c
**
** 				 		      ZJU - 2015
**
** ϵͳ���ܣ�XXXXXXXXXXXXXXXXXXXXXX
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_Init_for_Communication.c
** ģ �� ����XXXXXXXXXXXXXXXXXXXX
** ����������XXXXXXXXXXXXXXXX
** ����˵����
** �� �� �ˣ�½����
** ����ʱ�䣺2015-05-31
** ----------------------------------------------------------------------------
** �� �� �ˣ�½����
** �޸�ʱ�䣺2015-05-31
** �޸�˵����
** ----------------------------------------------------------------------------
** �� �� �ˣ�½����
** �޸�ʱ�䣺2015-05-31
** �޸�˵����
** ----------------------------------------------------------------------------
*******************************************************************************/	

/* ------------------------------ͷ�ļ�����-----------------------------------*/
#include "ROS_hydraulic_Init_for_Communication.h"
/* --------------------------------��ָ��-------------------------------------*/

/* ---------------------------------ȫ�ֱ���----------------------------------*/

/* ---------------------------------��̬����----------------------------------*/

/* ----------------------------------����-------------------------------------*/
/********************************************************************************
** �� �� ����ROS_HY_Init_Communication()
** ����������������оƬ��������ʼ��
** ����˵����XXXXXXXXXXXXXXXXXXXX
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ�½����
** ����ʱ�䣺2015-05-31
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
void ROS_HY_Init_Communication(void)
{
	/*RS232ͨ�Žӿڳ�ʼ��*/
	RS232_Init();

}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������XXXXxxxxxxx
** ����˵����XXXXXXXXXXXXXXXXXXXX
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ�½����
** ����ʱ�䣺2015-05-31
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
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
		/*   �򿪴��ڵĽ����ж� */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		/*   ���ڴ�  */
	USART_Cmd(USART1,ENABLE);
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������XXXXxxxxxxx
** ����˵����XXXXXXXXXXXXXXXXXXXX
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ�½����
** ����ʱ�䣺2015-05-31
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵���� ������stm3210e_eval.c�ļ�
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
