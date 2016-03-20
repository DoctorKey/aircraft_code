#include "r_cg_macrodriver.h"

#ifndef _ANO_TECH_HOST_
#define _ANO_TECH_HOST_

#define RX_PLOAD_WIDTH  32  	
#define TX_PLOAD_WIDTH  32 


//extern uint8_t ARMED;
extern float RC_Target_ROL , RC_Target_PIT , RC_Target_YAW;

void NRF_Send_AF(void);
void NRF_Send_Gyro_Data(void);

void NRF_Send_PID(void);
void NRF_Send_ARMED(void);
uint8_t NRF_DataAnl(void);


#endif