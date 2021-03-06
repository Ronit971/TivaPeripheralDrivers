/******************************************************************************************************************
*	@file			-	TM4C123xxSSI_DRIVER.c																																								*
*	@author		-	Ronit Vairagi																																												*
*																																																									*
*	This file contains definitions of SSI Driver APIs.																															*
*																																																									*
* @Note			-	All of the code present in the this file applies to TM4C123GH6PM microcontroller.										*
*																																																									*
*	@Note2		- Feel free to use, modify, and/or re-distribute this code at your will.															*
******************************************************************************************************************/

#include "TM4C123xxSSI_DRIVER.h"
#include <math.h>


__vo uint16_t* SSIIntrTxBuf[4] = {NULL,NULL,NULL,NULL};
__vo uint16_t* SSIIntrRxBuf[4] = {NULL,NULL,NULL,NULL};

__vo uint8_t SSIIntrTxCount[4] = {0,0,0,0};
__vo uint8_t SSIIntrRxCount[4] = {0,0,0,0};




/******************************************************************************************************************
*																				Pins Available for SSI functions																					*
*																																																									*
*		 SSIx				CLK				SS				Rx				Tx		Comments																											*
*																																																									*
*			0					PA2				PA3				PA4				PA5																																	*
*			1					PF2				PF3				PF0				PF1																																	*
*			1					PD0				PD1				PD2				PD3		(These pins aren't used for SSI1 in this driver)							*
*			2					PB4				PB5				PB6				PB7																																	*
*			3					PD0				PD1				PD2				PD3																																	*
******************************************************************************************************************/



/******************************************************************************************************************
*																					APIs Supported by this Driver																						*
*	Below are the prototypes for driver APIs																																				*
*	1. SSIClockControl()		-	Enable/Disable clock for an SSI Module.																								*
*	2. SSIInit()						-	Initialize and SSI Module.																														*
*	3. SSIDeInit()					-	Reset and turn off an SSI Module.																											*
*																																																									*
*	4. SPIStart()						-	Initialize an SSI Module for FREESCALE SPI format, with some default configurations.	*
*																																																									*
*	5. SSISendData()				-	Send data over an SSI Module.																													*
*	6. SSISend()						-	Send one packet(16-bit) of data over an SSI Module.																		*
*																																																									*
*	7.	SSIRecvData()				-	Receive data over an SSI Module.																											*
*	8.	SSIRecv()						-	Receive one packet(16-bit) of data over an SSI Module.																*
*																																																									*
*	9.	SSISendWithIntr()		-	Send Data without blocking the CPU by using interrupts.																*
*	10. SSIRecvWithIntr()		-	Receive Data without blocking the CPU by using interrupts.														*
*																																																									*
*	11. SSIIntrSend()				-	Helper for SSI Interrupt Handler function.																						*
*	12. SSIIntrRecv()				-	Helper for SSI Interrupt Handler function.																						*
*																																																									*
*	13. SSIGetAddress()			-	Get the access pointer for a given SSI Module.																				*
*	14.	WaitWhileSSIControllerIsBusy() - Pause program execution till the SSI controller is busy in transmission.		*
*		Definitions for these can be found in TM4C123xxSSI_DRIVER.c file																							*
******************************************************************************************************************/



/******************************************************************************************************************
*	@SSIClockControl()																																															*
* @brief			-	This function is used to enable or disable clock for a particular SSI module.											*
*	@SSIx				- Name of the SSI module for which clock needs to be enabled or disabled.														*
*	@EnOrDi			- This variable speifies whether we have to enable or disable the clock.														*
*								Use (I) ENABLE or (II) DISABLE macros for this variable.																					*
******************************************************************************************************************/
void SSIClockControl(uint8_t SSIx, uint8_t	EnOrDi)
{
	if(EnOrDi == ENABLE)
		switch(SSIx)
		{
			case SSI0:	SSI0_PCLK_EN();		break;		//	These macros are defined in section 3.2 in TM4C123xx.h file
			case SSI1:	SSI1_PCLK_EN();		break;
			case SSI2:	SSI2_PCLK_EN();		break;
			case SSI3:	SSI3_PCLK_EN();		break;
		}
	else
		switch(SSIx)
		{
			case SSI0: SSI0_PCLK_DIS();		break;		//	These macros are defined in section 3.2 in TM4C123xx.h file
			case SSI1: SSI1_PCLK_DIS();		break;
			case SSI2: SSI2_PCLK_DIS();		break;
			case SSI3: SSI3_PCLK_DIS();		break;
		}
}



