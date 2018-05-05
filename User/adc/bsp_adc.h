#ifndef __ADC_H
#define	__ADC_H


#include "stm32f4xx.h"

// RHEOSTAT: 滑动变阻器/电位器
// 四通道ADC采集

//转换的通道个数
#define RHEOSTAT_NOFCHANEL      4

#define RHEOSTAT_ADC_DR_ADDR     ((u32)ADC3+0x4c)
#define RHEOSTAT_ADC_GPIO_PORT    GPIOF
#define RHEOSTAT_ADC_GPIO_CLK     RCC_AHB1Periph_GPIOF
#define RHEOSTAT_ADC              ADC3
#define RHEOSTAT_ADC_CLK          RCC_APB2Periph_ADC3

#define RHEOSTAT_ADC_GPIO_PIN1    GPIO_Pin_6
#define RHEOSTAT_ADC_CHANNEL1     ADC_Channel_4

#define RHEOSTAT_ADC_GPIO_PIN2    GPIO_Pin_7
#define RHEOSTAT_ADC_CHANNEL2     ADC_Channel_5

#define RHEOSTAT_ADC_GPIO_PIN3    GPIO_Pin_8
#define RHEOSTAT_ADC_CHANNEL3     ADC_Channel_6

#define RHEOSTAT_ADC_GPIO_PIN4    GPIO_Pin_9
#define RHEOSTAT_ADC_CHANNEL4     ADC_Channel_7

// DMA2 数据流0 通道2
#define RHEOSTAT_ADC_DMA_CLK      RCC_AHB1Periph_DMA2
#define RHEOSTAT_ADC_DMA_CHANNEL  DMA_Channel_2
#define RHEOSTAT_ADC_DMA_STREAM   DMA2_Stream0

void Rheostat_Init(void);


#endif /* __ADC_H */

