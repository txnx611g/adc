/**
  ******************************************************************************
  * @file    bsp_xxx.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   adc1 Ӧ��bsp / ��ͨ����DMA ģʽ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������   
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./adc/bsp_adc.h"



__IO uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL]={0};

/**
  * @brief  ����ADC��GPIO
  * @param  ��
  * @retval ��
  */
static void Rheostat_ADC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_GPIO_CLK, ENABLE);
		
	// ���� IO
  GPIO_InitStructure.GPIO_Pin = RHEOSTAT_ADC_GPIO_PIN1 | RHEOSTAT_ADC_GPIO_PIN2 |
                                RHEOSTAT_ADC_GPIO_PIN3 | RHEOSTAT_ADC_GPIO_PIN4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	    
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ; //������������
	GPIO_Init(RHEOSTAT_ADC_GPIO_PORT, &GPIO_InitStructure);			
}

/**
  * @brief  ����ADC��DMA����
  * @param  ��
  * @retval ��
  */
static void Rheostat_ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
  // ����ADCʱ��
	RCC_APB2PeriphClockCmd(RHEOSTAT_ADC_CLK , ENABLE);
	// ����DMAʱ��
  RCC_AHB1PeriphClockCmd(RHEOSTAT_ADC_DMA_CLK, ENABLE);
	
	// ------------------DMA Init �ṹ����� ��ʼ��--------------------------
	// ѡ�� DMA ͨ����ͨ����������������
  DMA_InitStructure.DMA_Channel = RHEOSTAT_ADC_DMA_CHANNEL;	
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = RHEOSTAT_ADC_DR_ADDR;	
  // �洢����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)ADC_ConvertedValue;  
	  // ���ݴ��䷽��Ϊ���赽�洢��	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	// ��������С��ָһ�δ����������
	DMA_InitStructure.DMA_BufferSize = RHEOSTAT_NOFCHANEL;		
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  // �洢����ַ����
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	//DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;	
  // // �������ݴ�СΪ���֣��������ֽ� 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;   
  //	�洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;		
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  // DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;	
  // ��ֹDMA FIFO	��ʹ��ֱ��ģʽ
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;    
  // FIFO ��ֵ��С��FIFOģʽ��ֹʱ�������������	
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	// �洢��ͻ�����δ���
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	// ����ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;	
  //��ʼ��DMA�����������൱��һ����Ĺܵ����ܵ������кܶ�ͨ��
	DMA_Init(RHEOSTAT_ADC_DMA_STREAM, &DMA_InitStructure);	
	// ʹ��DMA������
  DMA_Cmd(RHEOSTAT_ADC_DMA_STREAM, ENABLE);

  // -------------------ADC Common �ṹ�� ���� ��ʼ��------------------------
	// ����ADCģʽ
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  // ʱ��Ϊfpclk x��Ƶ	
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
  // ��ֹDMAֱ�ӷ���ģʽ	
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  // ����ʱ����	
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;  
  ADC_CommonInit(&ADC_CommonInitStructure);
	
  // -------------------ADC Init �ṹ�� ���� ��ʼ��--------------------------
  // ADC �ֱ���
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  // ����ɨ��ģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE; 
  // ����ת��	
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
  //��ֹ�ⲿ���ش���
  ADC_InitStructure.ADC_ExternalTrigConvEdge = 
                                            ADC_ExternalTrigConvEdge_None;
  //ʹ������������ⲿ�����������ã�ע�͵�����
  //ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  //�����Ҷ���	
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  //ת��ͨ�� x��
  ADC_InitStructure.ADC_NbrOfConversion = RHEOSTAT_NOFCHANEL;                                    
  ADC_Init(RHEOSTAT_ADC, &ADC_InitStructure);
  //---------------------------------------------------------------------------
  // ���� ADC ͨ��ת��˳��Ͳ���ʱ������
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL1, 1, ADC_SampleTime_56Cycles);
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL2, 2, ADC_SampleTime_56Cycles); 
  ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL3, 3, ADC_SampleTime_56Cycles); 
	ADC_RegularChannelConfig(RHEOSTAT_ADC, RHEOSTAT_ADC_CHANNEL4, 4, ADC_SampleTime_56Cycles); 
  // ʹ��DMA���� after last transfer (Single-ADC mode)
  ADC_DMARequestAfterLastTransferCmd(RHEOSTAT_ADC, ENABLE);
  // ʹ��ADC DMA
  ADC_DMACmd(RHEOSTAT_ADC, ENABLE);
  // ʹ��ADC
  ADC_Cmd(RHEOSTAT_ADC, ENABLE);  
  //��ʼadcת�����������
  ADC_SoftwareStartConv(RHEOSTAT_ADC);
}

/**
  * @brief  ADC1��ʼ��
  * @param  ��
  * @retval ��
  */
void Rheostat_Init(void)
{
	Rheostat_ADC_GPIO_Config();
	Rheostat_ADC_Mode_Config();
}
/*********************************************END OF FILE**********************/
