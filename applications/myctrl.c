#include "myctrl.h"
#include "include.h"
#include "data_transfer.h"
#include "rc.h"
#include "ctrl.h"
void take_off()
{
	int thr;
//	for(thr=-400;thr<=-100;thr+=10){
//		CH_filter[THR]=thr;
//		Delay_ms(10);
//	}
//	Feed_Rc_Dog(1);
	for(thr=1100;thr<=1400;thr+=1){
		Feed_Rc_Dog(1);
		Rc_Pwm_In[2]=thr;
		Delay_ms(10);
	}
}
void drop()
{
	
}

