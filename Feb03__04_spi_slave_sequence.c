#include "TM4C123xx.h"

int main(void)
{
	UseLEDs();
	
	blink(LED_RED);
	
	SPIStart(SSI3, SSI_Slave_Mode_OutDis, SSI_NoInterrupts);
	
	//uint16_t command[] = {0x1234, 0x5678, 0x9ABC, 0xDEF0 };
	
	uint16_t command[4] = {0,0,0,0};
	
	while(1)
	{
		SSIRecvData(SSI3, command, 64);
		for( int i = 0; i<4; i++)
			switch(command[i])
			{
				case 1:		WhiteLEDoff();
									blink(LED_GREEN);
									break;
			
				case 2:		WhiteLEDoff();
									blink(LED_BLUE);
									break;
			
				case 3:		WhiteLEDoff();
									blink(LED_RED);
									break;
			
				case 0:		TurnOn(LED_RED);
									break;
				
				default:	WhiteLEDon();
			}
	}
	
	return 0;
}
