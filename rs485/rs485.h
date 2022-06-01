#ifndef __RS485_H
#define __RS485_H

#include <stm8l15x.h>
#include <stm8l15x_usart.h>

#include <string.h>

#define DE_PORT GPIOC
#define DE_PIN GPIO_Pin_4



void init485(void);
void send485(char sen[100]);
char rece485(char rec[100]);
void Delay1(uint32_t nCount);

#endif