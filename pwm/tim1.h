#ifndef __TIM1_H
#define __TIM1_H

#include "stm8l15x.h"
#include "stm8l15x_tim1.h"

#define TIM1_PERIOD             65535
#define TIM1_PRESCALER              1
#define TIM1_REPTETION_COUNTER      0

__IO uint16_t CCR1_Val = 32768;
__IO uint16_t CCR2_Val = 16384;
__IO uint16_t CCR3_Val = 8192;

static void tim1init(void);
static void TIM1_Config(void);

#endif