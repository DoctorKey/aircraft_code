#include "usart1.h"
#include "stm32f4xx_usart.h"
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
  	/*����GPIOF������ʱ��*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
/*ѡ��Ҫ���Ƶ�GPIOF����*/		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10 ;
  /*��������ģʽΪͨ���������*/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  /*������������Ϊ100MHz */   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	/*���ÿ⺯������ʼ��GPIOF*/
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	 USART_DeInit(USART1);
	 USART_InitStructure.USART_BaudRate = 115200;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 
   USART_Init(USART1, &USART_InitStructure);
	 USART_Cmd(USART1,ENABLE);
}
