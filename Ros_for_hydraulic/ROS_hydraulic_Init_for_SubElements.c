/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_SubElements.c
**
** 				 		      ZJU - 2015
**
** ϵͳ���ܣ�XXXXXXXXXXXXXXXXXXXXXX
**			 
** ϵͳ˵����
**
** �� �� ����ROS_hydraulic_Init_for_SubElements.c
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
#include "ROS_hydraulic_Init_for_SubElements.h"
/* --------------------------------��ָ��-------------------------------------*/

/* ---------------------------------ȫ�ֱ���----------------------------------*/

/* ---------------------------------��̬����----------------------------------*/

/* ----------------------------------����-------------------------------------*/
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
void ROS_HY_Init_SubElements(void)
{
	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_POWER); //����IO_GPIO_Config���
	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_A);	//����IO_GPIO_Config���
	IndexLED_Init(RCC_APB2Periph_GPIOC,&IndexLED_B);	//����IO_GPIO_Config���

	IndexLED_Init(RCC_APB2Periph_GPIOD,&IndexLED_Window);	//����IO_GPIO_Config���
	IndexLED_Init(RCC_APB2Periph_GPIOA,&IndexLED_Err);	//����IO_GPIO_Config���
	IndexLED_Init(RCC_APB2Periph_GPIOA,&IndexLED_Dx[0]);	//����IO_GPIO_Config���
	IndexLED_Init(RCC_APB2Periph_GPIOA,&IndexLED_Dx[1]);	//����IO_GPIO_Config���
	IndexLED_Init(RCC_APB2Periph_GPIOB,&IndexLED_Dx[2]);	//����IO_GPIO_Config���
	IndexLED_Init(RCC_APB2Periph_GPIOB,&IndexLED_Dx[3]);	//����IO_GPIO_Config���
	IndexLED_Init(RCC_APB2Periph_GPIOB,&IndexLED_Dx[4]);	//����IO_GPIO_Config���

	Buzzer_Init(RCC_APB2Periph_GPIOB,&Buzzer_Alarm);   	//����IO_GPIO_Config���
	VoltageLevel_Input_Init(RCC_APB2Periph_GPIOB,&InputSignal_Flag);

	PropertionalSolenoid_Init(RCC_APB2Periph_GPIOC,&SolenoidB);		//�����PWM�������TIM3_PWM_Init(void)���
	PropertionalSolenoid_Init(RCC_APB2Periph_GPIOC,&SolenoidA);		//�����PWM�������TIM3_PWM_Init(void)���
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
void IndexLED_Init(uint32_t GPIO_CLK,IndexLED_TypeDef *IndexLED)
{ 
	/* Enable the GPIO_LED Clock*/ 
	RCC_APB2PeriphClockCmd(GPIO_CLK, ENABLE);
	/* Configure the GPIO_LED pin */
	GPIO_Init(IndexLED->GPIOX, &IndexLED->GPIO_InitStructure);	
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
void VoltageLevel_Input_Init(uint32_t GPIO_CLK,VoltageLevel_TypeDef *Input)
{ 
	/* Enable the GPIO_LED Clock*/ 
	RCC_APB2PeriphClockCmd(GPIO_CLK, ENABLE);
	/* Configure the GPIO_LED pin */
	GPIO_Init(Input->GPIOX, &Input->GPIO_InitStructure);	
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
void Buzzer_Init(uint32_t GPIO_CLK,Buzzer_TypeDef *Buzzer)
{
	/* Enable the GPIO_LED Clock*/ 
	RCC_APB2PeriphClockCmd(GPIO_CLK, ENABLE);
	/* Configure the GPIO_LED pin */
	GPIO_Init(Buzzer->GPIOX, &Buzzer->GPIO_InitStructure);	
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������XXXXxxxxxxx
** ����˵������ڲ���ֻ������GPIO�ڵ�ָʾ����Ӧ�Ķ�ʱ��ָʾ��IO��ӳ����Ҫ�ں���
			��ʱ�е���,ʱ������Ҳ��Ҫ��Ӧ����
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
void PropertionalSolenoid_Init(uint32_t GPIO_CLK,PropertionalSolenoid_TypeDef *Solenoid)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* TIM3 clock enable */
	//PCLK1����2��Ƶ����ΪTIM2��ʱ��Դ����72MHz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //����TIM3��ʱ��
	/* GPIOC clock enable */
	RCC_APB2PeriphClockCmd(GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);  //����C��ʱ��
	
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
	TIM_TimeBaseStructure.TIM_Period =PWM_Period;// PWM_Period;//1000;//14400-1;     //����ʱ����0������59999����Ϊ60000�Σ�Ϊһ����ʱ����  14400~5000Hz
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//65535;//0;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
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
//void PilotValve_Init(PilotValve_TypeDef *PilotValve)
//{
//
//}

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
//void MainValve_Init(MainValve_TypeDef *MainValve)
//{
//
//}

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
//void LVDT_PositionSenser_Init(GPIO_TypeDef *GPIOx,LVDT_PositionSenser_TypeDef *LVDT_PositionSenser)
//{
//
//}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������
** ����˵����DMA��ʽAD�ɼ�,��Ӧ��DMAͨ����ADͨ��Ҫ��Ӧ
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
** �� �� ����XXXXXXXXXXX
** ����������
** ����˵����DMA��ʽAD�ɼ�,��Ӧ��DMAͨ����ADͨ��Ҫ��Ӧ
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
//	DMA_InitStructure.DMA_PeripheralBaseAddr = 0x4001244C;//ADC1�Ĺ������ݼĴ�����ַ
//	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&VoltageSenser->Voltage;	//ADת���������Ŀ��洢��ַ
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
//void TemperatureSenser_Init(GPIO_TypeDef *GPIOx,TemperatureSenser_TypeDef *TemperatureSenser)
//{
//
//}

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
//void PID_ControlParameters_Init(GPIO_TypeDef *GPIOx,PID_ControlParameters_TypeDef *PID_ControlParameters)
//{
//
//}
