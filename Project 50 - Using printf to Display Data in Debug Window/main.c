/*
 * Using printf to Display Data in Debug Window
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

static int itm_putchar(int ch)
{
    if((ITM->TCR&ITM_TCR_ITMENA_Msk)&&(ITM->TER&1UL)){
        while(ITM->PORT[0].u32==0UL){}
        ITM->PORT[0].u8=(uint8_t)ch;
    }
    return ch;
}

int _write(int file,char *p,int len){(void)file;for(int i=0;i<len;i++)itm_putchar(p[i]);return len;}
int main(void){HAL_Init();SystemClock_Config();uint32_t n=0;while(1){printf("n=%lu\r\n",(unsigned long)n++);HAL_Delay(1000);}}
