/*
 * Random Flashing LEDs
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

static const uint16_t led_pins[8] = {
    GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3,
    GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7
};

static void LED_Bus_Init(void)
{
    GPIO_InitTypeDef g = {0};
    __HAL_RCC_GPIOC_CLK_ENABLE();
    g.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
            GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    g.Mode = GPIO_MODE_OUTPUT_PP;
    g.Pull = GPIO_NOPULL;
    g.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &g);
}

static void LED_Bus_Write(uint8_t value)
{
    for (uint32_t i = 0; i < 8; ++i) {
        HAL_GPIO_WritePin(GPIOC, led_pins[i],
            (value & (1U << i)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

int main(void)
{
    HAL_Init(); SystemClock_Config(); LED_Bus_Init();
    uint16_t lfsr = 0xACE1U;
    while (1) {
        uint16_t bit = (uint16_t)(((lfsr >> 0) ^ (lfsr >> 2) ^
                         (lfsr >> 3) ^ (lfsr >> 5)) & 1U);
        lfsr = (uint16_t)((lfsr >> 1) | (bit << 15));
        LED_Bus_Write((uint8_t)lfsr);
        HAL_Delay(250);
    }
}
