#ifndef __LED_H__
#define __LED_H__
#include "common.h"
#include "GUI.h"

//////////////////////////////////////////
// led1引脚设置
#define RCC_LED1_GPIO_CLK_EN()  __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED1_GPIOx              GPIOF
#define pinLED1                 PIN_13
#define LED1out                 PFout
#define LED1in                  PFin

#define LED1_PINx              (1 << pinLED1)
#define LED1_ON()               LED1out(pinLED1)=1 // LED1输出"1"
#define LED1_OFF()              LED1out(pinLED1)=0 // LED1输出"0"
#define LED1_TOGGLE()           LED1out(pinLED1)=~LED1in(pinLED1)  // LED1输出取反

// led2引脚设置
#define RCC_LED2_GPIO_CLK_EN()  __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED2_GPIOx              GPIOF
#define pinLED2                 PIN_12
#define LED2out                 PFout
#define LED2in                  PFin

#define LED2_PINx              (1 << pinLED2)
#define LED2_ON()               LED2out(pinLED2)=1 // LED2输出"1"
#define LED2_OFF()              LED2out(pinLED2)=0 // LED2输出"0"
#define LED2_TOGGLE()           LED2out(pinLED2)=~LED2in(pinLED2)  // LED2输出取反

// led3引脚设置
#define RCC_LED3_GPIO_CLK_EN()  __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED3_GPIOx              GPIOF
#define pinLED3                 PIN_11
#define LED3out                 PFout
#define LED3in                  PFin

#define LED3_PINx              (1 << pinLED3)
#define LED3_ON()               LED3out(pinLED3)=1 // LED3输出"1"
#define LED3_OFF()              LED3out(pinLED3)=0 // LED3输出"0"
#define LED3_TOGGLE()           LED3out(pinLED3)=~LED3in(pinLED3)  // LED3输出取反

// led4引脚设置
#define RCC_LED4_GPIO_CLK_EN()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED4_GPIOx              GPIOB
#define pinLED4                 PIN_1
#define LED4out                 PBout
#define LED4in                  PBin

#define LED4_PINx              (1 << pinLED4)
#define LED4_ON()               LED4out(pinLED4)=1 // LED4输出"1"
#define LED4_OFF()              LED4out(pinLED4)=0 // LED4输出"0"
#define LED4_TOGGLE()           LED4out(pinLED4)=~LED4in(pinLED4)  // LED4输出取反

// PF0 引脚设置
#define RCC_PF0_GPIO_CLK_EN()  __HAL_RCC_GPIOF_CLK_ENABLE()
#define PF0_GPIOx              GPIOF
#define pinPF0                 PIN_0
#define PF0out                 PFout
#define PF0in                  PFin

#define PF0_PINx              (1 << pinPF0)
#define PF0_ON()               PF0out(pinPF0)=1 // PF1输出"1"
#define PF0_OFF()              PF0out(pinPF0)=0 // PF1输出"0"
#define PF0_TOGGLE()           PF0out(pinPF0)=~PF0in(pinPF0)  // PF1输出取反
//////////////////////////////////////////

#define LED_ALL_OFF()          do{ \
                                    LED1_OFF();\
                                    LED2_OFF();\
                                    LED3_OFF();\
                                    LED4_OFF();\
                                }while(0)

#define LED_ALL_ON()           do{ \
                                    LED1_ON();\
                                    LED2_ON();\
                                    LED3_ON();\
                                    LED4_ON();\
                                }while(0)

////////////////////////////////////////////////////////////////////////////////////
#define LCD_X1        800
#define LCD_Y1        230    // 第一个圆的圆心坐标
#define LCD_R         25     // 圆的半径
#define R_R          (LCD_R * 2 + 15)
                                
#define LCD_X2        LCD_X1
#define LCD_Y2       (LCD_Y1 + R_R)
                                
#define LCD_X3        LCD_X1
#define LCD_Y3       (LCD_Y2 + R_R)

#define LCD_X4        LCD_X1
#define LCD_Y4       (LCD_Y3 + R_R)

