/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "led.h"
#include "w25q64.h"
#include "tftDisp.h"
#include "time_drive.h"
#include "key.h"
#include  "touch.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
struTouch  touch={{999,999}, NO_TOUCH, X_NO_MOVING, Y_NO_MOVING, 0,0, 0};

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_FSMC_Init();
  MX_SPI2_Init();
  MX_TIM2_Init();
  MX_TIM7_Init();
  MX_USART1_UART_Init();
  MX_TIM6_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();

  /* Initialize interrupts */
    MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
    LED_GPIO_Init();               // LED引脚初始化
    W25Q64_CS_GPIO_Init();         // 字库芯片W25Q64的 "/CS" 引脚初始化
    LCD_Initialize();              // LCD屏幕 硬件和 软件的初始化
    
    HAL_TIM_Base_Start_IT(&htim7); // 定时器7开始计数，并使能计数溢出中断
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);  // 定时器2开始计数,产生PWM信号
    KEY_GPIO_Init();               // 按键引脚初始化
    KEY_Param_Init(&Key);          // 初始化按键状态
    
    FT6336_I2C_GPIO_Init();        // 触摸屏引脚初始化
		MX_USART1_UART_Init();         //串口初始化
    
    Draw_Main_Win();
   
    Gui_Draw_Asc16_Hzk16(0, 0,  RED_4_4, BLACK, (uint8_t*)" ");
    
    HAL_UARTEx_ReceiveToIdle_DMA(&huart1, U1_Rx_Buf, U1_REC_MAX); // 设置串口1的接收条件
    U1_Rx_Success=ERROR;
    
    //****************************************************************
    // 以下完成 ADC 设置
    // 画出万用表界面显示框
   
    // 设置ADC1_IN10经触发进行ADC, 数据通过DMA2_stream0 通道传输到 ADC1_Value
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC1_Value, ADC_MAX_SIZE);
    
    // 启动TIM3计数，update事件触发ADC;
    Set_TIMx_Freq(&htim3, SAMPLE_FREQ); // 设置tim3的触发频率, ADC采样频率为20KHz
    HAL_TIM_Base_Start(&htim3);

  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	  HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 100);
    uint32_t adcValue = HAL_ADC_GetValue(&hadc1); // 获取ADC值

    // 发送ADC值
    SendIntValue(&huart1, adcValue);
  while (1)
  {     if(Read_Key_Enable == ENABLE)
        {
            ReadCTP(&touch);       // 读取触屏状态及坐标等
            Touch_Disp_XY(&touch); // 显示触点坐标
            Touch_Process(&touch); // 处理触摸屏
				}
       if(U1_Rx_Success == SUCCESS) // 串口成功接收一帧数据
       {
           U1_Rx_Success = ERROR;
           U1_Process(U1_Rx_Buf, U1_IDLE_Rxed_Num);
           HAL_UARTEx_ReceiveToIdle_DMA(&huart1, U1_Rx_Buf, U1_REC_MAX); // 设置串口1的接收条件
    
       }
       
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* TIM7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM7_IRQn, 7, 0);
  HAL_NVIC_EnableIRQ(TIM7_IRQn);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
