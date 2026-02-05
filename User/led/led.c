#include "led.h"

// LED引脚初始化函数
void LED_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    
    // LED1引脚初始化
    RCC_LED1_GPIO_CLK_EN();
    GPIO_InitStruct.Pin = LED1_PINx;
    HAL_GPIO_Init(LED1_GPIOx, &GPIO_InitStruct);
    
    // LED2引脚初始化
    RCC_LED2_GPIO_CLK_EN();
    GPIO_InitStruct.Pin = LED2_PINx;
    HAL_GPIO_Init(LED2_GPIOx, &GPIO_InitStruct);
    
    // LED3引脚初始化
    RCC_LED3_GPIO_CLK_EN();
    GPIO_InitStruct.Pin = LED3_PINx;
    HAL_GPIO_Init(LED3_GPIOx, &GPIO_InitStruct);
    
    // LED4引脚初始化
    RCC_LED4_GPIO_CLK_EN();
    GPIO_InitStruct.Pin = LED4_PINx;
    HAL_GPIO_Init(LED4_GPIOx, &GPIO_InitStruct);
    
    LED_ALL_OFF();
    
    // PF0引脚初始化
    RCC_PF0_GPIO_CLK_EN();
    GPIO_InitStruct.Pin = PF0_PINx;
    HAL_GPIO_Init(PF0_GPIOx, &GPIO_InitStruct);
}

// 根据code 点亮某一个 LED 和 LCD
void Disp_LED_LCD(int code)
{
    LED_ALL_OFF(); // 关闭所有的LED
    LCD_ALL_OFF(); // 所有的圆显示白色
    
    switch(code)
    {
        case 1: { LED1_ON(); LCD1_ON(); break; }
        case 2: { LED2_ON(); LCD2_ON(); break; }
        case 3: { LED3_ON(); LCD3_ON(); break; }
        case 4: { LED4_ON(); LCD4_ON(); break; }
        default: break;
    }
}

void LED_LCD_Run(int dlyms)
{
    int i;
    
    for (i=1; i<5; i++)
    {   // 顺向流动
        Disp_LED_LCD(i);
        HAL_Delay(dlyms);
    }
    for (i=3; i>1; i--)
    {   // 反向流动
        Disp_LED_LCD(i);
        HAL_Delay(dlyms);
    }
}

void LED_LCD_Disp(void)
{
    Gui_Draw_Asc32_String(750, 120, WHITE_4_4, BLUE_4_4, (uint8_t*)"B"); // 显示 "B"
    LED_LCD_Run(1000); // B过程
    
    Gui_Draw_Asc32_String(750, 120, WHITE_4_4, BLUE_4_4, (uint8_t*)"C"); // 显示 "C"
    LED_LCD_Run(2000); // C过程
    
    Gui_Draw_Asc32_String(750, 120, WHITE_4_4, BLUE_4_4, (uint8_t*)"D"); // 显示 "D"
    LED_LCD_Run(3000); // D过程
}


//// 显示一个LED 及 对应的LCD圆
//void Disp_A_LED_LCD(int code)
//{
//    LED_ALL_OFF();
//    LCD_ALL_OFF();
//    
//    switch(code)
//    {
//        case 1:{ LED1_ON(); LCD1_ON(); break; }
//        case 2:{ LED2_ON(); LCD2_ON(); break; }
//        case 3:{ LED3_ON(); LCD3_ON(); break; }
//        case 4:{ LED4_ON(); LCD4_ON(); break; }
//        default: break;
//    }
//}

//void LED_LCD_Run(int dlyms)
//{
//    int ledcode;
//    
//    for(ledcode=1; ledcode<5; ledcode++)  // 顺向流动
//    {
//        Disp_A_LED_LCD(ledcode);  // 根据编号，显示一个圆
//        HAL_Delay(dlyms);         // 延时 dlyms 毫秒
//    }
//    
//    for(ledcode=3; ledcode>1; ledcode--)  // 往回流动
//    {
//        Disp_A_LED_LCD(ledcode);  // 根据编号，显示一个圆
//        HAL_Delay(dlyms);         // 延时 dlyms 毫秒
//    }
//}

//void LED_LCD_Disp(void)
//{
//    Gui_Draw_Asc32_String(750, 120, WHITE_4_4, BLUE_4_4, (uint8_t*)"B"); // 显示 题号
//    LED_LCD_Run(1000); // 运行B过程
//    
//    Gui_Draw_Asc32_String(750, 120, WHITE_4_4, BLUE_4_4, (uint8_t*)"C"); // 显示 题号
//    LED_LCD_Run(2000); // 运行C过程
//    
//    Gui_Draw_Asc32_String(750, 120, WHITE_4_4, BLUE_4_4, (uint8_t*)"D"); // 显示 题号
//    LED_LCD_Run(3000); // 运行D过程
//}








