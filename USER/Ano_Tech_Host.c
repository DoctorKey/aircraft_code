#include "include.h"

#define BYTE0(dwTemp)       (*(char *)(&dwTemp))
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

float RC_Target_ROL = 0, RC_Target_PIT = 0 , RC_Target_YAW = 0;
uint8_t NRF24L01_RXDATA[RX_PLOAD_WIDTH] = {0};
uint8_t NRF24L01_TXDATA[RX_PLOAD_WIDTH] = {0};

uint8_t ARMED;

extern float MOTO_THRESHOLD;
extern float Roll_Target, Pitch_Target, Yaw_Target, Height_Target;
extern uint8_t Land_Flag;



void NRF_Send_AF(void)
{
	uint8_t i,sum = 0;
	uint16_t _temp;
	int16_t Acc_x, Acc_y, Acc_z, Gyro_x, Gyro_y, Gyro_z, Hx, Hy, Hz;
	Acc_x = (int16_t)(Get_DMP_Acc_x());
	Acc_y = (int16_t)(Get_DMP_Acc_y());
	Acc_z = (int16_t)(Get_DMP_Acc_z());
	Gyro_x = (int16_t)(Get_DMP_Gyro_x());
	Gyro_y = (int16_t)(Get_DMP_Gyro_y());
	Gyro_z = (int16_t)(Get_DMP_Gyro_z());
	Hx = (int16_t)(Get_HMC5883L_Hx());
	Hy = (int16_t)(Get_HMC5883L_Hy());
	Hz = (int16_t)(Get_HMC5883L_Hz());
	
	
	
	NRF24L01_TXDATA[0]=0x88;
	NRF24L01_TXDATA[1]=0xAF;
	NRF24L01_TXDATA[2]=0x1C;
	
	//NRF24L01_TXDATA[3]=BYTE1(Acc_x);
	//NRF24L01_TXDATA[4]=BYTE0(Acc_x);
	//NRF24L01_TXDATA[5]=BYTE1(Acc_y);
	//NRF24L01_TXDATA[6]=BYTE0(Acc_y);
	NRF24L01_TXDATA[7]=BYTE1(Acc_z);
	NRF24L01_TXDATA[8]=BYTE0(Acc_z);
	
	NRF24L01_TXDATA[9]=BYTE1(Gyro_x);
	NRF24L01_TXDATA[10]=BYTE0(Gyro_x);
	NRF24L01_TXDATA[11]=BYTE1(Gyro_y);
	NRF24L01_TXDATA[12]=BYTE0(Gyro_y);
	NRF24L01_TXDATA[13]=BYTE1(Gyro_z);
	NRF24L01_TXDATA[14]=BYTE0(Gyro_z);
	
	NRF24L01_TXDATA[15]=BYTE1(Hx);
	NRF24L01_TXDATA[16]=BYTE0(Hx);
	NRF24L01_TXDATA[17]=BYTE1(Hy);
	NRF24L01_TXDATA[18]=BYTE0(Hy);
	NRF24L01_TXDATA[19]=BYTE1(Hz);
	NRF24L01_TXDATA[20]=BYTE0(Hz);
	
	_temp = (int16_t)(Get_Roll()*100);
	NRF24L01_TXDATA[21]=BYTE1(_temp);
	NRF24L01_TXDATA[22]=BYTE0(_temp);
	
	_temp = (int16_t)(Get_Pitch()*100);
	NRF24L01_TXDATA[23]=BYTE1(_temp);
	NRF24L01_TXDATA[24]=BYTE0(_temp);
	
	_temp = (int16_t)(Get_Yaw()*10);
	NRF24L01_TXDATA[25]=BYTE1(_temp);
	NRF24L01_TXDATA[26]=BYTE0(_temp);
	
	_temp = (uint16_t)(Get_Height()*10);
	NRF24L01_TXDATA[3]=BYTE1(_temp);
	NRF24L01_TXDATA[4]=BYTE0(_temp);
	
	_temp = (uint16_t)(yaw_rate_PID.output);
	NRF24L01_TXDATA[5]=BYTE1(_temp);
	NRF24L01_TXDATA[6]=BYTE0(_temp);
	
	_temp = (uint16_t)(yaw_angle_PID.output);
	NRF24L01_TXDATA[7]=BYTE1(_temp);
	NRF24L01_TXDATA[8]=BYTE0(_temp);
	
	
	if(ARMED==0)			NRF24L01_TXDATA[27]=0xA0;
	else if(ARMED==1)		NRF24L01_TXDATA[27]=0xA1;
	
	for(i = 28;i < 32; i++) NRF24L01_TXDATA[i]=0;
	
	for(i=0;i<31;i++)
		sum += NRF24L01_TXDATA[i];
	
	NRF24L01_TXDATA[31]=sum;
	
	//R_UART0_Send(NRF24L01_TXDATA,32);
}

