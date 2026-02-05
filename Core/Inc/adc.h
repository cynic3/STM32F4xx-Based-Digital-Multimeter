/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.h
  * @brief   This file contains all the function prototypes for
  *          the adc.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN Private defines */

#define     SAMPLE_FREQ         20000   // 采样频率


#define     SAMPLE_A_CHN       1600     //一个通道的采样数
#define     NUMBER_ADC1         3       //3个通道
#define     ADC_MAX_SIZE        (SAMPLE_A_CHN*NUMBER_ADC1)   // 一次采集的样点数

#define     ADC_MAX_VALUE       4096    // ADC 的最大值
#define     ADC_TRIG_N          32      // 将4096等分成32份
#define     TRIG_LEVEL_DIV2     ((uint16_t)(ADC_MAX_VALUE / 2 / ADC_TRIG_N ) ) // 1/2的分层电平, 四舍五入用

#define     K1         0.000806   // 直流电压，系数
#define     K2         0.275   // 交流电压，系数
#define     add        1.65    // 差值
extern double         average_in10,average_in11,average_in12,adc_in11;
extern double         display_in10,display_in11,display_in12;
extern  uint16_t  ADC_TRIG_LEVEL[ADC_TRIG_N]; // 把ADC的均值等分为 N 份, 自动获取固定的触发电平
void SendIntValue(UART_HandleTypeDef *huart, int value);

////////////////////////////////////////////////////////
extern uint16_t  ADC1_Value[ADC_MAX_SIZE];
extern double    ADC_Vdc_Volt;
extern double    ADC_Vpp_Volt;
extern int       ADC_Sin_Freq;


/* USER CODE END Private defines */

void MX_ADC1_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */

