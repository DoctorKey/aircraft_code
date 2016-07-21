#ifndef __HEIGHT_CTRL_H
#define __HEIGHT_CTRL_H

#include "stm32f4xx.h"

typedef struct
{
	float kp;
	float kd;
	float ki;
	float integ;
	float error;
	float preerror;
	float prepreerror;
	float output;

}_st_height_pid;

void Height_Ctrl(float T,float thr);

void Ultra_PID_Init(void);

void Ultra_Ctrl(float T,float thr);

void PID_Position(_st_height_pid *ultra_pid,float target,float measure);

void PID_Incremental(_st_height_pid *ultra_pid,float target,float measure);
	
extern float ultra_ctrl_out;

extern float height_ctrl_out;

extern float exp_height;

#endif

