#include "myctrl.h"
#include "rc.h"
#include "ultrasonic.h"
#include "height_ctrl.h"
#include "pwm_in.h"

#define FLY_THR 1600;

void take_off()
{	
	CH[2]=100;
	
	#ifdef USE_CAMERA
	Rc_Pwm_In[2] = FLY_THR;
	#endif
	
	exp_height=700;
	fly_ready=1;
	height_mode=0;
//	mpu6050.Gyro_CALIBRATE = 2;
}
void land()
{
	#ifdef USE_CAMERA
	Rc_Pwm_In[2] = CH[2] + 1500;
	#endif
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
u8 take_off_ok=0;
u8 land_ok = 0;
void my_duty()
{
	if(my_mode > 1000 && my_mode < 1150)//wait_ready();
	{
		Rc_Pwm_In[2] = 1000;
	}else if(my_mode > 1150 && my_mode < 1250)
	{
		if(take_off_ok == 0)
		{
			take_off();
			take_off_ok = 1;
		}
	}else if(my_mode > 1250 && my_mode < 1350)//go();
	{
		Rc_Pwm_In[2] = FLY_THR;
//		exp_height = 500;
	}else if(my_mode > 1350 && my_mode < 1450)//throw_ball();
	{
		Rc_Pwm_In[2] = FLY_THR;
		exp_height = 400;		
	}else if(my_mode > 1450 && my_mode < 1550)//back();
	{
		Rc_Pwm_In[2] = FLY_THR;
		exp_height = 700;
	}else if(my_mode > 1550 && my_mode < 1650)
	{
		if(land_ok == 0)
		{
			land();
			land_ok = 1;
		}
	}
}