#define LCD1_ON()     Gui_Circle_Fill(LCD_X1, LCD_Y1, LCD_R, RED_4_4)   // 第一个圆 亮
#define LCD1_OFF()    Gui_Circle_Fill(LCD_X1, LCD_Y1, LCD_R, WHITE_4_4) // 第一个圆 不亮
                                
#define LCD2_ON()     Gui_Circle_Fill(LCD_X2, LCD_Y2, LCD_R, RED_4_4)   // 第2个圆 亮
#define LCD2_OFF()    Gui_Circle_Fill(LCD_X2, LCD_Y2, LCD_R, WHITE_4_4) // 第2个圆 不亮

#define LCD3_ON()     Gui_Circle_Fill(LCD_X3, LCD_Y3, LCD_R, RED_4_4)   // 第3个圆 亮
#define LCD3_OFF()    Gui_Circle_Fill(LCD_X3, LCD_Y3, LCD_R, WHITE_4_4) // 第3个圆 不亮

#define LCD4_ON()     Gui_Circle_Fill(LCD_X4, LCD_Y4, LCD_R, RED_4_4)   // 第4个圆 亮
#define LCD4_OFF()    Gui_Circle_Fill(LCD_X4, LCD_Y4, LCD_R, WHITE_4_4) // 第4个圆 不亮

#define LCD_ALL_OFF()          do{ \
                                    LCD1_OFF();\
                                    LCD2_OFF();\
                                    LCD3_OFF();\
                                    LCD4_OFF();\
                                 }while(0)

//#define LCD_R       20    // 半径
//#define LCD_X1      800   // 圆心1 X
//#define LCD_Y1      230   // 圆心1 Y
//#define LCD_HEIGHT  (LCD_R * 2 + 20) // 上下圆 圆心距离
//                                
//#define LCD_X2      LCD_X1   // 圆心2 X
//#define LCD_Y2      (LCD_Y1 + LCD_HEIGHT)  // 圆心2 Y
//                                
//#define LCD_X3      LCD_X1   // 圆心3 X
//#define LCD_Y3      (LCD_Y2 + LCD_HEIGHT)  // 圆心3 Y
//                                
//#define LCD_X4      LCD_X1   // 圆心4 X
//#define LCD_Y4      (LCD_Y3 + LCD_HEIGHT)  // 圆心4 Y
//                                
//// 第一个圆
//#define LCD1_ON()   Gui_Circle_Fill(LCD_X1, LCD_Y1, LCD_R, RED_4_4)
//#define LCD1_OFF()  Gui_Circle_Fill(LCD_X1, LCD_Y1, LCD_R, WHITE_4_4)
//// 第二个圆
//#define LCD2_ON()   Gui_Circle_Fill(LCD_X2, LCD_Y2, LCD_R, RED_4_4)
//#define LCD2_OFF()  Gui_Circle_Fill(LCD_X2, LCD_Y2, LCD_R, WHITE_4_4)
//// 第3个圆
//#define LCD3_ON()   Gui_Circle_Fill(LCD_X3, LCD_Y3, LCD_R, RED_4_4)
//#define LCD3_OFF()  Gui_Circle_Fill(LCD_X3, LCD_Y3, LCD_R, WHITE_4_4)
//// 第4个圆
//#define LCD4_ON()   Gui_Circle_Fill(LCD_X4, LCD_Y4, LCD_R, RED_4_4)
//#define LCD4_OFF()  Gui_Circle_Fill(LCD_X4, LCD_Y4, LCD_R, WHITE_4_4)

//#define LCD_ALL_OFF()          do{ \
//                                    LCD1_OFF();\
//                                    LCD2_OFF();\
//                                    LCD3_OFF();\
//                                    LCD4_OFF();\
//                                }while(0)

//#define LCD_ALL_ON()           do{ \
//                                    LCD1_ON();\
//                                    LCD2_ON();\
//                                    LCD3_ON();\
//                                    LCD4_ON();\
//                                }while(0)

////////////////////////////////////////////////////////////////////////////////////
void LED_GPIO_Init(void);
void LED_LCD_Disp(void);
////////////////////////////////////////////////////////////////////////////////////

#endif

