/******************** (C) COPYRIGHT 2014 ANO Tech ********************************
  * 作者   ：匿名科创
 * 文件名  ：led.c
 * 描述    ：LED驱动
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
**********************************************************************************/

#include "led.h"
#include "include.h"

void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOG,ENABLE);	//使能GPIOC的外设时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	//选择要用的GPIO引脚		 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//设置引脚为普通输出模式		
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//设置引脚为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//设置引脚速度为100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//设置引脚为上拉 		 
	GPIO_Init(GPIOB, &GPIO_InitStructure);//调用库函数，初始化GPIO	
}

#include "rc.h"
#include "ak8975.h"

u8 flag=1;
void LED_Duty()
{
	if(flag==0){
		LED0_ON;
		flag=1;
	}else{
		LED0_OFF;
		flag=0;
	}
}

void LED_MPU_Err(void)
{	
	while(1)
	{
		LED0_ON;
	}
}

void LED_Mag_Err(void)
{
	while(1)
	{
		LED0_ON;
	}
}

/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