/******************************************************************************************************************
*	@SSIInit()																																																			*
*	@brief						-	This function Initializes an SSI module.																										*
* @SSIx							-	This is the name of the SSI module which needs to be initialized.														*
*	@DeviceMode				-	Used to specify Master or Slave mode.																												*
* @ClockSource			-	Used to select the clock source for the SSI module.																					*
*	@ClockPrescalar		-	Even number by which the clock is divided i.e. prescaled.																		*
*	@SerialClkRate		-	SCR is used to configure the SSI clock frequency.																						*
*	@Phase						-	0 => Data capture on first clk edge,	1=> Data capture on second clk edge										*
*	@Polarity					-	0 => Steady Low SSI Clk,	1 => Steady High SSI Clk																					*
*											Phase and Polarity jointly determine the instant at which data is captured.									*
*	@FrameFormat			-	Format of data transfer (Freescale SPI, MICROWIRE, TI SSI Format).													*
*	@DataSize					-	Size of data frame in bits.																																	*
*																																																									*
*	@Note							-	See Pg No. 956 (Section 15.4) for detailed steps on Initialization and Configuration.				*
******************************************************************************************************************/
void SSIInit(uint8_t SSIx, uint8_t DeviceMode, uint8_t ClockSource, uint8_t ClockPrescalar, uint8_t SerialClkRate, uint8_t Phase, uint8_t Polarity, uint8_t FrameFormat, uint8_t DataSize)
{
	ssi_reg*	pSSI;								// Pointer to the SSI Module which needs to be initialized.
	GPIO_reg* pGPIO;							// Pointer to the GPIO port which has pins for the given SSI Module.
	uint8_t ssi_pins = 0x00;			// Variable to hold '1' for corresponding SSI pins on a GPIO port.
	
	SSIClockControl(SSIx, ENABLE);																//	Step 1 of Section 15.4: Enable Clock for the SSI Module.
	
	switch(SSIx)
	{
		case SSI0:	// Configure pins for SSI0 (Alternate Function # 2)
		
								pGPIO = GPIO_A_P;																//	GPIO_A has the pins for SSI0
								ssi_pins = 0x3C;																//	PA2,3,4,5 are used for SSI0
		
								GPIO_ClockControl(GPIO_PORT_A, ENABLE);					//	Step 2 of Section 15.4
								pGPIO->GPIO_AFSEL |= ssi_pins;									//	Step 3 of Section 15.4
								pGPIO->GPIO_PCTL &= 0xFF0000FF;									//	Step 4 of Section 15.4
								pGPIO->GPIO_PCTL |= 0x00222200;
		
								pSSI = pSSI0;							//	Pointer to SSI0
								break;
		
		//-------------------------------------------------------------------------------------------------------------
		case SSI1:	// Configure pins for SSI1 (Alternate Function # 2)
		
								pGPIO = GPIO_F_P;																//	GPIO_F has the pins for SSI1
								ssi_pins = 0x0F;																//	PF0,1,2,3 are used for SSI2
		
								GPIO_ClockControl(GPIO_PORT_F, ENABLE);					//	Step 2 of Section 15.4
								pGPIO->GPIO_AFSEL |= ssi_pins;									//	Step 3 of Section 15.4
								pGPIO->GPIO_PCTL &= 0xFFFF0000;									//	Step 4 of Section 15.4
								pGPIO->GPIO_PCTL |= 0x00002222;
		
								pSSI = pSSI1;							//	Pointer to SSI1
								break;
		
		//-------------------------------------------------------------------------------------------------------------
		case SSI2:	// Configure pins for SSI2 (Alternate Function # 2)
		
								pGPIO = GPIO_B_P;																//	GPIO_B has the pins for SSI2
								ssi_pins = 0xF0;																//	PB4,5,6,7 are used for SSI2
		
								GPIO_ClockControl(GPIO_PORT_B, ENABLE);					//	Step 2 of Section 15.4
								pGPIO->GPIO_AFSEL |= ssi_pins;									//	Step 3 of Section 15.4
								pGPIO->GPIO_PCTL &= 0x0000FFFF;									//	Step 4 of Section 15.4
								pGPIO->GPIO_PCTL |= 0x22220000;
		
								pSSI = pSSI2;							//	Pointer to SSI2
								break;
		
		//-------------------------------------------------------------------------------------------------------------
		case SSI3:	// Configure pins for SSI3 (Alternate Function # 1)
		
								pGPIO = GPIO_D_P;																//	GPIO_D has the pins for SSI3
								ssi_pins = 0x0F;																//	PD0,1,2,3 are used for SSI3
		
								GPIO_ClockControl(GPIO_PORT_D, ENABLE);					//	Step 2 of Section 15.4
								pGPIO->GPIO_AFSEL |= ssi_pins;									//	Step 3 of Section 15.4
								pGPIO->GPIO_PCTL &= 0xFFFF0000;									//	Step 4 of Section 15.4
								pGPIO->GPIO_PCTL |= 0x00001111;
		
								pSSI = pSSI3;							//	Pointer to SSI3
								break;
	}
	
	pGPIO->GPIO_DEN |= ssi_pins;																	//	Step 5... of Section 15.4
	pGPIO->GPIO_PUR |= ssi_pins;																	//	Step 5... of Section 15.4
	pGPIO->GPIO_DR8R |= ssi_pins;																	//	Step 5... of Section 15.4
	
	pSSI->SSI_CR[1] CLR_BIT( SSI_CR1_SSE );												//	Step ff.1 of Section 15.4
	
	switch(DeviceMode)																						//	Step ff.2 of Section 15.4
	{
		case SSI_Master_Mode:				pSSI->SSI_CR[1] = 0x00000000;				break;
		case SSI_Slave_Mode_OutEn:	pSSI->SSI_CR[1] = 0x00000004;				break;
		case SSI_Slave_Mode_OutDis:	pSSI->SSI_CR[1] = 0x0000000C;				break;
	}
	
	switch(ClockSource)																						//	Step ff.3 of Section 15.4
	{
		case SSI_Clk_SystemClock:		pSSI->SSI_CC &= 0xFFFFFFF0;		break;		//	System Clock
		case SSI_Clk_PIOSC:					pSSI->SSI_CC |= 0x00000005;		break;		//	Precision Internal Oscillator
		default:										return;
	}
	
	pSSI->SSI_CPSR |= (ClockPrescalar	<<	0);											//	Step ff.4 of Section 15.4
	
	pSSI->SSI_CR[0] |= ( SerialClkRate	<<	SSI_CR0_SCR);					//	Step ff.5.1 of Section 15.4
	pSSI->SSI_CR[0] |= ( Phase					<<	SSI_CR0_SPH);					//	Step ff.5.2 of Section 15.4
	pSSI->SSI_CR[0] |= ( Polarity				<<	SSI_CR0_SPO);					//	Step ff.5.2 of Section 15.4
	pSSI->SSI_CR[0] |= ( FrameFormat		<<	SSI_CR0_FRF);					//	Step ff.5.3 of Section 15.4
	pSSI->SSI_CR[0] |= ( DataSize				<<	SSI_CR0_DSS);					//	Step ff.5.4 of Section 15.4
	
	/* Step ff.6: DMA Configuration isn't implemented yet. It is optional, so we'll come back to it later, sometime.*/
	
	pSSI->SSI_CR[1] SET_BIT( SSI_CR1_SSE );												//	Step ff.7 of Section 15.4
}




