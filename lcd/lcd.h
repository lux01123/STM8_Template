#ifndef __LCD_H
#define __LCD_H

#include "stm8l15x.h"

#define LCD20xN

#define RS_PORT GPIOE
#define RS_PIN  GPIO_Pin_0

#define EN_PORT GPIOE
#define EN_PIN	GPIO_Pin_1

#define D7_PORT GPIOE
#define D7_PIN GPIO_Pin_5

#define D6_PORT GPIOE
#define D6_PIN GPIO_Pin_4

#define D5_PORT GPIOE
#define D5_PIN GPIO_Pin_3

#define D4_PORT GPIOE
#define D4_PIN GPIO_Pin_2

#define PIN_LOW(PORT,PIN)  GPIO_WriteBit(PORT, PIN, RESET);
#define PIN_HIGH(PORT,PIN) GPIO_WriteBit(PORT, PIN, SET);

void lcd_init(void);
void lcd_write(uint8_t type, uint8_t data);
void lcd_puts(uint8_t x, uint8_t y, int8_t *string);
void lcd_clear(void);
void Delay(uint32_t nCount);
void gpiolcd(void);

#endif 