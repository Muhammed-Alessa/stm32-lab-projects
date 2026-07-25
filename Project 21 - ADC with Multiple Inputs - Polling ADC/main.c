/*
 * ADC with Multiple Inputs - Polling ADC
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

/*
 * F446RE CubeMX-assisted ADC example.
 *
 * PA0 = ADC1_IN0
 * PA1 = ADC1_IN1
 *
 * Configure ADC1 in STM32CubeIDE/CubeMX for the mode named by this project.
 * For the DMA project, add DMA2 Stream0 Channel0 in circular mode.
 * For the interrupt project, enable ADC_IRQn.
 *
 * Keep the generated MX_ADC1_Init()/MX_DMA_Init() functions and put your
 * application processing in the USER CODE sections. This keeps the project
 * matched to the exact STM32CubeF4 package version you have installed.
 */
volatile uint16_t adc_values[2];

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1) {
        /* adc_values now contains the completed sample(s). */
    }
}

int main(void)
{
    HAL_Init(); SystemClock_Config();

    /* Call the CubeMX-generated initialization functions here:
       MX_GPIO_Init();
       MX_DMA_Init();     // DMA project only
       MX_ADC1_Init();
    */

    while (1) {
        __WFI();
    }
}