/******************************************************************************************************************
*	@SSIDeInit()																																																		*
*	@brief				-	This function De-Initializes(Reset and Disable) an SSI module.																	*
* @SSIx					-	This is the name of the SSI module which needs to be de-initialized.														*
*																																																									*
*	@Note					- To reset a SSI module, the corresponding bit in the SRSSI register needs to be set. Clock to		*
*									the module is then disabled to save power, and prevent access to the module.										*
******************************************************************************************************************/
void SSIDeInit(uint8_t SSIx)
{
	SYSCTL->SRSSI |=	1<<(SSIx-6);						//	Reset the SSI Module by setting the appropriate bit in the SRSSI register.
	SYSCTL->SRSSI &=	~( 1<<(SSIx-6) );				//	Clear the bit so that the module doesn't always remain in the reset state.
	SSIClockControl(SSIx,DISABLE);						//	Disable clock to the module to save power.
}



/******************************************************************************************************************
* @SPIStart()																																																			*
* @brief											-	This function initializes an SSI module for FREESCALE SPI format with 2MHz Serial	*
*																Clock. Additionally, interrupt delivery from the SSI module to the interrupt			*
*																controller(NVIC) can be enabled or disabled as required.													*
* @SSIx												-	This is the name of the SSI module which needs to be initialized.									*
*	@DeviceMode									-	Used to specify Master or Slave mode.																							*
*	@InterruptsNeedToBeEnabled	- Specifies which interrupts should be enabled.																			*
*																																																									*
* @Note												- SSI configuration for this function:																							*
*																1. Clock Source			-	System Clock(16 MHz in our board)														*
*																2. Clock Prescalar	-	2																														*
*																3. Serial Clk Rate	-	3																														*
*																4. Phase						-	0																														*
*																5. Polarity					-	0																														*
*																6. Frame Format			-	Freescale SPI format																				*
*																7. Data Size				-	16-bit																											*
******************************************************************************************************************/
void SPIStart(uint8_t SSIx,uint8_t DeviceMode, uint8_t InterruptsNeedToBeEnabled)
{
	if(InterruptsNeedToBeEnabled)
	{
		ssi_reg* pSSI = SSIGetAddress(SSIx);
		SSIClockControl(SSIx,ENABLE);
		
		// Enable interrupt reception for the given SSI Module.
		switch(SSIx)
		{
			case	SSI0:			NVIC->EN[0] |= ( 1 << NVIC_EN0_SSI0 );		 	break;
			case	SSI1:			NVIC->EN[1] |= ( 1 << NVIC_EN1_SSI1 );		 	break;
			case	SSI2:			NVIC->EN[1] |= ( 1 << NVIC_EN1_SSI2 );		 	break;	
			case	SSI3:			NVIC->EN[1] |= ( 1 << NVIC_EN1_SSI3 );		 	break;
			default:				return;											//	Break out of the function in case of a mismatch.
		}
		
		/**************************************************************************************************************
		*	The Interrupt Mode macros (defined in the SSI driver header file) have integer values equal to their bit		*
		*	position in the Interrupt Mask register (SSIIM) plus 'one'. To enable an interrupt, corresponding mask 			*
		*	should be disabled by setting the bit in SSIIM register. To get the bit position, subtract one from the			*
		*	interrupt mode variable (InterruptsNeedToBeEnabled).																												*
		**************************************************************************************************************/
		if(InterruptsNeedToBeEnabled == SSI_InterruptTxRxBoth)
			pSSI->SSI_IM |= 0x0000000C;
		else
		{
			uint8_t IntrMaskPosition = ( InterruptsNeedToBeEnabled - 1 );
			pSSI->SSI_IM SET_BIT( IntrMaskPosition );													//	Enable the requested interrupt.
		}
	}
	
	//SSIInit(SSIx, DeviceMode, ClockSource, ClockPrescalar, SerialClockRate, Phase, Polarity, FrameFormat, DataSize)
	SSIInit(SSIx, DeviceMode, SSI_Clk_SystemClock, 2, 3, 0, 0, SSI_FreescaleFormat, SSI_Data_16bit);
}



