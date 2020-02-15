#include "TM4C123xx.h"

#define Hello (uint8_t)0x69
#define SlaveAddress (uint8_t)0x68

void delay(void)
{
	for( unsigned long i = 0; i<1000000; i++);
}

int main(void)
{
	UseLEDs();
	I2CInit(I2C0, I2C_SPEED_MODE_STD, 100000, I2C_AUTO_ACK_ENABLE, NO);
	uint8_t error = 0, preverror = 0;
	
	while(1)
	{
		error = I2CMasterSendByte(I2C0, SlaveAddress, Hello);
		if(error != preverror)
		{
			if(error)
			{
				TurnOff(LED_GREEN);
				TurnOn(LED_RED);
			}
			else
			{
				TurnOn(LED_GREEN);
				TurnOff(LED_RED);
			}
			preverror = error;
		}
		
		delay();
	}
}
