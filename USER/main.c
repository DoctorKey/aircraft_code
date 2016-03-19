

/******************** 尚学科技 **************************
 * 实验平台：开拓者STM32开发板
 * 库版本  ：ST3.5.0
 * 作者    ：尚学科技团队 
 * 淘宝    ：http://shop102218275.taobao.com/
 * 本程序只供学习使用，未经作者许可，不得用于其它任何用途
 *版权所有，盗版必究。
**********************************************************************************/


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
	delay(444000);
	send_data=USART_ReceiveData(USART1);
	USART_SendData(USART1,send_data);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}
}



void delay(unsigned int count)
{
int i;
for(i=0;i<count;i++);
}