/******************************************************************************************************************
*	@SSISendData()																																																	*
*	@brief				-	This function is used to transmit/send data over an SSI channel.																*
* @SSIx					-	This is the name of the SSI module over which, data has to be sent.															*
*	@DataBuf			-	Pointer to the data that has to be transmitted.																									*
*	@Len					-	Length of Data (in bits) which needs to be sent.																								*
*																																																									*
*	@Note					-	This function does not care if the SSI module is properly initialized or not. Make sure that		*
*									the SSI module is already configured as needed otherwise data transmission might not occur.			*
*									Also, it might generate bus faults if the clock is disabled.																		*
*	@Note2				-	In case of incorrect data length, the function does not proceed further and breaks out.					*
******************************************************************************************************************/
void SSISendData(uint8_t SSIx, uint16_t* DataBuf, uint8_t Len)
{
	ssi_reg* pSSI = SSIGetAddress(SSIx);

	if(Len <= 0)	return;											//	Break out of the function in case of incorrect length.
	else
	{
		uint8_t n = ceil( Len/16.0 );						//	Tx count (no of 16 bit data packets that are to be sent)
		do
		{
			WaitWhileSSIControllerIsBusy(pSSI);
			
			pSSI->SSI_DR = (*DataBuf)<<0;					//	Insert data into the Tx buffer by writing it to SSIDR register.
			
			DataBuf++;														//	Step the pointer to the next data set.
			n--;																	//	Decrease the Tx count.
		}while(n>0);														//	Do this until the Tx count becomes zero.
	}
}
/******************************************************************************************************************
*	@SSISend()																																																			*
*	@brief				-	This function is used to transmit a single packet(16-bit) over an SSI channel.									*
* @SSIx					-	This is the name of the SSI module over which, data has to be sent.															*
*	@Data					-	Data that needs to be transmitted.																															*
*																																																									*
*	@Note					-	This function does not care if the SSI module is properly initialized or not. Make sure that		*
*									the SSI module is already configured as needed otherwise data transmission might not occur.			*
*									Also, it might generate bus faults if the clock is disabled.																		*
******************************************************************************************************************/
void SSISend(uint8_t SSIx, uint16_t Data)
{
	ssi_reg* pSSI = SSIGetAddress(SSIx);

	WaitWhileSSIControllerIsBusy(pSSI);
			
	pSSI->SSI_DR = Data<<0;										//	Insert data into the Tx buffer by writing it to SSIDR register.
}



