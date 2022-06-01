#include <rs485.h>

void Delay1(uint32_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}


void init485(void)
{
        GPIO_Init(DE_PORT, DE_PIN, GPIO_Mode_Out_PP_High_Fast);
        
        GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_3, ENABLE);
 
        GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_2, ENABLE);
 

	USART_DeInit(USART1);
	
	CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);

	USART_Init(USART1, 115200, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, USART_Mode_Tx | USART_Mode_Rx);
 
	USART_ClockInit(USART1, USART_Clock_Disable, USART_CPOL_Low, USART_CPHA_1Edge, USART_LastBit_Disable);
 
	USART_Cmd(USART1, ENABLE);
}

void send485(char sen[100])
{
        GPIO_WriteBit(DE_PORT, DE_PIN, SET);
        uint8_t Data;
        uint8_t j = 0;
        for(j = 0; j < strlen(sen); j++)
        {
          Data = sen[j];
          USART_SendData8(USART1, Data);
          Delay1(100);
        }
}

char rece485(char rec[100])
{
        GPIO_WriteBit(DE_PORT, DE_PIN, RESET);
        uint8_t Data;
        uint8_t j = 0;
        for(j = 0; j < 100; j++)
        {
	Data = USART_ReceiveData8(USART1);
        rec[j] = Data;
        }
        return rec[100];
}