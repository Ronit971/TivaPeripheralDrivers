/******************************************************************************************************************
*	@file			-	TM4C123xx.h																																													*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
* This file contains base addresses of core components, base addresses of peripherals, core components' register	*
*	definitions, peripheral register definitions, pointers to peripheral registers, and clock enable/disable macros.*
* This file also contains some aliases and peripheral name definitions which are used in the other files.					*
*																																																									*
*		Things that need to be changed/improved:-																																			*
*			<>	Change the data type of all reserved registers to uint8_t and update the array size accordingly, so			*
*					that it is easier to assign the size of reserved array. Also it would help in debugging.								*
*			<>	Add bus selection feature in every relevant function.																										*
*			<>	Update the Exception Handler register definition.																												*
*			<>	Change nvic register access pointer name to capital letters, and update the files which use it.					*
*			<>	Change ssi register name to capital letters, and update the files which use it.													*
*																																																									*
* @Note			-	All of the code present in the this file applies to TM4C123GH6PM microcontroller.										*
******************************************************************************************************************/

/******************************************************************************************************************
*	Sections in this file:-																																													*
* 0. Peripheral Names																																															*
*	1. Core Components																																															*
*			1.1	Base Addresses																																													*
*			1.2	System Control Block																																										*
*			1.3	Exception Handlers																																											*
*			1.4	NVIC: Nested Vector Interrupt Controller																																*
* 2. GPIO Modules																																																	*
* 3. SSI Modules																																																	*
*	4. I2C Modules																																																	*
*	5. UART Modules																																																	*
*																																																									*
*	9.	Miscellaneous macros & aliases																																							*
*	9.	Driver & other dependencies																																									*
*																																																									*
*		Each peripheral has the following sub-sections:-																															*
*		1.	Base Addresses.																																														*
*		2.	Clock Enable & Disable Macros.																																						*
*		3.	Peripheral Register Definition.																																						*
*		4.	Module Access Pointers.																																										*
******************************************************************************************************************/



#ifndef TM4C123XX_H
#define TM4C123XX_H

#include<stdint.h>
#include<stdlib.h>

#define __vo volatile
#define __reg volatile uint32_t



/******************************************************************************************************************
*																									Peripheral Names																								*
******************************************************************************************************************/

// 1 - GPIO ports
#define GPIO_PORT_A 0
#define GPIO_PORT_B 1
#define GPIO_PORT_C 2
#define GPIO_PORT_D 3
#define GPIO_PORT_E 4
#define GPIO_PORT_F 5

// 2 - Synchronous Serial Interface (SSI)
#define SSI0 6
#define SSI1 7
#define SSI2 8
#define SSI3 9

// 3 - Inter Integrated Circuit (I2C) Interface
#define I2C0 10
#define I2C1 11
#define I2C2 12
#define I2C3 13

// 4 - UART
#define UART0 14
#define UART1 15
#define UART2 16
#define UART3 17
#define UART4 18
#define UART5 19
#define UART6 20
#define UART7 21

// 5 - Controller Area Network (CAN) Module
#define CAN0 22
#define CAN1 23

// 6 - General Purpose Timers
#define Timer0 24
#define Timer1 25
#define Timer2 26
#define Timer3 27
#define Timer4 28
#define Timer5 29

#define Timer0W 30
#define Timer1W 31
#define Timer2W 32
#define Timer3W 33
#define Timer4W 34
#define Timer5W 35



/******************************************************************************************************************
*																								 CORE COMPONENTS																									*
******************************************************************************************************************/

//	1.1 - Base Addresses
#define FLASH_BASE_ADDR								0X00000000U							// Base Addr of Flash Memory
#define SRAM_BASE_ADDR								0x20000000U							// Base Addr of SRAM1

#define CORE_PERIPHERAL_BASE_ADDR 		0xE000E000U							// Base Addr of Core Peripherals
#define SYSTEM_CONTROL_BASE_ADDR			0x400FE000U							// Base Addr of System Control Block Register
#define NVIC_BASE_ADDR								0xE000E100U							// Base Addr of NVIC registers
#define VECTOR_TABLE_BASE_ADDR				0x00000000U							// Base Addr of Vector Table



//	1.2 - System Control Block : Register Definition

