/******************************************************************************************************************
*	@file			-	TM4C123xxGPIO_DRIVER.h																																							*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
*	This file contains prototypes of GPIO Driver APIs. Bit position macros and shorthands which are used by the			*
*	GPIO Driver APIs are also defined here.																																					*
*																																																									*
* @Note			-	All of the code present in the this file applies to TM4C123GH6PM microcontroller.										*
******************************************************************************************************************/



#ifndef TM4C123XXGPIO_DRIVER_H
#define TM4C123XXGPIO_DRIVER_H

#include "TM4C123xx.h"



/******************************************************************************************************************
*																								Bit Position Macros																								*
******************************************************************************************************************/
// NVIC EN0 Register
#define NVIC_EN0_GPIOA			0
#define NVIC_EN0_GPIOB			1
#define NVIC_EN0_GPIOC			2
#define NVIC_EN0_GPIOD			3
#define NVIC_EN0_GPIOE			4
#define NVIC_EN0_GPIOF			30



/******************************************************************************************************************
*																			Miscellaneous macros and shorthands																					*
******************************************************************************************************************/
//	GPIO Pin Modes
#define Digital				0
#define Analog				1

//	GPIO Pin Drive Strength
#define Two_mA				0
#define Four_mA				1
#define Eight_mA			2

//	GPIO Pull-Up, Pull-Down, and Open Drain configuration
#define PullUp				0
#define PullDn				1
#define OpenDr				2

//	GPIO Interrupt Trigger Modes
#define NoInterrupt		0
#define RisingEdge		1
#define FallingEdge		2
#define BothEdges			3
#define	HighLevel			4
#define	LowLevel			5

//	GPIO Alternate Function
#define NoAlternateFunction 99	/**********************************************************************************
																*	If a GPIO Pin is configured for an alternate function, it uses the peripheral		*
																*	name(define in mcu header file) as an identity. If the pin is simply used as a	*
																*	GPIO, then this macro is used to initialize/configure the pin.									*
																**********************************************************************************/



/******************************************************************************************************************
*																					GPIO Interrupt Pin Numbers																							*
*	These variables hold the pin number which has been configured as an Interrupt pin for a particular port.				*
*	Default value for all these variables is 99(defined in the source file). This value also suggests that a				*
*	particular port does not have any pin configured as an interrupt pin.																						*
******************************************************************************************************************/
extern uint8_t GPIOA_INT_PIN;
extern uint8_t GPIOB_INT_PIN;
extern uint8_t GPIOC_INT_PIN;
extern uint8_t GPIOD_INT_PIN;
extern uint8_t GPIOE_INT_PIN;
extern uint8_t GPIOF_INT_PIN;



/******************************************************************************************************************
*																					APIs Supported by this Driver																						*
*		Below are the prototypes for driver APIs																																			*
*		Definitions for these can be found in TM4C123xxGPIO_DRIVER.c file																							*
*																																																									*
*	void			GPIO_ClockControl()		-- Enable/Disable clock for a GPIO port																					*
*	void			GPIO_Init()						-- Initialize a GPIO port																												*
*	void			GPIO_DeInit()					-- De-Initialize or Reset a GPIO port																						*
*	void			DigitalPin()					-- Initialize a GPIO pin in Digital mode with some default configurations.			*
*	void			AnalogPin()						-- Initialize a GPIO pin in Analog	mode with some default configurations.			*
*	void			WriteToPin()					-- Write digital values to a GPIO pin																						*
*	void			WriteToPort()					-- Write digital values to a GPIO port																					*
*	void			ToggleGPIOPin()				-- Toggle the state of a GPIO pin																								*
*	uint8_t		ReadFromPin()					-- Read data from a GPIO pin																										*
*	uint8_t		ReadFromPort()				-- Read data from a GPIO port																										*
******************************************************************************************************************/
void			GPIO_Init(uint8_t pin, uint8_t Dir, uint8_t AltFn, uint8_t OpType, uint8_t Mode, uint8_t DriveStrength, uint8_t Trigger);	// Initialize a GPIO port
void			GPIO_DeInit(			uint8_t GPIO_PORT);															// De-Initialize or Reset a GPIO port
void			GPIO_ClockControl(uint8_t GPIO_Port, uint8_t Clk_En);							// Enable/Disable clock for a GPIO port

void			DigitalPin(uint8_t pin, uint8_t IOmode, uint8_t opType);					// Configure a pin in digital mode.
void			AnalogPin( uint8_t pin, uint8_t IOmode, uint8_t opType);					// Configure a pin in  analog mode.
void			InterruptPin(uint8_t pin, uint8_t triggerMode);										// Configure a pin with interrupt function.

void			ToggleGPIOPin(uint8_t pin);																				// Toggle the state of a GPIO pin
void			WriteToPin(		uint8_t pin, uint8_t Value);												// Write data to a GPIO pin
void			WriteToPort(	uint8_t GPIO_PORT, uint8_t Values);									// Write data to a GPIO port
uint8_t		ReadFromPin(	uint8_t pin);																				// Read data from a GPIO pin
uint8_t		ReadFromPort(	uint8_t GPIO_PORT);																	// Read data from a GPIO port

uint8_t		getAltFnNum(uint8_t AltFnName);																		// Get the alternate function no. for a specific peripheral


/******************************************************************************************************************
*																									Broken APIs																											*
*		Below are the prototypes for functions/APIs which are not in a working state yet.															*
******************************************************************************************************************/
void	interruptpin(uint8_t pin, void (*isr_func)(void), uint8_t triggerMode);

#endif