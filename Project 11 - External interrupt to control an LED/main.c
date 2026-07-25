/*
 * External interrupt to control an LED
 * Target: NUCLEO-F446RE / STM32F446RET6
 * Framework: STM32CubeF4 HAL
 *
 * Independently rewritten for the F446RE board.
 * This is not a copy of the book's program listing.
 */
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    __HAL_RCC_PWR_CLK_ENABLE();

    osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    osc.HSIState = RCC_HSI_ON;
    osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    osc.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&osc) != HAL_OK) {
        while (1) {}
    }

    clk.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                    RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV1;
    clk.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_0) != HAL_OK) {
        while (1) {}
    }
}

void EXTI15_10_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13); }
void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
    if (pin == GPIO_PIN_13) HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
static void IO_Init(void)
{
    GPIO_InitTypeDef g={0};
    __HAL_RCC_GPIOA_CLK_ENABLE(); __HAL_RCC_GPIOC_CLK_ENABLE(); __HAL_RCC_SYSCFG_CLK_ENABLE();
    g.Pin=GPIO_PIN_5; g.Mode=GPIO_MODE_OUTPUT_PP; g.Pull=GPIO_NOPULL; HAL_GPIO_Init(GPIOA,&g);
    g.Pin=GPIO_PIN_13; g.Mode=GPIO_MODE_IT_FALLING; HAL_GPIO_Init(GPIOC,&g);
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,0); HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
int main(void)
{
    HAL_Init(); SystemClock_Config(); IO_Init();
    while (1) __WFI();
}