typedef struct
{
	__vo uint32_t  DID0;                              // Device Identification 0
  __vo uint32_t  DID1;                              // Device Identification 1
  __vo uint32_t  DC0;                               // Device Capabilities 0
	__vo uint32_t  RESERVED1_0;
  __vo uint32_t  DC1;                               // Device Capabilities 1
  __vo uint32_t  DC2;                               // Device Capabilities 2
  __vo uint32_t  DC3;                               // Device Capabilities 3
  __vo uint32_t  DC4;                               // Device Capabilities 4
  __vo uint32_t  DC5;                               // Device Capabilities 5
  __vo uint32_t  DC6;                               // Device Capabilities 6
  __vo uint32_t  DC7;                               // Device Capabilities 7
  __vo uint32_t  DC8;                               // Device Capabilities 8
  __vo uint32_t  PBORCTL;                           // Brown-Out Reset Control
	__vo uint32_t  RESERVED1_1[3];
  __vo uint32_t  SRCR0;                             // Software Reset Control 0
  __vo uint32_t  SRCR1;                             // Software Reset Control 1
  __vo uint32_t  SRCR2;                             // Software Reset Control 2
	__vo uint32_t  RESERVED1_2;
  __vo uint32_t  RIS;                               // Raw Interrupt Status
  __vo uint32_t  IMC;                               // Interrupt Mask Control
  __vo uint32_t  MISC;                              // Masked Interrupt Status and Clear
  __vo uint32_t  RESC;                              // Reset Cause
  __vo uint32_t  RCC;                               // Run-Mode Clock Configuration
	__vo uint32_t  RESERVED1_3[2];
  __vo uint32_t  GPIOHBCTL;                         // GPIO High-Performance Bus Control
  __vo uint32_t  RCC2;                              // Run-Mode Clock Configuration 2
	__vo uint32_t  RESERVED1_4[2];
  __vo uint32_t  MOSCCTL;                           // Main Oscillator Control
	__vo uint32_t  RESERVED1_5[32];
  __vo uint32_t  RCGC0;                             // Run Mode Clock Gating Control Register 0
  __vo uint32_t  RCGC1;                             // Run Mode Clock Gating Control Register 1
  __vo uint32_t  RCGC2;                             // Run Mode Clock Gating Control Register 2
	__vo uint32_t  RESERVED1_6;
  __vo uint32_t  SCGC0;                             // Sleep Mode Clock Gating Control Register 0
  __vo uint32_t  SCGC1;                             // Sleep Mode Clock Gating Control Register 1
  __vo uint32_t  SCGC2;                             // Sleep Mode Clock Gating Control Register 2
	__vo uint32_t  RESERVED1_7;
  __vo uint32_t  DCGC0;                             // Deep Sleep Mode Clock Gating Control Register 0
  __vo uint32_t  DCGC1;                             // Deep-Sleep Mode Clock Gating Control Register 1
  __vo uint32_t  DCGC2;                             // Deep Sleep Mode Clock Gating Control Register 2
	__vo uint32_t  RESERVED1_8[6];
  __vo uint32_t  DSLPCLKCFG;                        // Deep Sleep Clock Configuration
	__vo uint32_t  RESERVED1_9;
  __vo uint32_t  SYSPROP;                           // System Properties
  __vo uint32_t  PIOSCCAL;                          // Precision Internal Oscillator Calibration
  __vo uint32_t  PIOSCSTAT;                         // Precision Internal Oscillator Statistics
	__vo uint32_t  RESERVED1_10[2];
  __vo uint32_t  PLLFREQ0;                          // PLL Frequency 0
  __vo uint32_t  PLLFREQ1;                          // PLL Frequency 1
  __vo uint32_t  PLLSTAT;                           // PLL Status
	__vo uint32_t  RESERVED1_11[7];
  __vo uint32_t  SLPPWRCFG;                         // Sleep Power Configuration
  __vo uint32_t  DSLPPWRCFG;                        // Deep-Sleep Power Configuration
  __vo uint32_t  DC9;                               // Device Capabilities 9
	__vo uint32_t  RESERVED1_12[3];
  __vo uint32_t  NVMSTAT;                           // Non-Volatile Memory Information
	__vo uint32_t  RESERVED1_13[4];
  __vo uint32_t  LDOSPCTL;                          // LDO Sleep Power Control
	__vo uint32_t  RESERVED1_14;
  __vo uint32_t  LDODPCTL;                          // LDO Deep-Sleep Power Control
	__vo uint32_t  RESERVED1_15[80];
  __vo uint32_t  PPWD;                              // Watchdog Timer Peripheral Present
  __vo uint32_t  PPTIMER;                           // 16/32-Bit General-Purpose Timer Peripheral Present
  __vo uint32_t  PPGPIO;                            // General-Purpose Input/Output Peripheral Present
  __vo uint32_t  PPDMA;                             // Micro Direct Memory Access Peripheral Present
	__vo uint32_t  RESERVED1_16;
  __vo uint32_t  PPHIB;                             // Hibernation Peripheral Present
  __vo uint32_t  PPUART;                            // Universal Asynchronous Receiver/Transmitter Peripheral Present
  __vo uint32_t  PPSSI;                             // Synchronous Serial Interface Peripheral Present
  __vo uint32_t  PPI2C;                             // Inter-Integrated Circuit Peripheral Present
	__vo uint32_t  RESERVED1_17;
  __vo uint32_t  PPUSB;                             // Universal Serial Bus Peripheral Present
	__vo uint32_t  RESERVED1_18[2];
  __vo uint32_t  PPCAN;                             // Controller Area Network Peripheral Present
  __vo uint32_t  PPADC;                             // Analog-to-Digital Converter Peripheral Present
  __vo uint32_t  PPACMP;                            // Analog Comparator Peripheral Present
  __vo uint32_t  PPPWM;                             // Pulse Width Modulator Peripheral Present
  __vo uint32_t  PPQEI;                             // Quadrature Encoder Interface Peripheral Present
	__vo uint32_t  RESERVED1_19[4];
  __vo uint32_t  PPEEPROM;                          // EEPROM Peripheral Present
  __vo uint32_t  PPWTIMER;                          // 32/64-Bit Wide General-Purpose Timer Peripheral Present
	__vo uint32_t  RESERVED1_20[104];
  __vo uint32_t  SRWD;                              // Watchdog Timer Software Reset/
  __vo uint32_t  SRTIMER;                           // 16/32-Bit General-Purpose Timer Software Reset
  __vo uint32_t  SRGPIO;                            // General-Purpose Input/Output Software Reset
  __vo uint32_t  SRDMA;                             // Micro Direct Memory Access Software Reset
	__vo uint32_t  RESERVED1_21;
  __vo uint32_t  SRHIB;                             // Hibernation Software Reset
  __vo uint32_t  SRUART;                            // Universal Asynchronous Receiver/Transmitter Software Reset
  __vo uint32_t  SRSSI;                             // Synchronous Serial Interface Software Reset
  __vo uint32_t  SRI2C;                             // Inter-Integrated Circuit Software Reset
	__vo uint32_t  RESERVED1_22;
  __vo uint32_t  SRUSB;                             // Universal Serial Bus Software Reset
	__vo uint32_t  RESERVED1_23[2];
  __vo uint32_t  SRCAN;                             // Controller Area Network Software Reset
  __vo uint32_t  SRADC;                             // Analog-to-Digital Converter Software Reset
  __vo uint32_t  SRACMP;                            // Analog Comparator Software Reset
  __vo uint32_t  SRPWM;                             // Pulse Width Modulator Software Reset
  __vo uint32_t  SRQEI;                             // Quadrature Encoder Interface Software Reset
	__vo uint32_t  RESERVED1_24[4];
  __vo uint32_t  SREEPROM;                          // EEPROM Software Reset
  __vo uint32_t  SRWTIMER;                          // 32/64-Bit Wide General-Purpose Timer Software Reset
	__vo uint32_t  RESERVED1_25[40];
  __vo uint32_t  RCGCWD;                            // Watchdog Timer Run Mode Clock Gating Control
  __vo uint32_t  RCGCTIMER;                         // 16/32-Bit General-Purpose Timer Run Mode Clock Gating Control
  __vo uint32_t  RCGCGPIO;                          // General-Purpose Input/Output Run Mode Clock Gating Control
  __vo uint32_t  RCGCDMA;                           // Micro Direct Memory Access Run Mode Clock Gating Control
	__vo uint32_t  RESERVED1_26;
  __vo uint32_t  RCGCHIB;                           // Hibernation Run Mode Clock Gating Control
  __vo uint32_t  RCGCUART;                          // Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating Control
  __vo uint32_t  RCGCSSI;                           // Synchronous Serial Interface Run Mode Clock Gating Control
  __vo uint32_t  RCGCI2C;                           // Inter-Integrated Circuit Run Mode Clock Gating Control
	__vo uint32_t  RESERVED1_27;
  __vo uint32_t  RCGCUSB;                           // Universal Serial Bus Run Mode Clock Gating Control
	__vo uint32_t  RESERVED1_28[2];
  __vo uint32_t  RCGCCAN;                           // Controller Area Network Run Mode Clock Gating Control
  __vo uint32_t  RCGCADC;                           // Analog-to-Digital Converter Run Mode Clock Gating Control
  __vo uint32_t  RCGCACMP;                          // Analog Comparator Run Mode Clock Gating Control
  __vo uint32_t  RCGCPWM;                           // Pulse Width Modulator Run Mode Clock Gating Control
  __vo uint32_t  RCGCQEI;                           // Quadrature Encoder Interface Run Mode Clock Gating Control
	__vo uint32_t  RESERVED1_29[4];
  __vo uint32_t  RCGCEEPROM;                        // EEPROM Run Mode Clock Gating Control
  __vo uint32_t  RCGCWTIMER;                        // 32/64-Bit Wide General-Purpose Timer Run Mode Clock Gating Control
	__vo uint32_t  RESERVED1_30[40];
  __vo uint32_t  SCGCWD;                            // Watchdog Timer Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCTIMER;                         // 16/32-Bit General-Purpose Timer Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCGPIO;                          // General-Purpose Input/Output Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCDMA;                           // Micro Direct Memory Access Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED1_31;
  __vo uint32_t  SCGCHIB;                           // Hibernation Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCUART;                          // Universal Asynchronous Receiver/Transmitter Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCSSI;                           // Synchronous Serial Interface Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCI2C;                           // Inter-Integrated Circuit Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED1_32;
  __vo uint32_t  SCGCUSB;                           // Universal Serial Bus Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED1_33[2];
  __vo uint32_t  SCGCCAN;                           // Controller Area Network Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCADC;                           // Analog-to-Digital Converter Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCACMP;                          // Analog Comparator Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCPWM;                           // Pulse Width Modulator Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCQEI;                           // Quadrature Encoder Interface Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED1_34[4];
  __vo uint32_t  SCGCEEPROM;                        // EEPROM Sleep Mode Clock Gating Control
  __vo uint32_t  SCGCWTIMER;                        // 32/64-Bit Wide General-Purpose Timer Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED1_35[40];
  __vo uint32_t  DCGCWD;                            // Watchdog Timer Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCTIMER;                         // 16/32-Bit General-Purpose Timer Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCGPIO;                          // General-Purpose Input/Output Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCDMA;                           // Micro Direct Memory Access Deep-Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED1_36;
  __vo uint32_t  DCGCHIB;                           // Hibernation Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCUART;                          // Universal Asynchronous Receiver/Transmitter Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCSSI;                           // Synchronous Serial Interface Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCI2C;                           // Inter-Integrated Circuit Deep-Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED1_37;
  __vo uint32_t  DCGCUSB;                           // Universal Serial Bus Deep-Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED1_38[2];
  __vo uint32_t  DCGCCAN;                           // Controller Area Network Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCADC;                           // Analog-to-Digital Converter Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCACMP;                          // Analog Comparator Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCPWM;                           // Pulse Width Modulator Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCQEI;                           // Quadrature Encoder Interface Deep-Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED1_39[4];
  __vo uint32_t  DCGCEEPROM;                        // EEPROM Deep-Sleep Mode Clock Gating Control
  __vo uint32_t  DCGCWTIMER;                        // 32/64-Bit Wide General-Purpose Timer Deep-Sleep Mode Clock Gating Control
	__vo uint32_t  RESERVED1_40[104];
  __vo uint32_t  PRWD;                              // Watchdog Timer Peripheral Ready
  __vo uint32_t  PRTIMER;                           // 16/32-Bit General-Purpose Timer Peripheral Ready
  __vo uint32_t  PRGPIO;                            // General-Purpose Input/Output Peripheral Ready
  __vo uint32_t  PRDMA;                             // Micro Direct Memory Access Peripheral Ready
	__vo uint32_t  RESERVED1_41;
  __vo uint32_t  PRHIB;                             // Hibernation Peripheral Ready
  __vo uint32_t  PRUART;                            // Universal Asynchronous Receiver/Transmitter Peripheral Ready
  __vo uint32_t  PRSSI;                             // Synchronous Serial Interface Peripheral Ready
  __vo uint32_t  PRI2C;                             // Inter-Integrated Circuit Peripheral Ready
	__vo uint32_t  RESERVED1_42;
  __vo uint32_t  PRUSB;                             // Universal Serial Bus Peripheral Ready
	__vo uint32_t  RESERVED1_43[2];
  __vo uint32_t  PRCAN;                             // Controller Area Network Peripheral Ready
  __vo uint32_t  PRADC;                             // Analog-to-Digital Converter Peripheral Ready
  __vo uint32_t  PRACMP;                            // Analog Comparator Peripheral Ready
  __vo uint32_t  PRPWM;                             // Pulse Width Modulator Peripheral Ready
  __vo uint32_t  PRQEI;                             // Quadrature Encoder Interface Peripheral Ready
	__vo uint32_t  RESERVED1_44[4];
  __vo uint32_t  PREEPROM;                          // EEPROM Peripheral Ready
  __vo uint32_t  PRWTIMER; 
}SYSCTL_reg;