/******************************************************************************************************************
*	@SSIRecvData()																																																	*
*	@brief				-	This function is used to recevie data over an SSI channel.																			*
* @SSIx					-	This is the name of the SSI module from which, data has to be received.													*
*	@DataBuf			-	Pointer to data buffer which will be used to hold the received data.														*
*	@Len					-	Length of Data (in bits) which needs to be received.																						*
*																																																									*
*	@Note					-	This function does not care if the SSI module is properly initialized or not. Make sure that		*
*									the SSI module is already configured as needed otherwise no data will be received.							*
*									Also, it might generate bus faults if the clock is disabled.																		*
*	@Note2				-	In case of incorrect data length, the function does not proceed further and breaks out.					*
******************************************************************************************************************/
void SSIRecvData(uint8_t SSIx, uint16_t* DataBuf, uint8_t Len)
{
	ssi_reg* pSSI = SSIGetAddress(SSIx);
	
	if(Len <= 0)	return;											//	Break out of the function in case of incorrect data length
	else
	{
		
		uint8_t n = ceil( Len/16.0 );						// Rx count (no of 16 bit data packets that are to be received)
		do
		{
			WaitWhileSSIControllerIsBusy(pSSI);
			
			*DataBuf = (uint16_t)pSSI->SSI_DR;
			/************************************************************************************************************
			*	Pick data from SSIDR register, and put it into the Rx buffer. NOTE: SSI_DR register is 32-bit register,		*
			*	but Rx shift register is of 16-bits. Rest of the 16 bits in the SSI_DR register are reserved. Data, of		*
			*	our concern, lies in the first 16-bits. So we convert the value in the SSI_DR register to uint16_t. This	*
			*	discards the higher 16 bits, and stores the remaining bits in the data variable, pointed by DataBuf.			*
			************************************************************************************************************/
			
			DataBuf++;														//	Step the pointer for the next data set.
			n--;																	//	Decrease the Rx-count.
		}while(n>0);														//	Do this until the Rx-count becomes zero.
	}
}



