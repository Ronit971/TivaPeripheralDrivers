#include "TM4C123xx.h"

int main(void)
{
	UseLEDs();
	
	blink(LED_RED);
	blink(LED_BLUE);
	blink(LED_GREEN);
	
	WhiteLEDon();
	WhiteLEDoff();
	while(1);
	return 0;
}
