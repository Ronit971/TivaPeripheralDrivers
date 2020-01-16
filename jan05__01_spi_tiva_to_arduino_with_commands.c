#include "TM4C123xx.h"
#include <string.h>

#define SSI_COMMAND_1		51
#define SSI_COMMAND_2		52
#define SSI_COMMAND_3		53
#define SSI_COMMAND_4		54

void blink_red(void);
void blink_green(void);
void delay_s(void);
void delay_l(void);

int main(void)
{
	// Buttons to send different commands.
	DigitalPin(PC4,IN,PullUp);								//	For Command 1	-	Led blink once
	DigitalPin(PC5,IN,PullUp);								//	For Command 2	-	Led blink twice
	DigitalPin(PC6,IN,PullUp);								//	For Command 3	-	Led blink four times (fast)
	DigitalPin(PC7,IN,PullUp);								//	For Command 4	-	Led blink nine times (fast)
	
	DigitalPin(PF1,OUT,PullDn);								//	Red LED.
	DigitalPin(PF3,OUT,PullDn);								//	Green LED.
	blink_red();
	
	SSIStart(SSI3,SSI_Master_Mode);
	
	uint16_t	command = 0;
	uint8_t buttons = 0;
	
	while(1)
	{
		buttons = (ReadFromPort(GPIO_PORT_C) & 0xF0);						//	Read the state of all buttons at once.
		blink_green();																					//	Flash green led to acknowledge button read.
		
		// Send command corresponding to the buttons pressed.
		if( buttons & 0x10 )	{		command = SSI_COMMAND_1;			SSISendData(SSI3, &command, 16);	}
		if( buttons & 0x20 )	{		command = SSI_COMMAND_2;			SSISendData(SSI3, &command, 16);	}
		if( buttons & 0x40 )	{		command = SSI_COMMAND_3;			SSISendData(SSI3, &command, 16);	}
		if( buttons & 0x80 )	{		command = SSI_COMMAND_4;			SSISendData(SSI3, &command, 16);	}
		
		blink_red();
		blink_red();
	}
	return 0;
}

/*****************************************************************************************************************/

void blink_red(void)
{
	WriteToPin(PF1,PIN_SET);			delay_s();
	WriteToPin(PF1,PIN_RESET);		delay_s();
}

void blink_green(void)
{
	WriteToPin(PF3,PIN_SET);			delay_s();
	WriteToPin(PF3,PIN_RESET);		delay_s();
}


void delay_s(void)
{
	for(int i = 0; i<5000; i++)
		for(int j = 0; j<1000; j++);
}
void delay_l(void)
{
	for(int i = 0; i<50000; i++)
		for(int j = 0; j<1000; j++);
}