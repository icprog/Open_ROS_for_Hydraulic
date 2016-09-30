/******************* (C) COPYRIGHT 2015 ZJU-StormLand *************************
**               		      ROS_hydraulic
**					  ROS_hydraulic_Init_for_PeriphChip.c
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
#include "ROS_hydraulic_Init_for_PeriphChip.h"
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
** ��    �ߣ���־��
** ����ʱ�䣺2010-5-1
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
void ROS_HY_Init_PeriphChip(void)
{
	MAX197_Init();
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
** ��    �ߣ���־��
** ����ʱ�䣺2010-5-1
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
void DelayNs(uint8_t t)
{ 
  	uint8_t i,j;
  	for(i=0; i<t; i++)
  		for(j=0; j<5; j++);
}

/******************************MAX197********************************
	��������оƬ���������ڱ����������壬����MAX197оƬ��ΪAD�ɼ�
******************************MAX197********************************/

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ������������ʼ��AD����
** ����˵����XXXXXXXXXXXXXXXXXXXX
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ���־��
** ����ʱ�䣺2010-5-1
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
void MAX197_Init(void)
{
	Set_CS_High();
	Set_WR_High();
	Set_RD_High();
}

/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������ѡ��ͨ��������ADת��
** ����˵����XXXXXXXXXXXXXXXXXXXX
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ���־��
** ����ʱ�䣺2010-5-1
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
void MAX197Write_cmd(uint8_t ch)
{
	uint8_t 	ch_data;
	GPIO_InitTypeDef GPIO_InitStructure_AD; 
	/* ����AD�ɼ�����������GPIO�ܽ�Ϊ���ģʽ*/
	GPIO_InitStructure_AD.GPIO_Pin = 0x00FF; 
	GPIO_InitStructure_AD.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure_AD.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure_AD);
	
	if(ch<2)  //����0-10V
		ch_data = (ch + 0x50) & 0xff;
	else   //���̡�10V
		ch_data = (ch + 0x58) & 0xff;
	
	MAX197_Init();
	Clr_CS_Low();
	MAX197SendData(ch_data);    //�������̺�ͨ��
	Clr_WR_Low();
	Set_WR_High();
	Set_CS_High();	

}
/********************************************************************************
** �� �� ����XXXXXXXXXXX
** ����������
** ����˵����XXXXXXXXXXXXXXXXXXXX
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ���־��
** ����ʱ�䣺2010-5-1
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
** -------------------------------------------------------------------------------
**********************************************************************************/
int32_t MAX197Read_data(void)
{	
	int32_t High_data,Low_data;
	int32_t MAX197_data;
	GPIO_InitTypeDef GPIO_InitStructure_AD; 
	/* ����AD�ɼ�����������GPIO�ܽ�Ϊ����ģʽ*/
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
** �� �� ����XXXXXXXXXXX
** ������������λƽ��ֵ�����˲�����
** ����˵����XXXXXXXXXXXXXXXXXXXX
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ���־��
** ����ʱ�䣺2010-5-1
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
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
** �� �� ����XXXXXXXXXXX
** ������������ȡͨ���ɼ�ֵ����
** ����˵����XXXXXXXXXXXXXXXXXXXX
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ���־��
** ����ʱ�䣺2010-5-1
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
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
** �� �� ����XXXXXXXXXXX
** ����������AD ��ȡ�˲�����
** ����˵����XXXXXXXXXXXXXXXXXXXX
** ȫ�ֱ�����
** ���ú�����
** ��ڲ�����
** ���ڲ�����
**
** ��    �ߣ���־��
** ����ʱ�䣺2010-5-1
** -------------------------------------------------------------------------------
** �� �� �ˣ�
** �޸�ʱ�䣺
** �޸�˵����
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