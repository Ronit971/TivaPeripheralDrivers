#include "TM4C123xx.h"

void delay(void)
{
	for(int i=0; i<5000; i++)
		for(int j=0; j<1000; j++)
		{
		}
}

int main(void)
{
	DigitalPin(PF1, OUT, PullDn);
	DigitalPin(PF2, OUT, PullDn);
	DigitalPin(PF3, OUT, PullDn);

	WriteToPin(PF1,PIN_SET);			delay();
	WriteToPin(PF1,PIN_RESET);
	WriteToPin(PF2,PIN_SET);			delay();
	WriteToPin(PF2,PIN_RESET);
	WriteToPin(PF3,PIN_SET);			delay();
	WriteToPin(PF3,PIN_RESET);		delay();
	
	for(int i =0; i<2; i++)
	{
		WriteToPin(PF1,PIN_SET);
		WriteToPin(PF2,PIN_SET);
		WriteToPin(PF3,PIN_SET);
		
		delay();
		
		WriteToPin(PF1,PIN_RESET);
		WriteToPin(PF2,PIN_RESET);
		WriteToPin(PF3,PIN_RESET);
		
		delay();
	}
	return 1;
}
