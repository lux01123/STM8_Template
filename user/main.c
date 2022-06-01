/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stdio.h"

#include "lcd.h"
#include "rs485.h"
//#include "tim1.h"
/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//Dinh nghia cho chan ra LED
#define LED_PORT        GPIOC
#define LED_PIN1        GPIO_Pin_5
#define LED_PORT        GPIOC
#define LED_PIN2        GPIO_Pin_6


// RS 485
//#include "stm8l15x.h"
#include "stm8l15x_tim1.h"

#define TIM1_PERIOD             65535
#define TIM1_PRESCALER              1
#define TIM1_REPTETION_COUNTER      0

__IO uint16_t CCR1_Val = 32768;
__IO uint16_t CCR2_Val = 16384;
__IO uint16_t CCR3_Val = 8192;

static void CLK_Config(void)                                                    // Thiet lap tan so su dung bo dao dong noi HSI voi tan so mac dinh 16Mhz
{
  /* Select HSE as system clock source */
  CLK_SYSCLKSourceSwitchCmd(ENABLE);
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
  /* system clock prescaler: 1*/                                                // Dat he so chia truoc la 1 de tan so CPU bang tan so bo dao dong noi         
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
  while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI)
  {}
}

void tim1init(void)
{
  /* Enable TIM1 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE);
  /* GPIOD configuration: TIM1 channel 1 (PD2), channel 2 (PD4) and channel 3 (PD5) */
  GPIO_Init(GPIOD, GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Fast);
}

void TIM1_Config(void)
{
  /*
  - TIM1CLK = 2 MHz
  - TIM1 counter clock = TIM1CLK / TIM1_PRESCALER+1 = 2 MHz/1+1 = 1 MHz
  */
  /* Time base configuration */
  TIM1_TimeBaseInit(TIM1_PRESCALER, TIM1_CounterMode_Up, TIM1_PERIOD, TIM1_REPTETION_COUNTER);

  /*
  - The TIM1 CCR1 register value is equal to 32768: 
  - CC1 update rate = TIM1 counter clock / CCR1_Val = 30.51 Hz,
  - So the TIM1 Channel 1 generates a periodic signal with a frequency equal to 15.25 Hz.
  */
  /* Toggle Mode configuration: Channel1 */
  TIM1_OC1Init(TIM1_OCMode_Toggle, TIM1_OutputState_Enable, TIM1_OutputNState_Disable,
               CCR1_Val, TIM1_OCPolarity_Low, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set,
               TIM1_OCNIdleState_Set);
  TIM1_OC1PreloadConfig(DISABLE);

  /*
  - The TIM1 CCR2 register is equal to 16384:
  - CC2 update rate = TIM1 counter clock / CCR2_Val = 61.03 Hz
  - So the TIM1 channel 2 generates a periodic signal with a frequency equal to 30.51 Hz.
  */
  /* Toggle Mode configuration: Channel2 */
  TIM1_OC2Init(TIM1_OCMode_Toggle, TIM1_OutputState_Enable, TIM1_OutputNState_Disable,
               CCR2_Val, TIM1_OCPolarity_Low, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set,
               TIM1_OCNIdleState_Set);
  TIM1_OC2PreloadConfig(DISABLE);

  /*
  -The TIM1 CCR3 register is equal to 8192:
  - CC3 update rate = TIM1 counter clock / CCR3_Val = 123.01 Hz
  - So the TIM1 channel 3 generates a periodic signal with a frequency equal to 61.5 Hz.
  */
  /* Toggle Mode configuration: Channel3 */
  TIM1_OC3Init(TIM1_OCMode_Toggle, TIM1_OutputState_Enable, TIM1_OutputNState_Disable,
               CCR3_Val, TIM1_OCPolarity_Low, TIM1_OCNPolarity_Low, TIM1_OCIdleState_Set,
               TIM1_OCNIdleState_Set);
  TIM1_OC3PreloadConfig(DISABLE);

  TIM1_ARRPreloadConfig(ENABLE);

  /* TIM1 Interrupt enable */
  TIM1_ITConfig(TIM1_IT_CC1, ENABLE);
  TIM1_ITConfig(TIM1_IT_CC2, ENABLE);
  TIM1_ITConfig(TIM1_IT_CC3, ENABLE);
  enableInterrupts();

  /* Enable TIM1 outputs */
  TIM1_CtrlPWMOutputs(ENABLE);
  /* TIM1 enable counter */
  TIM1_Cmd(ENABLE);
}

/*******************************/

/* Private functions ---------------------------------------------------------*/
// RS485

/**7
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  CLK_Config();
 // GPIO_DeInit(LED_PORT1);
  
  GPIO_Init(LED_PORT, LED_PIN1, GPIO_Mode_Out_PP_High_Fast);                   // Khai bao chan LED
  GPIO_Init(LED_PORT, LED_PIN2, GPIO_Mode_Out_PP_High_Fast);
  /**** CODE LCD *****/
  gpiolcd();
  lcd_init();
  lcd_clear();
  
  lcd_puts(0,0, "U Phan ung =      V");
  lcd_puts(1,0, "I Kich tu  =      A");
  lcd_puts(2,0, "I Phan ung =      A");
  lcd_puts(3,0, "  Nhiet do =     'C");
  /******************/
  
  /***** CODE RS485 *****/
  init485();
  /**********************/
  
  GPIO_Init(GPIOD, GPIO_Pin_3 , GPIO_Mode_Out_PP_High_Fast);
  
  /***** PWM***********/
  tim1init();
  TIM1_Config();
  
  /* Infinite loop */
  while (1)
  {
  /*** RS485 ****/
    
  //send485("Hello");
  Delay(500000);
  //send485("123");
  //Delay(500000);
  //send485("#!@");
  //Delay(500000);
  /*** PWM ****/
  GPIO_WriteBit(DE_PORT, DE_PIN , RESET);
  Delay(10000);
  GPIO_WriteBit(DE_PORT, DE_PIN , SET);
  Delay(10000);
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
