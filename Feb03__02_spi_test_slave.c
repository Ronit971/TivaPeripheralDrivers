#include "TM4C123xx.h"

#define B1IsPressed				0x1			//	Command: Button 1 is pressed.					=>	Blink Green LED once.
#define B2IsPressed				0x2			//	Command: Button 2 is pressed.					=>	Blink Blue LED once.
#define BothArePressed		0x3			//	Command: Both buttons are pressed.		=>	Blink Red LED once.
#define NoButtonPressed		0x0			//	Command: No button is pressed.				=>	Make Red LED on.

int main(void)
{
	UseLEDs();
	
	blink(LED_RED);
	
	SPIStart(SSI3, SSI_Slave_Mode_OutDis, SSI_NoInterrupts);
	
	uint16_t	command = 0;
	
	while(1)
	{
		SSIRecv(SSI3, &command);
		switch(command)
		{
			case B1IsPressed:					WhiteLEDoff();
																blink(LED_GREEN);
																break;
			
			case B2IsPressed:					WhiteLEDoff();
																blink(LED_BLUE);
																break;
			
			case BothArePressed:			WhiteLEDoff();
																blink(LED_RED);
																break;
			
			case NoButtonPressed:			TurnOn(LED_RED);
																break;
			default:	WhiteLEDon();
		}
	}
	return 0;
}
