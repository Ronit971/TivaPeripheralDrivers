#include "TM4C123xx.h"
#include<string.h>

void blink(void);
void delay_s(void);
void delay_l(void);

I2CHandle master;

int main(void)
{
	DigitalPin(PF1,OUT,PullDn);
	DigitalPin(PF2,OUT,PullDn);
	DigitalPin(PF3,OUT,PullDn);
	
	//I2CInit(I2C0,I2C_SPEED_MODE_STD,100000,I2C_AUTO_ACK_ENABLE);
	
	WriteToPin(PF3,PIN_SET);

	while(1)
	{
		uint8_t error = I2CMasterSendByte(I2C1, 0x68, 65);
		if(error)	break;
		
		delay_l();
		blink();
	}
	
	WriteToPin(PF3,PIN_RESET);
	WriteToPin(PF2,PIN_SET);
	while(1);
	
	return 0;
}

/*  */
void blink(void)
{
	WriteToPin(PF1,PIN_SET);			delay_s();
	WriteToPin(PF1,PIN_RESET);		delay_s();
}

void delay_s(void)
{
	for(int i = 0; i<10000; i++)
		for(int j = 0; j<1000; j++);
}
void delay_l(void)
{
	for(int i = 0; i<35000; i++)
		for(int j = 0; j<1000; j++);
}