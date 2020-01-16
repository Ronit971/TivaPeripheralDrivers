#include "TM4C123xx.h"
#include "TM4C123xxGPIO_DRIVER.h"
#include "GPIO_PIN_NAMES.h"

void delay(void);

int main(void)
{
	GPIO_HANDLE button_zero;
	inpin(&button_zero,PF0,Digital,PullUp);
	
	GPIO_HANDLE led_zero;
	outpin(&led_zero,PF1,Digital,PullDn);
	GPIO_HANDLE led_one;
	outpin(&led_one,PF3,Digital,PullDn);

	
	while(1)
	{
		if(ReadFromPin(&button_zero))
		{
		WriteToPin(&led_zero,PIN_SET);
		delay();
		WriteToPin(&led_zero,PIN_RESET);
		delay();
		WriteToPin(&led_one,PIN_SET);
		delay();
		WriteToPin(&led_one,PIN_RESET);
		delay();
		}
	}
	return 0;
}

void delay(void)
{
	for(int i=0; i<1000; i++)
		for(int j=0; j<1000; j++)
		{
		}
}