/******************************************************************************************************************
*	@SSIRecv()																																																			*
*	@brief				-	This function is used to receive a single packet(16-bit) over an SSI channel.										*
* @SSIx					-	This is the name of the SSI module over which, data should be received.													*
*	@DataBuf			-	Pointer to the variable where received data should be stored.																		*
*																																																									*
*	@Note					-	This function does not care if the SSI module is properly initialized or not. Make sure that		*
*									the SSI module is already configured as needed otherwise data might not be received.						*
*									Also, it might generate bus faults if the clock is disabled.																		*
******************************************************************************************************************/
void SSIRecv(uint8_t SSIx, uint16_t* DataBuf)
{
	ssi_reg* pSSI = SSIGetAddress(SSIx);
	WaitWhileSSIControllerIsBusy(pSSI);
	
	*DataBuf = (uint16_t)pSSI->SSI_DR;
	/****************************************************************************************************************
	*	Pick data from SSIDR register, and put it into the Rx buffer. NOTE: SSI_DR register is 32-bit register, but		*
	*	Rx shift register is of 16-bits. Rest 16 bits in the SSI_DR register are reserved. Data, of our concern, lies	*
	*	in the first 16-bits. So we convert the value in the SSI_DR register to uint16_t. This discards the higher		*
	*	16 bits, and stores the remaining bits in the data variable, pointed by DataBuf.															*
	****************************************************************************************************************/
}



/******************************************************************************************************************
* @SSISendWithIntr()																																															*
* @brief				-	This function sends data over an SSI module without blocking the CPU.														*
* @SSIx					-	This is the name of the SSI module over which, data has to be sent.															*
*	@DataBuf			-	Data buffer, which points to the data that has to be transmitted.																*
*	@Len					-	Data Size, or the length of Data bits which need to be sent.																		*
* @return				-	None.																																														*
******************************************************************************************************************/
void SSISendWithIntr(uint8_t SSIx, uint16_t* DataBuf, uint8_t Len)
{
	ssi_reg* pSSI = SSIGetAddress(SSIx);
	
	pSSI->SSI_CR[1] CLR_BIT( SSI_CR1_SSE );						//	Disable SSI operation.
	pSSI->SSI_IM 		SET_BIT( SSI_IM_TX );
	pSSI->SSI_CR[1] SET_BIT( SSI_CR1_SSE );						//	Re-Enable SSI operation.

	SSIIntrTxBuf[SSIx-6] = DataBuf;									//	Save the data pointer to the appropriate buffer variable.
	SSIIntrTxCount[SSIx-6] = ceil( Len/16.0 );			//	Tx count (no of 16-bit data packets that are to be sent)
}



/******************************************************************************************************************
* @SSIRecvWithIntr()																																															*
* @brief				-	This function receives data from an SSI module without blocking the CPU.												*
* @SSIx					-	This is the name of the SSI module from which, data has to be received.													*
*	@DataBuf			-	Pointer to data buffer which will be used to hold the received data.														*
*	@Len					-	Length of Data (in bits) which need to be received.																							*
* @return				-	None.																																														*
******************************************************************************************************************/
void SSIRecvWithIntr(uint8_t SSIx, __vo uint16_t *DataBuf, uint8_t Len)
{
	ssi_reg* pSSI = SSIGetAddress(SSIx);
	
	pSSI->SSI_CR[1] CLR_BIT( SSI_CR1_SSE );						//	Disable SSI operation.
	pSSI->SSI_IM 		SET_BIT( SSI_IM_RX );
	pSSI->SSI_CR[1] SET_BIT( SSI_CR1_SSE );						//	Re-Enable SSI operation.
	
	SSIIntrRxBuf[SSIx-6] = DataBuf;									//	Save the data pointer to the appropriate buffer variable.
	SSIIntrRxCount[SSIx-6] = ceil( Len/16.0 );			//	Rx count (no of 16-bit data packets that are to be sent)
}



