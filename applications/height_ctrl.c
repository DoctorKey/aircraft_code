#include "height_ctrl.h"
#include "ultrasonic.h"
#include "mymath.h"
#include "filter.h"
#include "ctrl.h"
#include "rc.h"

float ultra_ctrl_out;
float height_ctrl_out;

void Height_Ctrl(float T,float thr)
{
	if(ultra_ok==1)
	{
		Ultra_Ctrl(T,thr);
		ultra_ok=0;
	}
	if(height_ctrl_mode)
	{	
		height_ctrl_out = ultra_ctrl_out;//我的程序
	}
	else
	{
		height_ctrl_out = thr;
	}
}

#define ULTRA_MAX_HEIGHT 1000   // mm
#define INTEG_MAX 3000 //积分限幅

_st_height_pid ultra_pid;

void Ultra_PID_Init()
{
	ultra_pid.kp = 1.0f*pid_setup.groups.hc_height.kp;
	ultra_pid.kd = 1.0f*pid_setup.groups.hc_height.kd;
	ultra_pid.ki = 1.0f*pid_setup.groups.hc_height.ki;
}

float exp_height = 700;

//////////////////我的定高程序////////////////////
void Ultra_Ctrl(float T,float thr)
{
	/*
		CH_filter   -500  ------  500
		exp_height    0   ------  ULTRA_MAX_HEIGHT
	*/

	if( exp_height > ULTRA_MAX_HEIGHT ){
		exp_height = ULTRA_MAX_HEIGHT;
	}
	
	PID_Position(&ultra_pid,exp_height,ultra_distance);

	ultra_ctrl_out = thr+ultra_pid.output;
}
void PID_Position(_st_height_pid *ultra_pid,float target,float measure)
{
		
	ultra_pid->error = target - measure;
	ultra_pid->integ += ultra_pid->error;
	
	LIMIT(ultra_pid->integ,-INTEG_MAX,INTEG_MAX);

	ultra_pid->output = ultra_pid->kp * ultra_pid->error + ultra_pid->ki * ultra_pid->integ + ultra_pid->kd * (ultra_pid->error - ultra_pid->preerror);

	ultra_pid->preerror = ultra_pid->error;
//	ultra_pid->prepreerror = ultra_pid->preerror;
	
}
void PID_Incremental(_st_height_pid *ultra_pid,float target,float measure)
{
	ultra_pid->error = target - measure;

	ultra_pid->output = ultra_pid->kp * (ultra_pid->error - ultra_pid->preerror) + ultra_pid->ki * ultra_pid->error + ultra_pid->kd * (ultra_pid->error - 2 * ultra_pid->preerror + ultra_pid->prepreerror);

	ultra_pid->preerror = ultra_pid->error;
	ultra_pid->prepreerror = ultra_pid->preerror;
}


