#include "TM4C123xx.h"

void delay(void)
{
	for(unsigned int d = 0; d<500000; d++);
}

int main(void)
{
	UseLEDs();
	blink(LED_RED);
	DigitalPin(PB0, OUT, PullDn);
	DigitalPin(PB1, OUT, PullDn);
	DigitalPin(PB2, OUT, PullDn);
	DigitalPin(PB3, OUT, PullDn);
	DigitalPin(PB4, OUT, PullDn);
	DigitalPin(PB5, OUT, PullDn);
	DigitalPin(PB6, OUT, PullDn);
	DigitalPin(PB7, OUT, PullDn);
	
	GPIO_reg* pGPIOx = GPIO_B_P;
	uint8_t Reg = 1;
	while(1)
	{
		for(int i = 0; i<8; i++)
		{
			pGPIOx->GPIO_DATA_BITS[Reg] = 0xFF;
			Reg *= 2;
			delay();
		}
		Reg = 1;
		for(int i = 0; i<8; i++)
		{
			pGPIOx->GPIO_DATA_BITS[Reg] = 0x00;
			Reg *= 2;
			delay();
		}
		Reg = 1;
	}
	return 0;
}
