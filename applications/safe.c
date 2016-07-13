#include "safe.h"
#include "imu.h"
#include "rc.h"

void safe_motor(void)
{
	if(Roll>SAFE_ANGLE||Roll<-SAFE_ANGLE||Pitch>SAFE_ANGLE||Pitch<-SAFE_ANGLE)
	{
		CH[2]=-400;
		fly_ready=0;
	}	
}
