/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_STM32.c
**
** 				 		      ZJU - 2015
**
** 系统介绍：XXXXXXXXXXXXXXXXXXXXXX
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_Init_for_STM32.c
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
#include "ROS_hydraulic_Init_for_STM32.h"
/* --------------------------------宏指令-------------------------------------*/

/* ---------------------------------全局变量----------------------------------*/

/* ---------------------------------静态变量----------------------------------*/

/* ----------------------------------函数-------------------------------------*/
/********************************************************************************
** 函 数 名：ROS_HY_Init_STM32()
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
void ROS_HY_Init_STM32(void)
{
	/* 配置系统时钟为 72M */  
	SystemInit();
	NVIC_Configuration();        //中断初始化
	/*TIM2 定时器中断初始化*/
//	TIM2_NVIC_Configuration();	 
//	TIM2_Configuration();
	TIM2_IRQHandler_Init();	 //直接用一条语句表示前面的两条语名内容
	/*IO口初始化*/
	GPIO_EnergySaving_Init();
   	IO_GPIO_Config();
	/*TIM3 定时器中断初始化*/
	TIM3_IRQHandler_Init();	
	/* TIM3 PWM波输出初始化，并使能TIM3 PWM输出 */
//	TIM3_PWM_Init();     //占空比范围0-10000，两路PWM同时关闭
	/*外部IO口中断初始化，用于采样电流峰值与谷值*/
//	EXTI9_5_IRQ_Init();		//统一赋值是无效的
	EXTI9_5_Pin8_IRQ_Init(); //在外部中断中处理电流峰值采样程序
	EXTI9_5_Pin9_IRQ_Init();


}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：节能初始化所有GPIO为模拟输入模式,此函数必需在其他初始化函数之前调用
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
** 函 数 名：XXXXXXXXXXX
** 功能描述：节能初始化所有GPIO为模拟输入模式,此函数必需在其他初始化函数之前调用
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
** 函 数 名：XXXXXXXXXXX
** 功能描述：定时器中断配置
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
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=500;		 								/* 自动重装载寄存器周期的值(计数值) */
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= 65535;//65535; //(72 - 1);				    /* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);																		/* 开启时钟 */
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);		/*先关闭等待使用*/    
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：定时器中断初始化
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
	TIM_TimeBaseStructure.TIM_Period=500;	/* 自动重装载寄存器周期的值(计数值) */
	/* 累计 TIM_Period个频率后产生一个更新或者中断 */
	TIM_TimeBaseStructure.TIM_Prescaler= 65535;//(72 - 1);	/* 时钟预分频数 72M/72 */
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	/* 采样分频 */
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	/*向上计数模式 */
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	/*清除溢出中断标志 */
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM2, ENABLE);	/*开启时钟 */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);	/*等待使用*/   
}
/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：定时器中断初始化
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
//	TIM_TimeBaseStructure.TIM_Period=100;	/* 自动重装载寄存器周期的值(计数值) */
	/* 累计 TIM_Period个频率后产生一个更新或者中断 */
//	TIM_TimeBaseStructure.TIM_Prescaler= 65535;//(72 - 1);	/* 时钟预分频数 72M/72 */
//	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	/* 采样分频 */
//	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 	/*向上计数模式 */
//	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);	/*清除溢出中断标志 */
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3, ENABLE);	/*开启时钟 */
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);	/*先关闭等待使用*/   
}
/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：定时器中断初始化
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
** 函 数 名：XXXXXXXXXXX
** 功能描述：XXXXxxxxxxx
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：龙玉其
** 创建时间：2015-05-31
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
void IO_GPIO_Config(void)
{
	/*定义一个GPIO_InitTypeDef 类型的结构体*/ 
 
	GPIO_InitTypeDef GPIO_InitStructure;    
	
	/*开启GPIOC的外设时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE); /*使能LED灯使用的GPIO时钟*/
 
	/*选择要控制的GPIOC的引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_12;
	
	/*设置引脚的模式为通用的推挽输出
	
	GPIO_Mode_AIN               模拟输入模式
	GPIO_Mode_IN_FLOATING       浮空输入模式
	GPIO_Mode_IPD               下拉输入
	GPIO_Mode_IPU               上拉输入
	GPIO_Mode_Out_OD            开漏输出
	GPIO_Mode_Out_PP            通用推挽输出模式
	GPIO_Mode_AF_OD             复用功能开漏输出
	GPIO_Mode_AF_PP             复用功能推挽输出
	*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	/*设置引脚速率为50MHZ
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

	/* 配置AD采集的GPIO管脚模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	/* 配置AD采集的中断GPIO管脚为输入模式*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);			
}

/********************************************************************************
** 函 数 名：NVIC_Configuration()
** 功能描述：中断配置
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
	
	/* 需要配置的中断向量 */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	
	
	/*  中断向量抢占优先级  */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	
	/*  中断向量抢相应先级  */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	
	/*  中断使能  */ 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

/********************************************************************************
** 函 数 名：NVIC_Configuration()
** 功能描述：中断配置
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
void TIM3_PWM_Init(void)
{
	TIM3_GPIO_Config();
	TIM3_Mode_Config();	
}

/********************************************************************************
** 函 数 名：NVIC_Configuration()
** 功能描述：中断配置
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
static void TIM3_GPIO_Config(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* TIM3 clock enable */
	//PCLK1经过2倍频后作为TIM2的时钟源等于72MHz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //开启TIM3定时器
	/* GPIOC clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);  //开启C口时钟
	
	/*GPIOC Configuration: TIM3 channel 3 and channel 4 as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
}

/********************************************************************************
** 函 数 名：NVIC_Configuration()
** 功能描述：中断配置
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
void TIM3_Mode_Config(void)
{
 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;	

	/* TIM3 clock enable */
	//PCLK1经过2倍频后作为TIM2的时钟源等于72MHz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //开启TIM3定时器
	/* GPIOC clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);  //开启C口时钟
	
	/* -----------------------------------------------------------------------
	TIM3 Configuration: generate 2 PWM signals with the same duty cycle:
	TIM3CLK = 72 MHz, Prescaler = 0x0, TIM3 counter clock = 72 MHz
	TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
	PWM Frequency = 72 KHz.
	TIM3 Channel 3 and channel 4 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
	----------------------------------------------------------------------- */
	
	/* Time base configuration */		 
	TIM_TimeBaseStructure.TIM_Period = PWM_Period;//1000;//14400-1;     //当定时器从0计数到59999，即为60000次，为一个定时周期  14400~5000Hz
	TIM_TimeBaseStructure.TIM_Prescaler = 65535;//0;	    //设置预分频：不预分频，即为72MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //自动重装载周期值
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		
	/* Channel 1, 2,3 and 4 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;    //脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能输出比较状态
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;//失能输出比较N状态
	TIM_OCInitStructure.TIM_Pulse = 0;		  //捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出比较极性低
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	//输出比较空闲状态
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);				  
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);                   //使能定时器3		 
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
}