#define SYSCTL ( (SYSCTL_reg*)SYSTEM_CONTROL_BASE_ADDR )		// Pointer for Register Access (System Control Block)



//	1.3 - Exception Handlers : Register Definition

typedef struct
{
	__vo uint8_t	RESERVED2_1[64];															// Offset(0x40) for System exceptions
	__vo uint32_t	_GPIOA;
	__vo uint32_t	_GPIOB;
	__vo uint32_t	_GPIOC;
	__vo uint32_t	_GPIOD;
	__vo uint32_t	_GPIOE;
	__vo uint32_t	_UART0;
	__vo uint32_t	_UART1;
	__vo uint32_t	_SSI0;
	__vo uint32_t	_I2C0;
	__vo uint32_t	_PWM0_FAULT;
	__vo uint32_t	_PWM0_GENERATOR0;
	__vo uint32_t	_PWM0_GENERATOR1;
	__vo uint32_t	_PWM0_GENERATOR2;
	__vo uint32_t	_QEI0;
	__vo uint32_t	_ADC0_SEQUENCE0;
	__vo uint32_t	_ADC0_SEQUENCE1;
	__vo uint32_t	_ADC0_SEQUENCE2;
	__vo uint32_t	_ADC0_SEQUENCE3;
	__vo uint32_t	_WATCHDOG_TIMER_0_AND_1;
	__vo uint32_t	_TIMER_0A;
	__vo uint32_t	_TIMER_0B;
	__vo uint32_t	_TIMER_1A;
	__vo uint32_t	_TIMER_1B;
	__vo uint32_t	_TIMER_2A;
	__vo uint32_t	_TIMER_2B;
	__vo uint32_t	_ANALOG_COMPARATOR0;
	__vo uint32_t	_ANALOG_COMPARATOR1;
	
	__vo uint8_t	RESERVED2_2[4];
	
	__vo uint32_t	_SYSTEM_CONTROL;
	__vo uint32_t	_FLASH_MEM_CTRL_AND_EEPROM_CTRL;
	__vo uint32_t	_GPIOF;
	
	// There are more to be added here.
	//__vo uint32_t	_
}Exception_Handler_reg;

		/* Pointer for Register Access (Exception Handlers)	*/