void NRF_Send_Gyro_Data(void)
{
	uint8_t i,sum = 0;
	uint16_t _temp;
	float Gyro_x, Gyro_y, Gyro_z;

	Gyro_x = Get_DMP_Gyro_x();
	Gyro_y = Get_DMP_Gyro_y();
	Gyro_z = Get_DMP_Gyro_z();
	
	NRF24L01_TXDATA[0]=0x88;
	NRF24L01_TXDATA[1]=0xA2;
	NRF24L01_TXDATA[2]=0x1C;
	
	NRF24L01_TXDATA[3]=BYTE3(Gyro_x);
	NRF24L01_TXDATA[4]=BYTE2(Gyro_x);	
	NRF24L01_TXDATA[5]=BYTE1(Gyro_x);
	NRF24L01_TXDATA[6]=BYTE0(Gyro_x);
	
	NRF24L01_TXDATA[7]=BYTE3(Gyro_y);
	NRF24L01_TXDATA[8]=BYTE2(Gyro_y);
	NRF24L01_TXDATA[9]=BYTE1(Gyro_y);
	NRF24L01_TXDATA[10]=BYTE0(Gyro_y);
	
	NRF24L01_TXDATA[11]=BYTE3(Gyro_z);
	NRF24L01_TXDATA[12]=BYTE2(Gyro_z);
	NRF24L01_TXDATA[13]=BYTE1(Gyro_z);	
	NRF24L01_TXDATA[14]=BYTE0(Gyro_z);
	
	
	if(ARMED==0)			NRF24L01_TXDATA[27]=0xA0;
	else if(ARMED==1)		NRF24L01_TXDATA[27]=0xA1;
	
	for(i=0;i<31;i++)
		sum += NRF24L01_TXDATA[i];
	
	NRF24L01_TXDATA[31]=sum;
}




void NRF_Send_ARMED(void)
{
	uint8_t i,sum = 0;
	
	NRF24L01_TXDATA[0]=0x88;
	NRF24L01_TXDATA[1]=0xAF;
	NRF24L01_TXDATA[2]=0x1C;

	if(ARMED)
	{
		NRF24L01_TXDATA[27]=0xA1;
	}
	else 	
	{
		NRF24L01_TXDATA[27]=0xA0;
	}
	for(i=0;i<31;i++)
		sum += NRF24L01_TXDATA[i];
	
	NRF24L01_TXDATA[31]=sum;
	
	//R_UART0_Send(NRF24L01_TXDATA,32);
}


void NRF_Send_PID(void)
{
	uint8_t i,sum = 0;
	uint16_t _temp;
	
	NRF24L01_TXDATA[0]=0x88;
	NRF24L01_TXDATA[1]=0xAC;
	NRF24L01_TXDATA[2]=0x1C;
	NRF24L01_TXDATA[3]=0xAD;
	
	//_temp = (uint16_t)(Get_PID_Roll_Rate_Kp() * 100);
	_temp = (uint16_t)(Get_PID_Roll_Angle_Kp() * 100);
	//_temp = (uint16_t)(Get_PID_alt_Kp() * 100);	
	NRF24L01_TXDATA[4]=BYTE1(_temp);
	NRF24L01_TXDATA[5]=BYTE0(_temp);
	//_temp = (uint16_t)(Get_PID_Roll_Rate_Ki() * 100);
	_temp = (uint16_t)(Get_PID_Roll_Angle_Ki() * 100);
	//_temp = (uint16_t)(Get_PID_alt_Ki() * 100);	
	NRF24L01_TXDATA[6]=BYTE1(_temp);
	NRF24L01_TXDATA[7]=BYTE0(_temp);
	//_temp = (uint16_t)(Get_PID_Roll_Rate_Kd() * 100);
	_temp = (uint16_t)(Get_PID_Roll_Angle_Kd() * 100);
	//_temp = (uint16_t)(Get_PID_alt_Kd() * 100);	
	NRF24L01_TXDATA[8]=BYTE1(_temp);
	NRF24L01_TXDATA[9]=BYTE0(_temp);
	
	//_temp = (uint16_t)(Get_PID_Pitch_Rate_Kp() * 100);
	_temp = (uint16_t)(Get_PID_Pitch_Angle_Kp() * 100);
	//_temp = (uint16_t)(Get_PID_Yaw_Angle_Kp() * 100);
	NRF24L01_TXDATA[10]=BYTE1(_temp);
	NRF24L01_TXDATA[11]=BYTE0(_temp);
	//_temp = (uint16_t)(Get_PID_Pitch_Rate_Ki() * 100);
	_temp = (uint16_t)(Get_PID_Pitch_Angle_Ki() * 100);
	//_temp = (uint16_t)(Get_PID_Yaw_Angle_Ki() * 100);
	NRF24L01_TXDATA[12]=BYTE1(_temp);
	NRF24L01_TXDATA[13]=BYTE0(_temp);
	//_temp = (uint16_t)(Get_PID_Pitch_Rate_Kd() * 100);
	_temp = (uint16_t)(Get_PID_Pitch_Angle_Kd() * 100);
	//_temp = (uint16_t)(Get_PID_Yaw_Angle_Kd() * 100);
	NRF24L01_TXDATA[14]=BYTE1(_temp);
	NRF24L01_TXDATA[15]=BYTE0(_temp);
	
	//_temp = (uint16_t)(Get_PID_Yaw_Rate_Kp() * 100);
	_temp = (uint16_t)(Get_PID_Yaw_Angle_Kp() * 100);
	NRF24L01_TXDATA[16]=BYTE1(_temp);
	NRF24L01_TXDATA[17]=BYTE0(_temp);
	//_temp = (uint16_t)(Get_PID_Yaw_Rate_Ki() * 100);
	_temp = (uint16_t)(Get_PID_Yaw_Angle_Ki() * 100);
	NRF24L01_TXDATA[18]=BYTE1(_temp);
	NRF24L01_TXDATA[19]=BYTE0(_temp);
	//_temp = (uint16_t)(Get_PID_Yaw_Rate_Kd() * 100);
	_temp = (uint16_t)(Get_PID_Yaw_Angle_Kd() * 100);
	NRF24L01_TXDATA[20]=BYTE1(_temp);
	NRF24L01_TXDATA[21]=BYTE0(_temp);
	
	sum = 0;
	for(i=0;i<31;i++)
		sum += NRF24L01_TXDATA[i];
	
	NRF24L01_TXDATA[31]=sum;
	
	//R_UART0_Send(NRF24L01_TXDATA,32);  
}


