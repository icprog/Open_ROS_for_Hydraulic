/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_STM32.c
**
** 				 		      ZJU - 2015
**
** ϵͳ���ܣ�XXXXXXXXXXXXXXXXXXXXXX
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_Init_for_STM32.c
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
#include "ROS_hydraulic_Init_for_STM32.h"
/* --------------------------------��ָ��-------------------------------------*/

/* ---------------------------------ȫ�ֱ���----------------------------------*/

/* ---------------------------------��̬����----------------------------------*/

/* ----------------------------------����-------------------------------------*/
/********************************************************************************
** �� �� ����ROS_HY_Init_STM32()
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
void ROS_HY_Init_STM32(void)
{
	/* ����ϵͳʱ��Ϊ 72M */  
	SystemInit();
	NVIC_Configuration();        //�жϳ�ʼ��
	/*TIM2 ��ʱ���жϳ�ʼ��*/
//	TIM2_NVIC_Configuration();	 
//	TIM2_Configuration();
	TIM2_IRQHandler_Init();	 //ֱ����һ������ʾǰ���������������
	/*IO�ڳ�ʼ��*/
	GPIO_EnergySaving_Init();
   	IO_GPIO_Config();
	/*TIM3 ��ʱ���жϳ�ʼ��*/
	TIM3_IRQHandler_Init();	
	/* TIM3 PWM�������ʼ������ʹ��TIM3 PWM��� */
//	TIM3_PWM_Init();     //ռ�ձȷ�Χ0-10000����·PWMͬʱ�ر�
	/*�ⲿIO���жϳ�ʼ�������ڲ���������ֵ���ֵ*/
//	EXTI9_5_IRQ_Init();		//ͳһ��ֵ����Ч��
	EXTI9_5_Pin8_IRQ_Init(); //���ⲿ�ж��д��������ֵ��������
	EXTI9_5_Pin9_IRQ_Init();


}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** �������������ܳ�ʼ������GPIOΪģ������ģʽ,�˺���������������ʼ������֮ǰ����
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
void GPIO_EnergySaving_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;   
	/* Configure all unused GPIO port pins in Analog Input mode (floating input
	  trigger OFF), this will reduce the power consumption and increase the 
	immunity against EMI/EMC *************************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
	                      RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
	                      RCC_APB2Periph_GPIOE, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
	                      RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
	                      RCC_APB2Periph_GPIOE, DISABLE);  
	#ifdef USE_STM3210E_EVAL
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE); 
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, DISABLE);
	#endif /* USE_STM3210E_EVAL */
}
/********************************************************************************
** �� �� ����XXXXXXXXXXX
** �������������ܳ�ʼ������GPIOΪģ������ģʽ,�˺���������������ʼ������֮ǰ����
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
void TIM2_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ������������ʱ���ж�����
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
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=500;		 								/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
    TIM_TimeBaseStructure.TIM_Prescaler= 65535;//65535; //(72 - 1);				    /* ʱ��Ԥ��Ƶ�� 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* ������Ƶ */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* ���ϼ���ģʽ */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* �������жϱ�־ */
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);																		/* ����ʱ�� */
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);		/*�ȹرյȴ�ʹ��*/    
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ������������ʱ���жϳ�ʼ��
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
void TIM2_IRQHandler_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Period=500;	/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
	/* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
	TIM_TimeBaseStructure.TIM_Prescaler= 65535;//(72 - 1);	/* ʱ��Ԥ��Ƶ�� 72M/72 */
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	/* ������Ƶ */
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	/*���ϼ���ģʽ */
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	/*�������жϱ�־ */
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);	/*����ʱ�� */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);	/*�ȴ�ʹ��*/   
}
/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ������������ʱ���жϳ�ʼ��
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
void TIM3_IRQHandler_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	TIM_DeInit(TIM3);
//	TIM_TimeBaseStructure.TIM_Period=100;	/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
	/* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
//	TIM_TimeBaseStructure.TIM_Prescaler= 65535;//(72 - 1);	/* ʱ��Ԥ��Ƶ�� 72M/72 */
//	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	/* ������Ƶ */
//	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	/*���ϼ���ģʽ */
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);	/*�������жϱ�־ */
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3, ENABLE);	/*����ʱ�� */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);	/*�ȹرյȴ�ʹ��*/   
}
/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ������������ʱ���жϳ�ʼ��
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
void EXTI9_5_IRQ_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the BUTTON Clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
//	/* Configure Button pin as input floating */
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

 
     /* Configure Button EXTI line */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8|GPIO_PinSource9);

	EXTI_InitStructure.EXTI_Line = EXTI_Line9|EXTI_Line8;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//EXTI_Mode_Event;EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x06;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 
	NVIC_Init(&NVIC_InitStructure); 
}

void EXTI9_5_Pin8_IRQ_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the BUTTON Clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
//	/* Configure Button pin as input floating */
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

 
     /* Configure Button EXTI line */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8);

	EXTI_InitStructure.EXTI_Line = EXTI_Line8;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//EXTI_Mode_Event;EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x06;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 
	NVIC_Init(&NVIC_InitStructure); 
}