#define ExceptionHandlers ( (Exception_Handler_reg*)VECTOR_TABLE_BASE_ADDR )



//	1.4 - Nested Vector Interrupt Controller (NVIC) : Register Definition

typedef struct
{
	__vo uint32_t EN[5];						__vo uint32_t RESERVED3_1[27];
	__vo uint32_t DIS[5];						__vo uint32_t RESERVED3_2[27];
	__vo uint32_t PEND[5];					__vo uint32_t RESERVED3_3[27];
	__vo uint32_t UNPEND[5];				__vo uint32_t RESERVED3_4[27];
	__vo uint32_t ACTIVE[5];				__vo uint32_t RESERVED3_5[59];
	__vo uint32_t PRI[35];					__vo uint32_t RESERVED3_6[669];
	__vo uint32_t SWTRIG;
	
}NVIC_reg;

#define NVIC ( (NVIC_reg*)NVIC_BASE_ADDR )
/****************************************************************************
*		NVIC Enable Registers Bit definitions																		*
*																																						*
*							En 0 Reg		En 1 Reg		En 2 Reg		En 3 Reg		En 4 Reg			*
*			Bit		 		Intr#			 Intr#			 Intr#			 Intr#			 Intr#				*
*			0...........0..........32..........64..........96.........128					*
*			1						1					 33					 65					 97					129					*
*			2...........2..........34..........66..........98.........130					*
*			3						3					 35					 67					 99					131					*
*			4...........4..........36..........68..........100........132					*
*			5						5					 37					 69					 101				133					*
*			6...........6..........38..........70..........102........134					*
*			7						7					 39					 71					 103				135					*
*			8...........8..........40..........72..........104........136					*
*			9						9					 41					 73					 105				137					*
*			10..........10.........42..........74..........106........138					*
*			11					11				 43				 	 75					 107										*
*			12..........12.........44..........76..........108										*
*			13					13				 45					 77					 109										*
*			14..........14.........46..........78..........110										*
*			15					15				 47					 79					 111										*
*			16..........16.........48..........80..........112										*
*			17					17				 49					 81					 113										*
*			18..........18.........50..........82..........114										*
*			19					19				 51					 83					 115										*
*			20..........20.........52..........84..........116										*
*			21					21				 53					 85					 117										*
*			22..........22.........54..........86..........118										*
*			23					23				 55					 87					 119										*
*			24..........24.........56..........88..........120										*
*			25					25				 57					 89					 121										*
*			26..........26.........58..........90..........122										*
*			27					27				 59					 91					 123										*
*			28..........28.........60..........92..........124										*
*			29					29				 61					 93					 125										*
*			30..........30.........62..........94..........126										*
*			31					31				 63					 95					 127										*
****************************************************************************/



/******************************************************************************************************************
*																							 			GPIO Ports																										*
*		All GPIO  ports are connected to both AHB and APB Bus ( GPIOxP => APB bus GPIOxH => AHB bus )									*
******************************************************************************************************************/

//	2.1 Base Addresses

#define GPIO_BASE																		 0x40004000U
#define GPIOAP_BASE_ADDRESS							(GPIO_BASE + 0x00000000U)
#define GPIOBP_BASE_ADDRESS							(GPIO_BASE + 0x00001000U)
#define GPIOCP_BASE_ADDRESS							(GPIO_BASE + 0x00002000U)
#define GPIODP_BASE_ADDRESS							(GPIO_BASE + 0x00003000U)
#define GPIOEP_BASE_ADDRESS							(GPIO_BASE + 0x00020000U)
#define GPIOFP_BASE_ADDRESS							(GPIO_BASE + 0x00021000U)

