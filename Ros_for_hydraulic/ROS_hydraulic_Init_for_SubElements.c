/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_SubElements.c
**
** 				 		      ZJU - 2015
**
** 系统介绍：XXXXXXXXXXXXXXXXXXXXXX
**			 
** 系统说明：
**
** 文 件 名：ROS_hydraulic_Init_for_SubElements.c
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
#include "ROS_hydraulic_Init_for_SubElements.h"
/* --------------------------------宏指令-------------------------------------*/

/* ---------------------------------全局变量----------------------------------*/

/* ---------------------------------静态变量----------------------------------*/

/* ----------------------------------函数-------------------------------------*/
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
void ROS_HY_Init_SubElements(void)
{
	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_POWER); //可由IO_GPIO_Config完成
	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_A);	//可由IO_GPIO_Config完成
	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_B);	//可由IO_GPIO_Config完成

	IndexLED_Init(RCC_APB2Periph_GPIOD,&IndexLED_Window);	//可由IO_GPIO_Config完成
	IndexLED_Init(RCC_APB2Periph_GPIOA,&IndexLED_Err);	//可由IO_GPIO_Config完成
	IndexLED_Init(RCC_APB2Periph_GPIOA,&IndexLED_Dx[0]);	//可由IO_GPIO_Config完成
	IndexLED_Init(RCC_APB2Periph_GPIOA,&IndexLED_Dx[1]);	//可由IO_GPIO_Config完成
	IndexLED_Init(RCC_APB2Periph_GPIOB,&IndexLED_Dx[2]);	//可由IO_GPIO_Config完成
	IndexLED_Init(RCC_APB2Periph_GPIOB,&IndexLED_Dx[3]);	//可由IO_GPIO_Config完成
	IndexLED_Init(RCC_APB2Periph_GPIOB,&IndexLED_Dx[4]);	//可由IO_GPIO_Config完成

	Buzzer_Init(RCC_APB2Periph_GPIOB,&Buzzer_Alarm);   	//可由IO_GPIO_Config完成
	VoltageLevel_Input_Init(RCC_APB2Periph_GPIOB,&InputSignal_Flag);

	PropertionalSolenoid_Init(RCC_APB2Periph_GPIOC,&SolenoidB);		//电磁铁PWM输出可由TIM3_PWM_Init(void)完成
	PropertionalSolenoid_Init(RCC_APB2Periph_GPIOC,&SolenoidA);		//电磁铁PWM输出可由TIM3_PWM_Init(void)完成
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
void IndexLED_Init(uint32_t GPIO_CLK,IndexLED_TypeDef *IndexLED)
{ 
	/* Enable the GPIO_LED Clock*/ 
	RCC_APB2PeriphClockCmd(GPIO_CLK, ENABLE);
	/* Configure the GPIO_LED pin */
	GPIO_Init(IndexLED->GPIOX, &IndexLED->GPIO_InitStructure);	
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
void VoltageLevel_Input_Init(uint32_t GPIO_CLK,VoltageLevel_TypeDef *Input)
{ 
	/* Enable the GPIO_LED Clock*/ 
	RCC_APB2PeriphClockCmd(GPIO_CLK, ENABLE);
	/* Configure the GPIO_LED pin */
	GPIO_Init(Input->GPIOX, &Input->GPIO_InitStructure);	
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
void Buzzer_Init(uint32_t GPIO_CLK,Buzzer_TypeDef *Buzzer)
{
	/* Enable the GPIO_LED Clock*/ 
	RCC_APB2PeriphClockCmd(GPIO_CLK, ENABLE);
	/* Configure the GPIO_LED pin */
	GPIO_Init(Buzzer->GPIOX, &Buzzer->GPIO_InitStructure);	
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：XXXXxxxxxxx
** 其他说明：入口参数只给出了GPIO口的指示，相应的定时器指示与IO重映射需要在函数
			内时行调整,时钟周期也需要相应调整
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
void PropertionalSolenoid_Init(uint32_t GPIO_CLK,PropertionalSolenoid_TypeDef *Solenoid)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* TIM3 clock enable */
	//PCLK1经过2倍频后作为TIM2的时钟源等于72MHz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //开启TIM3定时器
	/* GPIOC clock enable */
	RCC_APB2PeriphClockCmd(GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);  //开启C口时钟
	
	/*GPIOC Configuration: TIM3 channel 3 and channel 4 as alternate function push-pull */
	
	GPIO_Init(Solenoid->GPIOX, &Solenoid->GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
		
	/* -----------------------------------------------------------------------
	TIM3 Configuration: generate 2 PWM signals with the same duty cycle:
	TIM3CLK = 72 MHz, Prescaler = 0x0, TIM3 counter clock = 72 MHz
	TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
	PWM Frequency = 72 KHz.
	TIM3 Channel 3 and channel 4 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
	----------------------------------------------------------------------- */	
	/* Time base configuration */		 
	TIM_TimeBaseStructure.TIM_Period =PWM_Period;// PWM_Period;//1000;//14400-1;     //当定时器从0计数到59999，即为60000次，为一个定时周期  14400~5000Hz
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//65535;//0;	    //设置预分频：不预分频，即为72MHz
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
//void PilotValve_Init(PilotValve_TypeDef *PilotValve)
//{
//
//}

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
//void MainValve_Init(MainValve_TypeDef *MainValve)
//{
//
//}

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
//void LVDT_PositionSenser_Init(GPIO_TypeDef *GPIOx,LVDT_PositionSenser_TypeDef *LVDT_PositionSenser)
//{
//
//}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：
** 其他说明：DMA形式AD采集,相应的DMA通道与AD通道要对应
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
//void PressureSenser_Init(uint32_t GPIO_CLK,PressureSenser_TypeDef *PressureSenser)
//{
//	ADC_InitTypeDef ADC_InitStructure;
//	DMA_InitTypeDef DMA_InitStructure;
//
//	RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
//	/* Configure PC.04 (ADC Channel14) as analog input -------------------------*/
//	GPIO_Init(PressureSenser->GPIOX, &PressureSenser->GPIO_InitStructure);
//
//	/* DMA1 channel1 configuration ----------------------------------------------*/
//	DMA_DeInit(DMA1_Channel1);
//	DMA_InitStructure.DMA_PeripheralBaseAddr = 0x4001244C;
//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&PressureSenser->Pressure;
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//	DMA_InitStructure.DMA_BufferSize = 1;
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
//	
//	/* Enable DMA1 channel1 */
//	DMA_Cmd(DMA1_Channel1, ENABLE);
//	
//	/* ADC1 configuration ------------------------------------------------------*/
//	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
//	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
//	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
//	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//	ADC_InitStructure.ADC_NbrOfChannel = 1;
//	ADC_Init(ADC1, &ADC_InitStructure);
//	
//	/* ADC1 regular channel14 configuration */ 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);
//	
//	/* Enable ADC1 DMA */
//	ADC_DMACmd(ADC1, ENABLE);
//	
//	/* Enable ADC1 */
//	ADC_Cmd(ADC1, ENABLE);
//}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：
** 其他说明：DMA形式AD采集,相应的DMA通道与AD通道要对应
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
//void VoltageSenser_Init(uint32_t GPIO_CLK,VoltageSenser_TypeDef *VoltageSenser)
//{
//	ADC_InitTypeDef ADC_InitStructure;
//	DMA_InitTypeDef DMA_InitStructure;
//
//	RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
//	/* Configure PC.04 (ADC Channel14) as analog input -------------------------*/
//	GPIO_Init(VoltageSenser->GPIOX, &VoltageSenser->GPIO_InitStructure);
//
//	/* DMA1 channel1 configuration ----------------------------------------------*/
//	DMA_DeInit(DMA1_Channel1);
//	DMA_InitStructure.DMA_PeripheralBaseAddr = 0x4001244C;//ADC1的规则数据寄存器地址
//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&VoltageSenser->Voltage;	//AD转换后的数据目标存储地址
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//	DMA_InitStructure.DMA_BufferSize = 1;
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
//	
//	/* Enable DMA1 channel1 */
//	DMA_Cmd(DMA1_Channel1, ENABLE);
//	
//	/* ADC1 configuration ------------------------------------------------------*/
//	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
//	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
//	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
//	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//	ADC_InitStructure.ADC_NbrOfChannel = 1;
//	ADC_Init(ADC1, &ADC_InitStructure);
//	
//	/* ADC1 regular channel14 configuration */ 
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);
//	
//	/* Enable ADC1 DMA */
//	ADC_DMACmd(ADC1, ENABLE);
//	
//	/* Enable ADC1 */
//	ADC_Cmd(ADC1, ENABLE);
//}

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
//void TemperatureSenser_Init(GPIO_TypeDef *GPIOx,TemperatureSenser_TypeDef *TemperatureSenser)
//{
//
//}

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
//void PID_ControlParameters_Init(GPIO_TypeDef *GPIOx,PID_ControlParameters_TypeDef *PID_ControlParameters)
//{
//
//}