void EXTI9_5_Pin9_IRQ_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Enable the BUTTON Clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
//	/* Configure Button pin as input floating */
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

 
     /* Configure Button EXTI line */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource9);

	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//EXTI_Mode_Event;EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/* Enable and set Button EXTI Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x06;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x06;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 
	NVIC_Init(&NVIC_InitStructure); 
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
** ��    �ߣ�������
** ����ʱ�䣺2015-05-31
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
void IO_GPIO_Config(void)
{
	/*����һ��GPIO_InitTypeDef ���͵Ľṹ��*/ 
 
	GPIO_InitTypeDef GPIO_InitStructure;    
	
	/*����GPIOC������ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE); /*ʹ��LED��ʹ�õ�GPIOʱ��*/
 
	/*ѡ��Ҫ���Ƶ�GPIOC������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_12;
	
	/*�������ŵ�ģʽΪͨ�õ��������
	
	GPIO_Mode_AIN               ģ������ģʽ
	GPIO_Mode_IN_FLOATING       ��������ģʽ
	GPIO_Mode_IPD               ��������
	GPIO_Mode_IPU               ��������
	GPIO_Mode_Out_OD            ��©���
	GPIO_Mode_Out_PP            ͨ���������ģʽ
	GPIO_Mode_AF_OD             ���ù��ܿ�©���
	GPIO_Mode_AF_PP             ���ù����������
	*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	/*������������Ϊ50MHZ
	  GPIO_Speed_10MHz 
    GPIO_Speed_2MHz 
    GPIO_Speed_50MHz	
	*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_12);  
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	GPIO_ResetBits(GPIOB,GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11);  
	GPIO_SetBits(GPIOB,GPIO_Pin_9);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_Init(GPIOC,&GPIO_InitStructure);	
	GPIO_ResetBits(GPIOC,GPIO_Pin_12|GPIO_Pin_10|GPIO_Pin_11);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD,&GPIO_InitStructure);	
	GPIO_ResetBits(GPIOD,GPIO_Pin_2); 

	/* ����AD�ɼ���GPIO�ܽ�ģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	/* ����AD�ɼ����ж�GPIO�ܽ�Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);			
}

/********************************************************************************
** �� �� ����NVIC_Configuration()
** �����������ж�����
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
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	#ifdef  VECT_TAB_RAM  
	/* Set the Vector Table base location at 0x20000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
	#else  /* VECT_TAB_FLASH  */
	/* Set the Vector Table base location at 0x08000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif

	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/* Enable the EXTI0 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* ��Ҫ���õ��ж����� */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	
	
	/*  �ж�������ռ���ȼ�  */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	
	/*  �ж���������Ӧ�ȼ�  */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	
	/*  �ж�ʹ��  */ 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

/********************************************************************************
** �� �� ����NVIC_Configuration()
** �����������ж�����
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
void TIM3_PWM_Init(void)
{
	TIM3_GPIO_Config();
	TIM3_Mode_Config();	
}

/********************************************************************************
** �� �� ����NVIC_Configuration()
** �����������ж�����
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
static void TIM3_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* TIM3 clock enable */
	//PCLK1����2��Ƶ����ΪTIM2��ʱ��Դ����72MHz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //����TIM3��ʱ��
	/* GPIOC clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);  //����C��ʱ��
	
	/*GPIOC Configuration: TIM3 channel 3 and channel 4 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
}

/********************************************************************************
** �� �� ����NVIC_Configuration()
** �����������ж�����
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
void TIM3_Mode_Config(void)
{
 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	

	/* TIM3 clock enable */
	//PCLK1����2��Ƶ����ΪTIM2��ʱ��Դ����72MHz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //����TIM3��ʱ��
	/* GPIOC clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);  //����C��ʱ��
	
	/* -----------------------------------------------------------------------
	TIM3 Configuration: generate 2 PWM signals with the same duty cycle:
	TIM3CLK = 72 MHz, Prescaler = 0x0, TIM3 counter clock = 72 MHz
	TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
	PWM Frequency = 72 KHz.
	TIM3 Channel 3 and channel 4 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
	----------------------------------------------------------------------- */
	
	/* Time base configuration */		 
	TIM_TimeBaseStructure.TIM_Period = PWM_Period;//1000;//14400-1;     //����ʱ����0������59999����Ϊ60000�Σ�Ϊһ����ʱ����  14400~5000Hz
	TIM_TimeBaseStructure.TIM_Prescaler = 65535;//0;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //�Զ���װ������ֵ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
	/* Channel 1, 2,3 and 4 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;    //�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ������Ƚ�״̬
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;//ʧ������Ƚ�N״̬
	TIM_OCInitStructure.TIM_Pulse = 0;		  //����ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //����Ƚϼ��Ե�
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	//����ȽϿ���״̬
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);				  
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3		 
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
}
