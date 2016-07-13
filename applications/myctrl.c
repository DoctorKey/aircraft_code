#include "myctrl.h"
#include "include.h"
#include "data_transfer.h"
#include "rc.h"
#include "ctrl.h"
#include "ultrasonic.h"
#define TAKE_OFF_HEIGHT 700
#define TAKE_OFF_UNLOCK 200
#define TAKE_OFF_PWM 500
void take_off()
{
	s16 motor_take_off[MAXMOTORS];
	motor_take_off[0] = TAKE_OFF_UNLOCK;  
	motor_take_off[1] = TAKE_OFF_UNLOCK;	 
	motor_take_off[2] = TAKE_OFF_UNLOCK;
	motor_take_off[3] = TAKE_OFF_UNLOCK;
	SetPwm(motor_take_off,0,1000);
	Delay_ms(2000);
	motor_take_off[0] = TAKE_OFF_PWM;  
	motor_take_off[1] = TAKE_OFF_PWM;	 
	motor_take_off[2] = TAKE_OFF_PWM;
	motor_take_off[3] = TAKE_OFF_PWM;
	SetPwm(motor_take_off,0,1000); 		
	Delay_ms(500);
	CH[2]=0;
	fly_ready=1;
	height_mode=0;//结束起飞模式
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