#define GPIOAH_BASE_ADDRESS							(GPIO_BASE + 0x00054000U)
#define GPIOBH_BASE_ADDRESS							(GPIO_BASE + 0x00055000U)
#define GPIOCH_BASE_ADDRESS							(GPIO_BASE + 0x00056000U)
#define GPIODH_BASE_ADDRESS							(GPIO_BASE + 0x00057000U)
#define GPIOEH_BASE_ADDRESS							(GPIO_BASE + 0x00058000U)
#define GPIOFH_BASE_ADDRESS							(GPIO_BASE + 0x00059000U)


//	2.2 Clock Enable and Disable Macros

#define GPIOA_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<0) )
#define GPIOB_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<1) )
#define GPIOC_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<2) )
#define GPIOD_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<3) )
#define GPIOE_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<4) )
#define GPIOF_PCLK_EN() ( SYSCTL->RCGCGPIO |= (1<<5) )

#define GPIOA_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<0) )
#define GPIOB_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<1) )
#define GPIOC_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<2) )
#define GPIOD_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<3) )
#define GPIOE_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<4) )
#define GPIOF_PCLK_DIS() ( SYSCTL->RCGCGPIO &= ~(1<<5) )


//	2.3 Register Definition

typedef struct
{
	__vo uint32_t GPIO_DATA_A[255];						//	GPIO Data (Address Masked)
	__vo uint32_t GPIO_DATA;									//	GPIO Data Register (All bits can be changed)
	__vo uint32_t GPIO_DIR;										//	GPIO Direction Register
	__vo uint32_t GPIO_IS;										//	GPIO Interrupt Sense Register
	__vo uint32_t GPIO_IBE;										//	GPIO Interrupt Both Edges
	__vo uint32_t GPIO_IEV;										//	GPIO Interrupt Event
	__vo uint32_t GPIO_IM;										//	GPIO Interrupt Mask
	__vo uint32_t GPIO_RIS;										//	GPIO Raw Interrupt Status
	__vo uint32_t GPIO_MIS;										//	GPIO Masked Interrupt Status
	__vo uint32_t GPIO_ICR;										//	GPIO Interrupt Clear
	__vo uint32_t GPIO_AFSEL;									//	GPIO Alternate Function Select
	__vo uint32_t RESERVED4_1[55];
	__vo uint32_t GPIO_DR2R;									//	GPIO Drive Strength - 2mA
	__vo uint32_t GPIO_DR4R;									//	GPIO Drive Strength - 4mA
	__vo uint32_t GPIO_DR8R;									//	GPIO Drive Strength - 8mA
	__vo uint32_t GPIO_ODR;										//	GPIO Open Drain Register
	__vo uint32_t GPIO_PUR;										//	GPIO Pull Up Register
	__vo uint32_t GPIO_PDR;										//	GPIO Pull Down Register
	__vo uint32_t GPIO_SLR;										//	GPIO Slew Rate
	__vo uint32_t GPIO_DEN;										//	GPIO Digital Enable Register
	__vo uint32_t GPIO_LOCK;									//	GPIO Lock Register
	__vo uint32_t GPIO_CR;										//	GPIO Commit Register
	__vo uint32_t GPIO_AMSEL;									//	GPIO Analog Mode Select
	__vo uint32_t GPIO_PCTL;									//	GPIO Port Control
	__vo uint32_t GPIO_ADCCTL;								//	GPIO ADC Control
	__vo uint32_t GPIO_DMACTL;								//	GPIO DMA Control
	
	__vo uint32_t RESERVED4_2[678];
	
	/*	Registers defined below are READ_ONLY.*/
	__vo uint32_t GPIOPeriphlD4;
	__vo uint32_t GPIOPeriphlD5;
	__vo uint32_t GPIOPeriphlD6;
	__vo uint32_t GPIOPeriphlD7;
	__vo uint32_t GPIOPeriphlD0;
	__vo uint32_t GPIOPeriphlD1;
	__vo uint32_t GPIOPeriphlD2;
	__vo uint32_t GPIOPeriphlD3;
	__vo uint32_t GPIOPCellID0;
	__vo uint32_t GPIOPCellID1;
	__vo uint32_t GPIOPCellID2;
	__vo uint32_t GPIOPCellID3;
}GPIO_reg;


//	2.4 Module Access Pointers

#define GPIO_A_H 		( (GPIO_reg*) GPIOAH_BASE_ADDRESS )				//	Pointers for GPIO Module on AHB Bus
#define GPIO_B_H 		( (GPIO_reg*) GPIOBH_BASE_ADDRESS )
#define GPIO_C_H 		( (GPIO_reg*) GPIOCH_BASE_ADDRESS )
#define GPIO_D_H 		( (GPIO_reg*) GPIODH_BASE_ADDRESS )
#define GPIO_E_H 		( (GPIO_reg*) GPIOEH_BASE_ADDRESS )
#define GPIO_F_H 		( (GPIO_reg*) GPIOFH_BASE_ADDRESS )

#define GPIO_A_P 		( (GPIO_reg*) GPIOAP_BASE_ADDRESS )				//	Pointers for GPIO Module on APB Bus
#define GPIO_B_P 		( (GPIO_reg*) GPIOBP_BASE_ADDRESS )
#define GPIO_C_P 		( (GPIO_reg*) GPIOCP_BASE_ADDRESS )
#define GPIO_D_P 		( (GPIO_reg*) GPIODP_BASE_ADDRESS )
#define GPIO_E_P 		( (GPIO_reg*) GPIOEP_BASE_ADDRESS )
#define GPIO_F_P 		( (GPIO_reg*) GPIOFP_BASE_ADDRESS )



/******************************************************************************************************************
*																										SSI MODULES																										*
******************************************************************************************************************/

//	3.1 Base Addresses
#define SSI0_BASE_ADDRESS			0x40008000U
#define SSI1_BASE_ADDRESS			0x40009000U
#define SSI2_BASE_ADDRESS			0x4000A000U
#define SSI3_BASE_ADDRESS			0x4000B000U


//	3.2 Clock Enable and Disable Macros
#define SSI0_PCLK_EN() 		(SYSCTL->RCGCSSI |= (1<<0)	)
#define SSI1_PCLK_EN() 		(SYSCTL->RCGCSSI |= (1<<1)	)
#define SSI2_PCLK_EN() 		(SYSCTL->RCGCSSI |= (1<<2)	)
#define SSI3_PCLK_EN() 		(SYSCTL->RCGCSSI |= (1<<3)	)

