/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc.c
  * @brief   This file provides code for the configuration
  *          of the ADC instances.
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
/* Includes ------------------------------------------------------------------*/
#include "adc.h"

/* USER CODE BEGIN 0 */
#include  "math.h"
#include "stdint.h"
#include  "tftDisp.h"
#include  "touch.h"
uint16_t  ADC1_Value[ADC_MAX_SIZE];
uint16_t  ADC_TRIG_LEVEL[ADC_TRIG_N]; // 把ADC的均值等分为 N 份, 自动获取固定的触发电平

/* USER CODE END 0 */

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hadc1.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 3;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_12;
  sConfig.Rank = 3;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN10
    PC1     ------> ADC1_IN11
    PC2     ------> ADC1_IN12
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA2_Stream0;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(adcHandle,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PC0     ------> ADC1_IN10
    PC1     ------> ADC1_IN11
    PC2     ------> ADC1_IN12
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(adcHandle->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
// 获取触发点的坐标值， 返回是否找到匹配值
ErrorStatus Find_Match_Trig_Value(uint16_t *scr, uint16_t start, uint16_t end, uint16_t matchval, uint16_t *trigX)
{    
    int         i;
    ErrorStatus result = ERROR;
    
    for(i=(start+1); i<end; i++)
    {
        if( (scr[i-1] < (matchval-1)) && (scr[i+1] > (matchval+1)) ) 
        {
            *trigX  = i;
            result = SUCCESS;
            break;
        }
    }
    return result;
}

// 求周期内均值
uint16_t  Get_Average(uint16_t *scr, uint16_t start, uint16_t end)
{
    int  i, sum;
    uint16_t average;
    
    sum =0;
    for(i=start; i<end; i++)
    {
        sum += scr[i];
    }
    average = (uint16_t)(sum / (end - start)); // 求均值
    return average;
}

// 求取样点均值
uint16_t  Average(uint16_t *scr)
{
    int  i, sum;
    uint16_t average;
    
    sum =0;
    for(i=0; i<SAMPLE_A_CHN; i++)
    {
        sum += scr[i];
    }
    average = (uint16_t)((double)sum / SAMPLE_A_CHN); // 求均值
    return average;
}
//求交流电压数据值
//uint16_t  vdget(uint16_t average,uint16_t *scr)
//{
//	  int   i,sum;
//	  uint16_t adc,adcbuf;
//	  sum=0;
//	  for(i=0; i<SAMPLE_A_CHN; i++)
//	  {  
//			 sum+=(scr[i]-average)*(scr[i]-average);
//		}
//		adcbuf=(uint16_t)(sum/SAMPLE_A_CHN);
//		adc=sqrt(adcbuf);
//		return adc;
//}

//
uint16_t vdget(uint16_t average, uint16_t *scr)
{
    int i;
    double sum = 0.0; // 使用long long int避免整数溢出
    double rms, avg_square_diff; // 使用浮点数类型存储方均根

    for (i = 0; i < SAMPLE_A_CHN; i++)
    {
        sum += ((int)scr[i] - (int)average) * ((int)scr[i] - (int)average);
    }

    // 计算平均平方差
    avg_square_diff = sum / SAMPLE_A_CHN;

    // 计算方均根
    rms = sqrt(avg_square_diff);

    // 将浮点数的方均根转换为uint16_t类型
    // 注意：这里可能会有精度损失
    uint16_t adc = (uint16_t)(rms + 0.5f); // 使用四舍五入

//    // 检查adc是否在合理范围内
//    if (adc > UINT16_MAX)
//    {
//        adc = UINT16_MAX;
//    }

    return adc;
}

// 求峰峰值，返回电压等级值
uint16_t  Get_Vpp(uint16_t *scr, uint16_t start, uint16_t end)
{
    uint16_t    i, maxvalue, minvalue;
    
    maxvalue = 0;
    minvalue = 50000;
    for(i=start; i<end; i++)
    {
        if(scr[i] > maxvalue)
        {
            maxvalue = scr[i];
        }
            
        if(scr[i] < minvalue)
        {
            minvalue = scr[i];
        }
    }
    return (maxvalue - minvalue);
}

// 将电压等级值转换为电压值
double  Get_Voltage(uint16_t level)
{
    double  volt;
    volt = (double)level * 3.3 / 4095;
    return volt;
}

// 根据均值计算选择一个固定的触发电平，避免均值抖动引起波形的抖动
uint16_t Get_Now_Trig_Level(uint16_t avg)
{
    uint16_t  i, triglevel;
    

    if(avg < (ADC_TRIG_LEVEL[0] + TRIG_LEVEL_DIV2))
    {
        triglevel = ADC_TRIG_LEVEL[0] + TRIG_LEVEL_DIV2 / 2;
    }
    else if(avg > (ADC_TRIG_LEVEL[ADC_TRIG_N-1] + TRIG_LEVEL_DIV2))
    {
        triglevel = ADC_TRIG_LEVEL[ADC_TRIG_N-1] + TRIG_LEVEL_DIV2 + TRIG_LEVEL_DIV2 / 2;
    }
    else
    {
        for(i=1; i<ADC_TRIG_N; i++)
        {
            if( (avg >= (ADC_TRIG_LEVEL[i] - TRIG_LEVEL_DIV2 - 2)) && \
                (avg <  (ADC_TRIG_LEVEL[i] + TRIG_LEVEL_DIV2 + 2)) 
              )
            {
                triglevel = ADC_TRIG_LEVEL[i];
                break;
            }
        }
    }
    return triglevel;
}

static uint16_t lasttriglevel=0;
static uint16_t lastavglevel=0;
static uint16_t newtrig=0;
uint16_t  Get_Trig_Level(uint16_t *scr, uint16_t scrsize)
{
    uint16_t  i, nowtriglevel, nowavglevel;
    int       dltavg;
    
    nowavglevel = Get_Average(scr, 0, scrsize);
    if(newtrig == 0) // 第一次执行
    {
        newtrig = 1;
        
        for(i=0; i<ADC_TRIG_N; i++)
        {   // 计算各个触发电平的等级值, 只计算一次
            ADC_TRIG_LEVEL[i] = ADC_MAX_VALUE * i / ADC_TRIG_N;
        }
        nowtriglevel  = Get_Now_Trig_Level(nowavglevel);
    }
    else
    {   // 第一次以后的所有执行次数
        nowtriglevel = Get_Now_Trig_Level(nowavglevel);
        if(nowtriglevel != lasttriglevel)
        {   // 如果前后2次的触发电平不一样，但是电平等级差在+-20之内，就不改变触发电平，避免波形在触发电平位于交界点时抖动
            dltavg = (int)nowavglevel - (int)lastavglevel;
            if( (dltavg < 20) || (dltavg > -20) )
            {
                nowtriglevel = lasttriglevel;
            }
        }
    }
    lasttriglevel = nowtriglevel;
    lastavglevel  = nowavglevel;
    
    return nowtriglevel;
}

////////////////////////////////////////////////////////////////////////////
double         average_in10,average_in11,average_in12,adc_in11;
double         display_in10,display_in11,display_in12;
// ADC 转换完成中断回调函数 ,不是指ADC一次中断一次而是ADC转换填满了数组 ADC1_Value 后，触发DMA中断后的回调函数
double  ADC_Vdc_Volt;  // ADC测量得到的直流电压
double  ADC_Vpp_Volt;  // ADC测量得到的峰峰电压
int     ADC_Sin_Freq;  // ADC测量得到的正弦波频率
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{   int            i;
    uint16_t    adcbuf_in10[SAMPLE_A_CHN];
    uint16_t    adcbuf_in11[SAMPLE_A_CHN];
    uint16_t    adcbuf_in12[SAMPLE_A_CHN];
    
    if(hadc->DMA_Handle->Instance == DMA2_Stream0)
    {
        for (i=0; i<SAMPLE_A_CHN; i++)
        {
            adcbuf_in10[i] = ADC1_Value[i*NUMBER_ADC1];    // 保存原始数据 ADC1_in10
            adcbuf_in11[i] = ADC1_Value[i*NUMBER_ADC1+1];  // 保存原始数据 ADC1_in11
            adcbuf_in12[i] = ADC1_Value[i*NUMBER_ADC1+2];  // 保存原始数据 ADC1_in12
        }

        average_in10      = Average(adcbuf_in10); // ADC1_in10 均值
        average_in11      = Average(adcbuf_in11); // ADC1_in11 均值
        average_in12      = Average(adcbuf_in12); // ADC1_in12 均值
				
				adc_in11          = vdget(average_in11,adcbuf_in11);//ADC_in12数据值
				
				display_in10      = 0.007996*average_in10-16.477409;
				display_in11      =0.00839*adc_in11;
				display_in12      =0.0008*average_in12-1.649859;
				
				if(Disp_ADC==1)
				{	
				Disp_ADC_in10(20, 450,display_in10);
				}
				if(Disp_ADC==2)
				{
					Disp_ADC_in11(20, 450,display_in11);
				}
				if(Disp_ADC==3)
				{
					Disp_ADC_in12(20, 450,display_in12);
				}

    } 

}
void SendIntValue(UART_HandleTypeDef *huart, int value)
	{
    char buffer[10]; // 足够存储32位整数及其符号
    int len = sprintf(buffer, "%d", value); // 转换整数为字符串
    HAL_UART_Transmit(huart, (uint8_t *)buffer, len, HAL_MAX_DELAY); // 发送字符串
  }
  

/* USER CODE END 1 */
