

/******************** ��ѧ�Ƽ� **************************
 * ʵ��ƽ̨��������STM32������
 * ��汾  ��ST3.5.0
 * ����    ����ѧ�Ƽ��Ŷ� 
 * �Ա�    ��http://shop102218275.taobao.com/
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
 *��Ȩ���У�����ؾ���
**********************************************************************************/


#include "stm32f4xx.h"
#include "LED.H"


  
void delay(unsigned int count);




int main(void)
{
	u8 send_data='1';
	LED_GPIO_Config();
	USART1_Config();
	printf("hello");

while(1)
{
	delay(1000);
	USART_SendData(USART1,send_data);
}
}



void delay(unsigned int count)
{
int i;
for(i=0;i<count;i++);
}


