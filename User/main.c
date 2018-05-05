/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ADC�ɼ���ѹ����ͨ����DMAģʽ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */


#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./adc/bsp_adc.h"


// ADCת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue[RHEOSTAT_NOFCHANEL];

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal[RHEOSTAT_NOFCHANEL]={0}; 

static void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  /*��ʼ��USART1*/
  Debug_USART_Config();

  /* ��ʼ�������������õ���DAC ��ADC���ݲɼ���ɺ�ֱ����DMA�������ݵ�ADC_ConvertedValue����
      DMAֱ�Ӹı�ADC_ConvertedValue��ֵ*/
  Rheostat_Init();

  printf("\r\n ----����һ��ADCʵ��(��ͨ���ɼ�)----\r\n");

  while (1)
  {
    Delay(0xffffff);  
    ADC_ConvertedValueLocal[0]=(float)(ADC_ConvertedValue[0]*3.3/4096);
    ADC_ConvertedValueLocal[1]=(float)(ADC_ConvertedValue[1]*3.3/4096);
    ADC_ConvertedValueLocal[2]=(float)(ADC_ConvertedValue[2]*3.3/4096);
    ADC_ConvertedValueLocal[3]=(float)(ADC_ConvertedValue[3]*3.3/4096);
    
    printf("\r\n CH1_PF6 value = %fV\r\n",ADC_ConvertedValueLocal[0]);
    printf("\r\n CH2_PF7 value = %fV\r\n",ADC_ConvertedValueLocal[1]);
    printf("\r\n CH3_PF8 value = %fV\r\n",ADC_ConvertedValueLocal[2]);
    printf("\r\n CH4_PF9 value = %fV\r\n",ADC_ConvertedValueLocal[3]);
    
    printf("\r\n");    
  }
}

static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

/*********************************************END OF FILE**********************/

