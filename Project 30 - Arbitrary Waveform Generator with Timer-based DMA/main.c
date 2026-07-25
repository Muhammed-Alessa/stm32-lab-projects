/*
 * Arbitrary Waveform Generator with Timer-based DMA
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
 * CubeMX-assisted F446RE version:
 *   DAC channel 1 -> PA4
 *   timer trigger -> TIM6 TRGO
 *   DMA           -> DAC channel 1, circular mode
 *
 * Generate the peripheral initialization in CubeIDE, then use the application
 * logic below in USER CODE. This avoids hard-coding DMA stream details that
 * can differ with CubeF4 configuration choices.
 */
static const uint16_t wave[16] = {
    2048,2831,3496,3939,4095,3939,3496,2831,
    2048,1265,600,157,0,157,600,1265
};

int main(void)
{
    HAL_Init(); SystemClock_Config();

    /* MX_GPIO_Init(); MX_DMA_Init(); MX_DAC_Init(); MX_TIM6_Init(); */

    /* HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(uint32_t*)wave,16,DAC_ALIGN_12B_R);
       HAL_TIM_Base_Start(&htim6); */

    while (1) __WFI();
}
