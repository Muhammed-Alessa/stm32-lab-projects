/*
 * Sawtooth Waveform Generator with Manual DAC Driving
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

static DAC_HandleTypeDef hdac;

static void DAC1_Init(void)
{
    GPIO_InitTypeDef g = {0};
    DAC_ChannelConfTypeDef c = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_DAC_CLK_ENABLE();

    g.Pin = GPIO_PIN_4;
    g.Mode = GPIO_MODE_ANALOG;
    g.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &g);

    hdac.Instance = DAC;
    HAL_DAC_Init(&hdac);

    c.DAC_Trigger = DAC_TRIGGER_NONE;
    c.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
    HAL_DAC_ConfigChannel(&hdac, &c, DAC_CHANNEL_1);
    HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
}

int main(void)
{
    HAL_Init(); SystemClock_Config(); DAC1_Init();
    while (1) {
        for (uint32_t i=0;i<10;i++) {
            HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,(i*4095U)/9U);
            HAL_Delay(1);
        }
    }
}
