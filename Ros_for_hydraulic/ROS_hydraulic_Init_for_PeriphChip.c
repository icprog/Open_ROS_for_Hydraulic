/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_PeriphChip.c
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
#include "ROS_hydraulic_Init_for_PeriphChip.h"
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
** 作    者：于志赣
** 创建时间：2010-5-1
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
void ROS_HY_Init_PeriphChip(void)
{
	MAX197_Init();
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
** 作    者：于志赣
** 创建时间：2010-5-1
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
void DelayNs(uint8_t t)
{ 
  	uint8_t i,j;
  	for(i=0; i<t; i++)
  		for(j=0; j<5; j++);
}

/******************************MAX197********************************
	以下外设芯片函数适用于比例阀开发板，采用MAX197芯片做为AD采集
******************************MAX197********************************/

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：初始化AD函数
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：于志赣
** 创建时间：2010-5-1
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
void MAX197_Init(void)
{
	Set_CS_High();
	Set_WR_High();
	Set_RD_High();
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：选择通道，启动AD转换
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：于志赣
** 创建时间：2010-5-1
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
void MAX197Write_cmd(uint8_t ch)
{
	uint8_t 	ch_data;
	GPIO_InitTypeDef GPIO_InitStructure_AD; 
	/* 配置AD采集的数据总线GPIO管脚为输出模式*/
	GPIO_InitStructure_AD.GPIO_Pin = 0x00FF; 
	GPIO_InitStructure_AD.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure_AD.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure_AD);
	
	if(ch<2)  //量程0-10V
		ch_data = (ch + 0x50) & 0xff;
	else   //量程±10V
		ch_data = (ch + 0x58) & 0xff;
	
	MAX197_Init();
	Clr_CS_Low();
	MAX197SendData(ch_data);    //设置量程和通道
	Clr_WR_Low();
	Set_WR_High();
	Set_CS_High();	

}
/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：于志赣
** 创建时间：2010-5-1
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
int32_t MAX197Read_data(void)
{	
	int32_t High_data,Low_data;
	int32_t MAX197_data;
	GPIO_InitTypeDef GPIO_InitStructure_AD; 
	/* 配置AD采集的数据总线GPIO管脚为输入模式*/
	GPIO_InitStructure_AD.GPIO_Pin = 0x00FF; 
	GPIO_InitStructure_AD.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	GPIO_Init(GPIOC, &GPIO_InitStructure_AD);
	
	
	while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
	{
		Clr_HBEN_Low();
	}
	
	Clr_CS_Low();
	Clr_HBEN_Low();
	Clr_RD_Low();
	Low_data = 0x00FF & GPIO_ReadInputData(GPIOC);
	Set_HBEN_High();
	DelayNs(5);
	High_data = 0x000F & GPIO_ReadInputData(GPIOC);
	Set_RD_High();
	Set_CS_High();
	MAX197_data = (int32_t)(High_data*256 + Low_data);
	return (MAX197_data);
}
/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：中位平均值数字滤波函数
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：于志赣
** 创建时间：2010-5-1
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
int32_t ADCfilters(int32_t Weiyi[],int8_t N)
{
	char i;
	int32_t sum=Weiyi[0],max=Weiyi[0],min=Weiyi[0],Averag;
	for(i=1;i<N;i++)
	   {
	   if (Weiyi[i]>max) max=Weiyi[i];
		 if (Weiyi[i]<min) min=Weiyi[i];
		 sum+=Weiyi[i];
	 }	
	Averag=(sum-max-min)/(N-2);
	return Averag;
}

/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：读取通道采集值函数
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：于志赣
** 创建时间：2010-5-1
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
int32_t Read_MAX197(uint8_t ch)
{
	uint8_t temp;
	int32_t data;
	temp = ch;	
	MAX197Write_cmd(temp);
	data = MAX197Read_data();
	return(data);
}
/********************************************************************************
** 函 数 名：XXXXXXXXXXX
** 功能描述：AD 读取滤波函数
** 其他说明：XXXXXXXXXXXXXXXXXXXX
** 全局变量：
** 调用函数：
** 入口参数：
** 出口参数：
**
** 作    者：于志赣
** 创建时间：2010-5-1
** -------------------------------------------------------------------------------
** 修 改 人：
** 修改时间：
** 修改说明：
** -------------------------------------------------------------------------------
**********************************************************************************/
int32_t Read_Port(uint8_t ch)
{ int i;
	int arv[3]={0};
	for (i=0;i<3;i++)
	{
		 arv[i]=Read_MAX197(ch);
		if((ch==3)||(ch==4))
		 if( arv[i]<2048)
          arv[i] = 10000* arv[i]/2047;  //SP>0
        else
          arv[i] = 10000*( arv[i]-4096)/2048;  //SP<0
   	}	  
  return ADCfilters(arv,3);
}
