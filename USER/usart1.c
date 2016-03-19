#include "usart1.h"
#include "stm32f4xx_usart.h"
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
  	/*开启GPIOF的外设时钟*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
/*选择要控制的GPIOF引脚*/		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
  /*设置引脚模式为通用推挽输出*/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  /*设置引脚速率为100MHz */   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	/*调用库函数，初始化GPIOF*/
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
  /*设置引脚模式为通用推挽输出*/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	 USART_InitStructure.USART_BaudRate = 115200;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 
   USART_Init(USART1, &USART_InitStructure);
	 USART_Cmd(USART1,ENABLE);
}
