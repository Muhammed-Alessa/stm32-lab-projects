/*
 * Timer Interrupt to Flash LED Every Second
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

static TIM_HandleTypeDef htim2;
void TIM2_IRQHandler(void) { HAL_TIM_IRQHandler(&htim2); }
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *h)
{
    if (h->Instance == TIM2) HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
int main(void)
{
    HAL_Init(); SystemClock_Config();

    GPIO_InitTypeDef g={0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    g.Pin=GPIO_PIN_5; g.Mode=GPIO_MODE_OUTPUT_PP; g.Pull=GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA,&g);

    __HAL_RCC_TIM2_CLK_ENABLE();
    htim2.Instance=TIM2; htim2.Init.Prescaler=15999; htim2.Init.CounterMode=TIM_COUNTERMODE_UP;
    htim2.Init.Period=999; htim2.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htim2);
    HAL_NVIC_SetPriority(TIM2_IRQn,1,0); HAL_NVIC_EnableIRQ(TIM2_IRQn);
    HAL_TIM_Base_Start_IT(&htim2);

    while (1) __WFI();
}
