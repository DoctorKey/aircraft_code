


#include "stm32f4xx.h"
#include "LED.H"
#include "usart1.h"

void delay(unsigned int count);

int main(void)
{
	u8 send_data='1';
	LED_GPIO_Config();
	USART1_Config();

while(1)
{
//	delay(444000);
//	send_data=USART_ReceiveData(USART1);
//	USART_SendData(USART1,send_data);
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}
}



void delay(unsigned int count)
{
int i;
for(i=0;i<count;i++);
}