#define SSI0_PCLK_DIS() 	(SYSCTL->RCGCSSI &= ~(1<<0)	)
#define SSI1_PCLK_DIS() 	(SYSCTL->RCGCSSI &= ~(1<<1)	)
#define SSI2_PCLK_DIS() 	(SYSCTL->RCGCSSI &= ~(1<<2)	)
#define SSI3_PCLK_DIS() 	(SYSCTL->RCGCSSI &= ~(1<<3)	)


//	3.3 Register Definition
typedef struct
{
	__vo uint32_t	SSI_CR[2];								// Control Registers 0, and 1
	__vo uint32_t	SSI_DR;										// Data Register
	__vo uint32_t	SSI_SR;										// Status Register
	__vo uint32_t	SSI_CPSR;									// Clock Prescalar
	__vo uint32_t	SSI_IM;										// Interrupt Mask
	__vo uint32_t	SSI_RIS;									// Raw Interrupt Status
	__vo uint32_t	SSI_MIS;									// Masked Interrupt Status
	__vo uint32_t	SSI_ICR;									// Interrupt Clear
	__vo uint32_t	SSI_DMACTL;								// DMA Control
	
	__vo uint8_t	Reserved5_1[4000];
	
	__vo uint32_t	SSI_CC;										// Clock Configuration
	
	__vo uint32_t	SSI_PeriphID4;
	__vo uint32_t	SSI_PeriphID5;
	__vo uint32_t	SSI_PeriphID6;
	__vo uint32_t	SSI_PeriphID7;
	__vo uint32_t	SSI_PeriphID0;
	__vo uint32_t	SSI_PeriphID1;
	__vo uint32_t	SSI_PeriphID2;
	__vo uint32_t	SSI_PeriphID3;
	__vo uint32_t	SSI_CellID[4];
	
}ssi_reg;


//	3.4 Module Access Pointers

#define pSSI0 		( (ssi_reg*) SSI0_BASE_ADDRESS )
#define pSSI1 		( (ssi_reg*) SSI1_BASE_ADDRESS )
#define pSSI2 		( (ssi_reg*) SSI2_BASE_ADDRESS )
#define pSSI3 		( (ssi_reg*) SSI3_BASE_ADDRESS )



/******************************************************************************************************************
*																										I2C MODULES																										*
******************************************************************************************************************/

//	4.1 Base Addresses

#define I2C0_BASE_ADDRESS			0x40020000U
#define I2C1_BASE_ADDRESS			0x40021000U
#define I2C2_BASE_ADDRESS			0x40022000U
#define I2C3_BASE_ADDRESS			0x40023000U


//	4.2 Clock Enable and Disable Macros

#define I2C0_PCLK_EN()			( SYSCTL->RCGCI2C |= (1<<0) )
#define I2C1_PCLK_EN()			( SYSCTL->RCGCI2C |= (1<<1) )
#define I2C2_PCLK_EN()			( SYSCTL->RCGCI2C |= (1<<2) )
#define I2C3_PCLK_EN()			( SYSCTL->RCGCI2C |= (1<<3) )

#define I2C0_PCLK_DIS()			( SYSCTL->RCGCI2C &= ~(1<<0) )
#define I2C1_PCLK_DIS()			( SYSCTL->RCGCI2C &= ~(1<<1) )
#define I2C2_PCLK_DIS()			( SYSCTL->RCGCI2C &= ~(1<<2) )
#define I2C3_PCLK_DIS()			( SYSCTL->RCGCI2C &= ~(1<<3) )


//	4.3 Register Definition

typedef struct
{
	/* I2C Master*/
	__vo uint32_t MSA;								// Master Slave Address
	__vo uint32_t MCS;								// Master Control/Status
	__vo uint32_t MDR;								// Master Data
	__vo uint32_t MTPR;								// Master Timer Period
	__vo uint32_t MIMR;								// Master Interrupt Mask
	__vo uint32_t MRIS;								// Master Raw Interrupt Status
	__vo uint32_t MMIS;								// Master Masked Interrupt Status
	__vo uint32_t MICR;								// Master Interrupt Clear
	__vo uint32_t MCR;								// Master Configuration
	__vo uint32_t MCLKOCNT;						// Master Clock Low Timeout Count
	__vo uint32_t	RESERVED6_1;
	__vo uint32_t MBMON;							// Master Bus Monitor
	__vo uint32_t	RESERVED6_2[2];
	__vo uint32_t MCR2;								// Master Configuration 2
	
	__vo uint32_t	RESERVED6_3[497];
	
	/* I2C Slave*/
	__vo uint32_t SOAR;								// Slave Own Address
	__vo uint32_t SCSR;								// Slave Control/Status
	__vo uint32_t SDR;								// Slave Data
	__vo uint32_t SIMR;								// Slave Interrupt Mask
	__vo uint32_t SRIS;								// Slave Raw Interrupt Status
	__vo uint32_t SMIS;								// Slave Masked Interrupt Status
	__vo uint32_t SICR;								// Slave Interrupt Clear
	__vo uint32_t SOAR2;							// Slave Own Address 2
	__vo uint32_t SACKCTL;						// Slave ACK Control
	
	__vo uint32_t	RESERVED6_4[487];
	
	/* I2C Control and Status*/
	__vo uint32_t PP;									// Peripheral Properties
	__vo uint32_t PC;									// Peripheral Configuration
	
}I2C_reg;


//	4.4 Module Access Pointers
#define pI2C0					( (I2C_reg*) I2C0_BASE_ADDRESS )
#define pI2C1					( (I2C_reg*) I2C1_BASE_ADDRESS )
#define pI2C2					( (I2C_reg*) I2C2_BASE_ADDRESS )
#define pI2C3					( (I2C_reg*) I2C3_BASE_ADDRESS )



/******************************************************************************************************************
*																									UART MODULES																										*
******************************************************************************************************************/

