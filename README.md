# NUCLEO-F446RE STM32F446RET6 Projects


Each project contains:

- `README.md`
- `main.c`
- `images/` 


## F446RE pin conventions used here

- On-board LD2 LED: `PA5`
- User button B1: `PC13`
- USART2 / ST-LINK Virtual COM: `PA2` TX, `PA3` RX
- I2C1: `PB8` SCL, `PB9` SDA
- SPI1: `PA5` SCK, `PA6` MISO, `PA7` MOSI; software CS uses `PB6`
- ADC examples: `PA0/A0` and `PA1/A1`
- DAC examples: `PA4`
- PWM examples: `PB3 / TIM2_CH2`

## Projects

- `Project 01 - Lighthouse flashing LED`
- `Project 02 - Alternately Flashing LEDs`
- `Project 03 - Moving LEDs`
- `Project 04 - Binary Up Counter with LEDs`
- `Project 05 - Random Flashing LEDs`
- `Project 06 - Pushbutton and LED`
- `Project 07 - Control of Multiple LEDs by 2 Buttons`
- `Project 08 - LED Dice`
- `Project 09 - 7-Segment LED Counter`
- `Project 10 - Two-Digit Multiplexed 7-Segment LED`
- `Project 11 - External interrupt to control an LED`
- `Project 12 - Two-digit Interrupt-Driven 7-Segment Event Counter`
- `Project 13 - Four-Digit 7-Segment LED Display`
- `Project 14 - Interrupt-Based Up-Down Counter with Four-Digit 7-Segment LED Display`
- `Project 15 - Multiple External Interrupts Sharing the Same Interrupt Line`
- `Project 16 - Timer Interrupt to Flash LED Every Second`
- `Project 17 - 4-Digit 7-Segment LED Up Counter with Timer Interrupts`
- `Project 18 - Using parallel LCDs - Displaying Text`
- `Project 19 - Using LCDs - Simple Up Counter`
- `Project 20 - Analogue Voltmeter - Polling ADC`
- `Project 21 - ADC with Multiple Inputs - Polling ADC`
- `Project 22 - Single-input ADC with Conversion Interrupt`
- `Project 23 - Analogue Temperature Sensor`
- `Project 24 - ON-OFF Temperature Controller`
- `Project 25 - Multiple-input ADC with DMA`
- `Project 26 - Sawtooth Waveform Generator with Manual DAC Driving`
- `Project 27 - Squarewave Generator with Manual DAC Driving`
- `Project 28 - Sinewave Generator with Manual DAC Driving`
- `Project 29 - Arbitrary Waveform Generator with Manual DAC Driving`
- `Project 30 - Arbitrary Waveform Generator with Timer-based DMA`
- `Project 31 - Hardware-based Triangular Waveform Generation`
- `Project 32 - Mosquito Repeller`
- `Project 33 - Continuously Variable Duty Cycle`
- `Project 34 - Multiple PWM Waveforms`
- `Project 35 - Potentiometer-controlled Duty Cycle Control of PWM Waveform`
- `Project 36 - Displaying Text on the PC`
- `Project 37 - Simple Up Counter`
- `Project 38 - Times Table`
- `Project 39 - Practising Elementary Multiplication`
- `Project 40 - Displaying Ambient Temperature on the PC Screen`
- `Project 41 - Communicating with Arduino - Displaying Temperature`
- `Project 42 - Communicating with Arduino - UART Interrupt Mode`
- `Project 43 - I2C Port Expander`
- `Project 44 - EEPROM memory`
- `Project 45 - TMP102 Temperature Sensor Chip Reading`
- `Project 46 - SPI Port Expander`
- `Project 47 - Simple Debug`
- `Project 48 - Debugging the GPIO`
- `Project 49 - Displaying Characters in Debug Window`
- `Project 50 - Using printf to Display Data in Debug Window`
- `Project 51 - Using the ST-Link Virtual COM Port`
- `Project 52 - Sleep Mode Example`
- `Project 53 - Stop Mode Example`
- `Project 54 - Standby Mode Example`
- `Project 55 - X-NUCLEO-OUT01A1 - Flashing an LED`
- `Project 56 - Reading Temperature from the X-NUCLEO-IKS01A2 Expansion Board`
- `Project 57 - Using the X-CUBE-MEMS1 Library`
- `Project 58 - FreeRTOS - Three LED Tasks`

## Notes

The small GPIO, ADC, DAC, PWM, UART, I2C, SPI, interrupt, and low-power examples include F446RE-oriented HAL application code.

Some advanced projects—especially DMA variants and X-NUCLEO/X-CUBE middleware—are intentionally CubeMX-assisted because DMA/BSP initialization depends on the STM32CubeF4 and expansion-pack version installed on your PC.

Treat each project as a clean portfolio starting point: build it on the real board, verify it, then add your own breadboard photo.
