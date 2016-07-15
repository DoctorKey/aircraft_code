#include "myctrl.h"
#include "include.h"
#include "data_transfer.h"
#include "rc.h"
#include "ctrl.h"
#include "ultrasonic.h"
u8 cnt=0;

void take_off()
{	
	CH[2]=40;
//	CH[0]=0;
//	CH[1]=0;
//	CH[3]=0;
//	exp_height=700;
	fly_ready=1;
	height_mode=0;
	mpu6050.Gyro_CALIBRATE = 2;
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
			height_mode=0;//½áÊø½µÂäÄ£Ê½
	}	
}