uint8_t NRF_DataAnl(void)
{
	uint8_t sum = 0, i = 0;
	float PID_ROL_P;
	float PID_ROL_I;
	float PID_ROL_D;
	
	float PID_PIT_P;
	float PID_PIT_I;
	float PID_PIT_D;
		
	float PID_YAW_P;
	float PID_YAW_I;
	float PID_YAW_D;
	
//	/* THRESHOLD */
//	if(NRF24L01_RXDATA[2]==0x81&&NRF24L01_RXDATA[3]==0x82&&NRF24L01_RXDATA[4]==0x83)
//	{
//		MOTO_THRESHOLD = (float)((int16_t)(NRF24L01_RXDATA[0]<<8)|NRF24L01_RXDATA[1]);
//		Pitch_Target = (float)((int16_t)(NRF24L01_RXDATA[5]<<8)|NRF24L01_RXDATA[6]);
//		Roll_Target = (float)((int16_t)(NRF24L01_RXDATA[7]<<8)|NRF24L01_RXDATA[8]);
//		Yaw_Target = (float)((int16_t)(NRF24L01_RXDATA[9]<<8)|NRF24L01_RXDATA[10]);
//		return 2;	
//	}
	

	if(NRF24L01_RXDATA[2]==0xE1 && NRF24L01_RXDATA[3]==0xE2 && NRF24L01_RXDATA[4]==0xE3 && NRF24L01_RXDATA[5]==0xE4)
	{
		Control_Test();
		return 2;	
	}
	
	if(NRF24L01_RXDATA[2]==0xE4 && NRF24L01_RXDATA[3]==0xE3 && NRF24L01_RXDATA[4]==0xE2 && NRF24L01_RXDATA[5]==0xE1)
	{
		//Control_Land();
		Land_Flag == 1;
		return 2;	
	}
	
	if(NRF24L01_RXDATA[2]==0xF1 && NRF24L01_RXDATA[3]==0xF2 && NRF24L01_RXDATA[4]==0xF3 && NRF24L01_RXDATA[5]==0xF4)
	{
		if(ARMED)
		{
			Control_Fly_Flag_On();
			Control_Fly();
		}else
			{
				Control_Fly_Flag_Off();
				Control_Free_Land();
			}		
		return 2;
	}
	
	if(NRF24L01_RXDATA[2]==0xF4 && NRF24L01_RXDATA[3]==0xF3 && NRF24L01_RXDATA[4]==0xF2 && NRF24L01_RXDATA[5]==0xF1)
	{
		Control_Fly_Flag_Off();
		Control_Free_Land();		
		return 2;
	}
	
		
/********************************/
	if(!(NRF24L01_RXDATA[0]==0x8A))
	{
		return 0;	
	}
	for(i=0;i<31;i++)
	{
		sum += NRF24L01_RXDATA[i];
	}
	if(!(sum==NRF24L01_RXDATA[31]))	
	{
		return 0;		
	}
	
	if(NRF24L01_RXDATA[1]==0x8A)		
	{
//		//Rc_Get.THROTTLE = (vs16)(NRF24L01_RXDATA[3]<<8)|NRF24L01_RXDATA[4];
//		Pitch_Target			= (vs16)(NRF24L01_RXDATA[5]<<8)|NRF24L01_RXDATA[6];
//		Rc_Get.ROLL			= (vs16)(NRF24L01_RXDATA[7]<<8)|NRF24L01_RXDATA[8];
//		Rc_Get.PITCH			= (vs16)(NRF24L01_RXDATA[9]<<8)|NRF24L01_RXDATA[10];
//		Rc_Get.AUX1			= (vs16)(NRF24L01_RXDATA[11]<<8)|NRF24L01_RXDATA[12];
//		Rc_Get.AUX2			= (vs16)(NRF24L01_RXDATA[13]<<8)|NRF24L01_RXDATA[14];
//		Rc_Get.AUX3			= (vs16)(NRF24L01_RXDATA[15]<<8)|NRF24L01_RXDATA[16];
//		Rc_Get.AUX4			= (vs16)(NRF24L01_RXDATA[17]<<8)|NRF24L01_RXDATA[18];
//		Rc_Get.AUX5			= (vs16)(NRF24L01_RXDATA[19]<<8)|NRF24L01_RXDATA[20];
//		RC_FUN();
//		RC_Target_ROL = (Rc_Get.ROLL-1500)/30;
//		RC_Target_PIT = (Rc_Get.PITCH-1500)/30;
//		RC_Target_YAW = (Rc_Get.YAW-1500)/30;
		
	}


	
	if(NRF24L01_RXDATA[1]==0X8B)		
	{
		
		if(NRF24L01_RXDATA[3]==0xA0)	
		{
			ARMED = 0;
			NRF_Send_ARMED();
			return 1;
		}
		if(NRF24L01_RXDATA[3]==0xA1)	
		{
			ARMED = 1;
			NRF_Send_ARMED();
			return 1;
		}
		
		if(NRF24L01_RXDATA[3]==0xAD)
		{
			NRF_Send_PID();
			return 1;
		}
		if(NRF24L01_RXDATA[3]==0xAE)
		{
			PID_ROL_P = ((float)((uint16_t)(NRF24L01_RXDATA[4]<<8)|NRF24L01_RXDATA[5])) / 100;
			PID_ROL_I = ((float)((uint16_t)(NRF24L01_RXDATA[6]<<8)|NRF24L01_RXDATA[7])) / 100;
			PID_ROL_D = ((float)((uint16_t)(NRF24L01_RXDATA[8]<<8)|NRF24L01_RXDATA[9])) / 100;
			
			PID_PIT_P = ((float)((uint16_t)(NRF24L01_RXDATA[10]<<8)|NRF24L01_RXDATA[11])) / 100;
			PID_PIT_I = ((float)((uint16_t)(NRF24L01_RXDATA[12]<<8)|NRF24L01_RXDATA[13])) / 100;
			PID_PIT_D = ((float)((uint16_t)(NRF24L01_RXDATA[14]<<8)|NRF24L01_RXDATA[15])) / 100;
			
			PID_YAW_P = ((float)((uint16_t)(NRF24L01_RXDATA[16]<<8)|NRF24L01_RXDATA[17])) / 100;
			PID_YAW_I = ((float)((uint16_t)(NRF24L01_RXDATA[18]<<8)|NRF24L01_RXDATA[19])) / 100;
			PID_YAW_D = ((float)((uint16_t)(NRF24L01_RXDATA[20]<<8)|NRF24L01_RXDATA[21])) / 100;
			
//			PID_Parameter_Load_Rate(PID_ROL_P, PID_ROL_I, PID_ROL_D,
//						PID_PIT_P, PID_PIT_I, PID_PIT_D,
//						PID_YAW_P, PID_YAW_I, PID_YAW_D);

			
			PID_Parameter_Load_Angle(PID_ROL_P, PID_ROL_I, PID_ROL_D,
						PID_PIT_P, PID_PIT_I, PID_PIT_D,
						PID_YAW_P, PID_YAW_I, PID_YAW_D);

//			PID_Parameter_Load_Height(PID_ROL_P, PID_ROL_I, PID_ROL_D,
//						PID_PIT_P, PID_PIT_I, PID_PIT_D,
//						PID_YAW_P, PID_YAW_I, PID_YAW_D);
						
			PID_Parameter_Reset_Angle();
			PID_Parameter_Reset_Rate();
			
			return 2;
		}
	}
	
	return 0;
}