//	5.1 Base Addresses

#define UART0_BASE_ADDRESS			0x4000C000U
#define UART1_BASE_ADDRESS			0x4000D000U
#define UART2_BASE_ADDRESS			0x4000E000U
#define UART3_BASE_ADDRESS			0x4000F000U
#define UART4_BASE_ADDRESS			0x40010000U
#define UART5_BASE_ADDRESS			0x40011000U
#define UART6_BASE_ADDRESS			0x40012000U
#define UART7_BASE_ADDRESS			0x40013000U


//	5.2 Clock Enable and Disable Macros

#define UART0_PCLK_EN()				( SYSCTL->RCGCUART |= (1<<0) )
#define UART1_PCLK_EN()				( SYSCTL->RCGCUART |= (1<<1) )
#define UART2_PCLK_EN()				( SYSCTL->RCGCUART |= (1<<2) )
#define UART3_PCLK_EN()				( SYSCTL->RCGCUART |= (1<<3) )
#define UART4_PCLK_EN()				( SYSCTL->RCGCUART |= (1<<4) )
#define UART5_PCLK_EN()				( SYSCTL->RCGCUART |= (1<<5) )
#define UART6_PCLK_EN()				( SYSCTL->RCGCUART |= (1<<6) )
#define UART7_PCLK_EN()				( SYSCTL->RCGCUART |= (1<<7) )

#define UART0_PCLK_DIS()			( SYSCTL->RCGCUART &= ~(1<<0) )
#define UART1_PCLK_DIS()			( SYSCTL->RCGCUART &= ~(1<<1) )
#define UART2_PCLK_DIS()			( SYSCTL->RCGCUART &= ~(1<<2) )
#define UART3_PCLK_DIS()			( SYSCTL->RCGCUART &= ~(1<<3) )
#define UART4_PCLK_DIS()			( SYSCTL->RCGCUART &= ~(1<<4) )
#define UART5_PCLK_DIS()			( SYSCTL->RCGCUART &= ~(1<<5) )
#define UART6_PCLK_DIS()			( SYSCTL->RCGCUART &= ~(1<<6) )
#define UART7_PCLK_DIS()			( SYSCTL->RCGCUART &= ~(1<<7) )


//	5.3 Register Definition

typedef struct
{
	__vo uint32_t DR;											//	DATA Register
	__vo uint32_t RSR_ECR;								//	Receive Status / Error Clear
	__vo uint32_t	RESERVED7_1[4];
	__vo uint32_t FR;											//	Flag Register
	__vo uint32_t	RESERVED7_2;
	__vo uint32_t ILPR;										//	IrDA Low-Power Register
	__vo uint32_t IBRD;										//	Integer Baud Rate Divisor
	__vo uint32_t FBRD;										//	Fractional Baud Rate Divisior
	__vo uint32_t LCRH;										//	Line Control
	__vo uint32_t CTL;										//	Control
	__vo uint32_t IFLS;										//	Interrupt FIFO Level Select
	__vo uint32_t IM;											//	Interrupt Mask
	__vo uint32_t RIS;										//	Raw Interrupt Status
	__vo uint32_t MIS;										//	Masked Interrupt Status
	__vo uint32_t ICR;										//	Interrupt Clear Register
	__vo uint32_t DMACTL;									//	DMA Control
	__vo uint32_t	RESERVED7_3[22];
	__vo uint32_t _9BITADDR;							//	9 Bit Self Address
	__vo uint32_t _9BITAMASK;							//	9-Bit Self Address Mask
	__vo uint32_t	RESERVED7_4[965];
	__vo uint32_t PP;											//	Peripheral Properties
	__vo uint32_t CC;											//	Clock Configuration
	__vo uint32_t	RESERVED7_5;
	
	/* Registers Defined below are READ-ONLY */
	__vo uint32_t PeriphID4;							//	Peripheral Identification 4
	__vo uint32_t PeriphID5;							//	Peripheral Identification 5
	__vo uint32_t PeriphID6;							//	Peripheral Identification 6
	__vo uint32_t PeriphID7;							//	Peripheral Identification 7
	__vo uint32_t PeriphID0;							//	Peripheral Identification 0
	__vo uint32_t PeriphID1;							//	Peripheral Identification 1
	__vo uint32_t PeriphID2;							//	Peripheral Identification 2
	__vo uint32_t PeriphID3;							//	Peripheral Identification 3
	
	__vo uint32_t PCellID4;								//	Prime Cell Identification 0
	__vo uint32_t PCellID1;								//	Prime Cell Identification 1
	__vo uint32_t PCellID2;								//	Prime Cell Identification 2
	__vo uint32_t PCellID3;								//	Prime Cell Identification 3
	
}UART_Reg;


//	5.4 Module Access Pointers
#define pUART0					( (UART_Reg*) UART0_BASE_ADDRESS )
#define pUART1					( (UART_Reg*) UART1_BASE_ADDRESS )
#define pUART2					( (UART_Reg*) UART2_BASE_ADDRESS )
#define pUART3					( (UART_Reg*) UART3_BASE_ADDRESS )
#define pUART4					( (UART_Reg*) UART4_BASE_ADDRESS )
#define pUART5					( (UART_Reg*) UART5_BASE_ADDRESS )
#define pUART6					( (UART_Reg*) UART6_BASE_ADDRESS )
#define pUART7					( (UART_Reg*) UART7_BASE_ADDRESS )



/******************************************************************************************************************
*																				GENERAL PURPOSE TIMER MODULE (GPTM)																				*
******************************************************************************************************************/

//	7.1 Base Addresses
#define Timer0_BASE_ADDRESS 0x40030000
#define Timer1_BASE_ADDRESS 0x40031000
#define Timer2_BASE_ADDRESS 0x40032000
#define Timer3_BASE_ADDRESS 0x40033000
#define Timer4_BASE_ADDRESS 0x40034000
#define Timer5_BASE_ADDRESS 0x40035000

