/*
 * Interrupt-Based Up-Down Counter with Four-Digit 7-Segment LED Display
 * Target: NUCLEO-F446RE / STM32F446RET6
 * Framework: STM32CubeF4 HAL
 *
 * Independently rewritten for the F446RE board.
 */
#include "stm32f4xx_hal.h"
#include <stdint.h>


static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    __HAL_RCC_PWR_CLK_ENABLE();

    osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    osc.HSIState = RCC_HSI_ON;
    osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    osc.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&osc) != HAL_OK) while (1) {}

    clk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                    RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV1;
    clk.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_0) != HAL_OK) while (1) {}
}

static const uint8_t seg_lut[10] = {
    0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F
};
static const uint16_t seg_pins[7] = {
    GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,
    GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6
};

static void Seg_Write(uint8_t p)
{
    for (uint32_t i=0;i<7;i++)
        HAL_GPIO_WritePin(GPIOC,seg_pins[i],
                          (p&(1U<<i))?GPIO_PIN_SET:GPIO_PIN_RESET);
}

static const uint16_t digit_pins[4]={GPIO_PIN_7,GPIO_PIN_8,GPIO_PIN_9,GPIO_PIN_10};

static void Display_Init(void)
{
    GPIO_InitTypeDef g={0};
    __HAL_RCC_GPIOC_CLK_ENABLE();
    g.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|
          GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10;
    g.Mode=GPIO_MODE_OUTPUT_PP; g.Pull=GPIO_NOPULL; g.Speed=GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC,&g);
}

static void Display_Number(uint32_t value)
{
    uint32_t div=1000U;
    for(uint8_t i=0;i<4;i++){
        uint8_t n=(uint8_t)((value/div)%10U);
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10,GPIO_PIN_RESET);
        Seg_Write(seg_lut[n]);
        HAL_GPIO_WritePin(GPIOC,digit_pins[i],GPIO_PIN_SET);
        HAL_Delay(3);
        div/=10U;
    }
}

static volatile int32_t value=0;

/* PA10 = UP button. PB5 = DOWN button. */
void EXTI15_10_IRQHandler(void){HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);}
void EXTI9_5_IRQHandler(void){HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);}
void HAL_GPIO_EXTI_Callback(uint16_t p)
{
    if(p==GPIO_PIN_10 && value<9999) ++value;
    if(p==GPIO_PIN_5 && value>0) --value;
}
static void Buttons_Init(void)
{
    GPIO_InitTypeDef g={0};
    __HAL_RCC_GPIOA_CLK_ENABLE(); __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    g.Pin=GPIO_PIN_10; g.Mode=GPIO_MODE_IT_FALLING; g.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA,&g);
    g.Pin=GPIO_PIN_5; HAL_GPIO_Init(GPIOB,&g);

    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,0); HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,0); HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}
int main(void)
{
    HAL_Init();SystemClock_Config();Display_Init();Buttons_Init();
    while(1) Display_Number((uint32_t)value);
}
