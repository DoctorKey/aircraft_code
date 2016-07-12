#include "myctrl.h"
#include "include.h"
#include "data_transfer.h"
#include "rc.h"
#include "ctrl.h"
#include "ultrasonic.h"
#define TAKE_OFF_HEIGHT 700
void take_off()
{
	if(ultra_distance>200)
	{
		CH[2]=-400;	
		fly_ready=1;
	}
		
//	delay_ms(2000);
	if(ultra_distance>TAKE_OFF_HEIGHT)
	{
		height_mode=0;//结束起飞模式
	}
}
void land()
{
	if(ultra_distance>600)
	{
		if(CH[2]>-200)
		{
			CH[2]=CH[2]-10;
		}
	}
	else if(ultra_distance>400)//400~600
	{
		if(CH[2]>-200)
		{
			CH[2]=CH[2]-1;
		}
	}
	else
	{
			CH[2]=-400;
			fly_ready=0;
			height_mode=0;//结束降落模式
	}	
}