#define Timer0W_BASE_ADDRESS 0x40036000
#define Timer1W_BASE_ADDRESS 0x40037000
#define Timer2W_BASE_ADDRESS 0x4003C000
#define Timer3W_BASE_ADDRESS 0x4003D000
#define Timer4W_BASE_ADDRESS 0x4003E000
#define Timer5W_BASE_ADDRESS 0x4003F000


//	7.2 Clock Enable and Disable Macros

#define Timer0_PCLK_EN() ( SYSCTL->RCGCTIMER |= (1<<0) )
#define Timer1_PCLK_EN() ( SYSCTL->RCGCTIMER |= (1<<1) )
#define Timer2_PCLK_EN() ( SYSCTL->RCGCTIMER |= (1<<2) )
#define Timer3_PCLK_EN() ( SYSCTL->RCGCTIMER |= (1<<3) )
#define Timer4_PCLK_EN() ( SYSCTL->RCGCTIMER |= (1<<4) )
#define Timer5_PCLK_EN() ( SYSCTL->RCGCTIMER |= (1<<5) )

#define Timer0W_PCLK_EN() ( SYSCTL->RCGCWTIMER |= (1<<0) )
#define Timer1W_PCLK_EN() ( SYSCTL->RCGCWTIMER |= (1<<1) )
#define Timer2W_PCLK_EN() ( SYSCTL->RCGCWTIMER |= (1<<2) )
#define Timer3W_PCLK_EN() ( SYSCTL->RCGCWTIMER |= (1<<3) )
#define Timer4W_PCLK_EN() ( SYSCTL->RCGCWTIMER |= (1<<4) )
#define Timer5W_PCLK_EN() ( SYSCTL->RCGCWTIMER |= (1<<5) )


#define Timer0_PCLK_DIS() ( SYSCTL->RCGCTIMER &= ~(1<<0) )
#define Timer1_PCLK_DIS() ( SYSCTL->RCGCTIMER &= ~(1<<1) )
#define Timer2_PCLK_DIS() ( SYSCTL->RCGCTIMER &= ~(1<<2) )
#define Timer3_PCLK_DIS() ( SYSCTL->RCGCTIMER &= ~(1<<3) )
#define Timer4_PCLK_DIS() ( SYSCTL->RCGCTIMER &= ~(1<<4) )
#define Timer5_PCLK_DIS() ( SYSCTL->RCGCTIMER &= ~(1<<5) )

#define Timer0W_PCLK_DIS() ( SYSCTL->RCGCWTIMER &= ~(1<<0) )
#define Timer1W_PCLK_DIS() ( SYSCTL->RCGCWTIMER &= ~(1<<1) )
#define Timer2W_PCLK_DIS() ( SYSCTL->RCGCWTIMER &= ~(1<<2) )
#define Timer3W_PCLK_DIS() ( SYSCTL->RCGCWTIMER &= ~(1<<3) )
#define Timer4W_PCLK_DIS() ( SYSCTL->RCGCWTIMER &= ~(1<<4) )
#define Timer5W_PCLK_DIS() ( SYSCTL->RCGCWTIMER &= ~(1<<5) )


//	7.3 Register Definition

typedef struct
{
	__reg CFG;
	__reg TAMR;
	__reg TBMR;
	__reg CTL;
	__reg SYNC;
	__reg RESERVED0;
	__reg IMR;
	__reg RIS;
	__reg MIS;
	__reg ICR;
	__reg TAILR;
	__reg TBILR;
	__reg TAMATCHR;
	__reg TBMATCHR;
	__reg TAPR;
	__reg TBPR;
	__reg TAPMR;
	__reg TBPMR;
	__reg TAR;
	__reg TBR;
	__reg TAV;
	__reg TBV;
	__reg RTCPD;
	__reg TAPS;
	__reg TBPS;
	__reg TAPV;
	__reg TBPV;
	__reg RESERVED1[981];
	__reg PP;
}Timer_Reg;

// 7.4 Module Access Pointers

#define pTimer0 ( (Timer_Reg*) Timer0_BASE_ADDRESS)
#define pTimer1 ( (Timer_Reg*) Timer1_BASE_ADDRESS)
#define pTimer2 ( (Timer_Reg*) Timer2_BASE_ADDRESS)
#define pTimer3 ( (Timer_Reg*) Timer3_BASE_ADDRESS)
#define pTimer4 ( (Timer_Reg*) Timer4_BASE_ADDRESS)
#define pTimer5 ( (Timer_Reg*) Timer5_BASE_ADDRESS)

#define pTimer0W ( (Timer_Reg*) Timer0W_BASE_ADDRESS)
#define pTimer1W ( (Timer_Reg*) Timer1W_BASE_ADDRESS)
#define pTimer2W ( (Timer_Reg*) Timer2W_BASE_ADDRESS)
#define pTimer3W ( (Timer_Reg*) Timer3W_BASE_ADDRESS)
#define pTimer4W ( (Timer_Reg*) Timer4W_BASE_ADDRESS)
#define pTimer5W ( (Timer_Reg*) Timer5W_BASE_ADDRESS)

/******************************************************************************************************************
*																					Miscellaneous macros and aliases																				*
******************************************************************************************************************/
#define SYS_CLK				16000000					//	System Clock Frequency (in Hz)

#define ENABLE				1
#define DISABLE				0
#define ENABLED				ENABLE
#define DISABLED			DISABLE

#define SET						1
#define RESET					0
#define CLEAR					0
#define PIN_SET				SET
#define PIN_RESET			RESET
#define PIN_CLEAR			CLEAR

#define NO						0
#define YES						1


#define IN						0
#define OUT						1

#define APB_BUS	0
#define AHB_BUS	1

#define SET_BIT(x) |= 1<<x
#define CLR_BIT(X) &= ~ (1<<X)
#define GET_BIT(reg,bit) ( ( reg & (1 << bit) )?1:0 )



/******************************************************************************************************************
*																					Driver and other Dependencies																						*
*																																																									*
******************************************************************************************************************/
#include "GPIO_PINS.h"

#include "TM4C123xxGPIO_DRIVER.h"
#include "TM4C123xxSSI_DRIVER.h"
#include "TM4C123xxI2C_DRIVER.h"
#include "TM4C123xxUART_DRIVER.h"

#endif