/******************************************************************************************************************
* @SSIIntrSend()																																																	*
* @brief				-	Function to send data over an SSI Module. It needs to be called from Interrupt Handler.					*
* @SSIx					-	This is the name of the SSI module over which, data needs to be sent.														*
* @return				-	None.																																														*
******************************************************************************************************************/
void SSIIntrSend(uint8_t SSIx)
{
	uint8_t SSI = SSIx - 6;													//	Index of SSI Module
	ssi_reg* pSSI = SSIGetAddress(SSIx);						//	Pointer to the SSI Module
	
	if(SSIIntrTxCount[SSI] > 0)											//	If the transmission is not complete...
	{
			uint16_t currentData = *SSIIntrTxBuf[SSI];	//	Fetch data from the data buffer
			pSSI->SSI_DR = currentData<<0;							//	Insert data into the Tx buffer by writing it to SSIDR register.

			SSIIntrTxBuf[SSI]++;												//	Step the pointer to the next data set.
			SSIIntrTxCount[SSI]--;											//	Decrease the Tx count.
	}
	if( SSIIntrTxCount[SSI] == 0 )
		pSSI->SSI_IM CLR_BIT( SSI_IM_TX );						//	Disable interrupt reception once the transmission is over.
}



/******************************************************************************************************************
* @SSIIntrRecv()																																																	*
* @brief				-	Function to receive data over an SSI Module. It needs to be called from Interrupt Handler.			*
* @SSIx					-	This is the name of the SSI module from which, data has to be received.													*
* @return				-	None.																																														*
******************************************************************************************************************/
void SSIIntrRecv(uint8_t SSIx)
{
	ssi_reg* pSSI = SSIGetAddress(SSIx);						//	Pointer to the SSI Module
	uint8_t SSI = SSIx - 6;													//	Index of SSI Module
	
	if(SSIIntrTxCount[SSI] > 0)											//	If the transmission is not complete...
	{
		*SSIIntrRxBuf[SSI] = (uint16_t)pSSI->SSI_DR;	//	Pick Data from SSIDR Register and store in the Rx Buffer.

		SSIIntrRxBuf[SSI]++;													//	Step the pointer to the next data set.
		SSIIntrRxCount[SSI]--;												//	Decrease the Rx count.
	}
	if(SSIIntrTxCount[SSI] == 0)
		pSSI->SSI_IM CLR_BIT( SSI_IM_RX );						//	Disable interrupt reception once the transmission is over.
}



/******************************************************************************************************************
* @SSIGetAddress()																																																*
* @brief		-	This function returns the address of SSI module.																										*
* @SSIx			-	This is the name of the SSI module whose address is required.																				*
* @return		-	Pointer to an SSI Module's peripheral register.																											*
******************************************************************************************************************/
ssi_reg* SSIGetAddress(uint8_t SSIx)
{
	switch(SSIx)
	{
		case SSI0:	return pSSI0;
		case SSI1:	return pSSI1;
		case SSI2:	return pSSI2;
		case SSI3:	return pSSI3;
		default:		return NULL;
	}
}



/******************************************************************************************************************
*	@WaitWhileSSIControllerIsBusy()																																									*
* @brief				-	This function pauses program execution while the SSI controller is busy in transmission by			*
*									continuously polling the busy bit of the ssi status register in a loop.													*
* @pSSI					-	Wait for this SSI Module.																																				*
*	@return				-	Nothing (void).																																									*
******************************************************************************************************************/
void WaitWhileSSIControllerIsBusy( ssi_reg* pSSI)
{
	uint8_t Busy;
	do
	{
		Busy = GET_BIT( pSSI->SSI_SR, SSI_SR_BSY );			//	Check the busy bit in the status register.
	}while( Busy );																		//	Wait if the bit is '1'.
}
