#include "myctrl.h"
#include "rc.h"
#include "ultrasonic.h"
#include "height_ctrl.h"
#include "pwm_in.h"
#include "include.h"


u8 my_mode=0;
u8 take_off_ok=0;
u8 land_ok = 0;

void take_off()
{	
	#ifndef USE_CAMERA
	CH[2]=135;
	#endif
	
	#ifdef USE_CAMERA
	Rc_Pwm_In[2] = FLY_THR;
	#endif
	
	exp_height=700;
	land_ok = 0;//允许降落
	fly_ready=1;
	take_off_ok = 1;
	height_mode=0;
//	mpu6050.Gyro_CALIBRATE = 2;
}
void land()
{
	#ifndef USE_CAMERA
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
			take_off_ok = 0;//允许起飞
			fly_ready=0;
			land_ok = 1;
			height_mode=0;//结束降落模式
	}	
	#endif
	
	#ifdef USE_CAMERA
	if(ultra_distance>600)
	{
		if(Rc_Pwm_In[2] > 1300)
		{
			Rc_Pwm_In[2]=Rc_Pwm_In[2]-10;
		}
	}
	else if(ultra_distance>400)//400~600
	{
		if(Rc_Pwm_In[2] > 1300)
		{
			Rc_Pwm_In[2]=Rc_Pwm_In[2]-1;
		}
	}
	else
	{
			Rc_Pwm_In[2] = 1100;
			take_off_ok = 0;//允许起飞
			fly_ready = 0;
			land_ok = 1;
			height_mode = 0;//结束降落模式
	}	
	#endif
}

void my_duty()
{
	if(camera_mode > 1000 && camera_mode < 1150)//wait_ready();
	{
		my_mode = 0;
//		Rc_Pwm_In[2] = 1000;
	}else if(camera_mode > 1150 && camera_mode < 1250)//take_off
	{
		my_mode = 1;
		if(take_off_ok == 0)
		{
			height_mode=1;//起飞
			Rc_Pwm_In[2] = FLY_THR;
		}
	}else if(camera_mode > 1250 && camera_mode < 1350)//go();
	{
		my_mode = 2;
		Rc_Pwm_In[2] = FLY_THR;
//		exp_height = 500;
	}else if(camera_mode > 1350 && camera_mode < 1450)//throw_ball();
	{
		my_mode = 3;
		Rc_Pwm_In[2] = FLY_THR;
//		exp_height = 400;		
	}else if(camera_mode > 1550 && camera_mode < 1650)//back();
	{
		my_mode = 4;
		Rc_Pwm_In[2] = FLY_THR;
		exp_height = 700;
	}else if(camera_mode > 1650 && camera_mode < 1750)
	{
		my_mode = 5;
		if(land_ok == 0)
		{
			height_mode=2;//降落模式
		}
	}
}
