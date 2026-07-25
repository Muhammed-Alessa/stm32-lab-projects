/*
 * LED Dice
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

static const uint16_t dp[7] = {
    GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
    GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6
};
static const uint8_t map[7] = {0x00,0x08,0x22,0x2A,0x55,0x5D,0x77};

static void Dice_Init(void)
{
    GPIO_InitTypeDef g = {0};
    __HAL_RCC_GPIOC_CLK_ENABLE();
    g.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|
            GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
    g.Mode = GPIO_MODE_OUTPUT_PP; g.Pull = GPIO_NOPULL;
    g.Speed = GPIO_SPEED_FREQ_LOW; HAL_GPIO_Init(GPIOC, &g);

    g.Pin = GPIO_PIN_13; g.Mode = GPIO_MODE_INPUT; HAL_GPIO_Init(GPIOC, &g);
}
static void Dice_Show(uint8_t n)
{
    for (uint32_t i=0;i<7;i++)
        HAL_GPIO_WritePin(GPIOC, dp[i], (map[n]&(1U<<i))?GPIO_PIN_SET:GPIO_PIN_RESET);
}
int main(void)
{
    HAL_Init(); SystemClock_Config(); Dice_Init();
    uint32_t state = 0x12345678U;
    while (1) {
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
            state = state * 1664525U + 1013904223U + HAL_GetTick();
            Dice_Show((uint8_t)(1U + state % 6U));
            HAL_Delay(3000); Dice_Show(0);
        }
    }
}
