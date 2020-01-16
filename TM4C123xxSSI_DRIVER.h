#ifndef TM4C123XXSSI_DRIVER_H
#define TM4C123XXSSI_DRIVER_H

#include "TM4C123xx.h"



/******************************************************************************************************************
*																								Bit Position Macros																								*
******************************************************************************************************************/
// Control Register 0  (SSICR0)
#define SSI_CR0_DSS							0							//	Data Size Select					Bit 0:3
#define SSI_CR0_FRF							4							//	Frame Format							Bit 4:5
#define SSI_CR0_SPO							6							//	Polarity									Bit 6
#define SSI_CR0_SPH							7							//	Phase											Bit 7
#define SSI_CR0_SCR							8							//	Serial Clock Rate					Bit 8:15

// Control Register 1  (SSICR1)
#define SSI_CR1_LBM							0							//	Loop Back Mode						Bit 0
#define SSI_CR1_SSE							1							//	Sync. Serial Port Enable	Bit 1
#define SSI_CR1_MSS							2							//	Master/Slave Select				Bit 2
#define SSI_CR1_EOT							4							//	End of Transmission				Bit 4

// Status Register	(SSISR)
#define SSI_SR_TFE							0							//	Transmit FIFO Empty
#define SSI_SR_TNF							1							//	Transmit FIFO Not Full
#define SSI_SR_RNE							2							//	Receive FIFO Not Empty
#define SSI_SR_RFF							3							//	Receive FIFO Full
#define SSI_SR_BSY							4							//	SSI Busy

// Interrupt Mask Register (SSIIM)
#define SSI_IM_ROR							0							//	Receive Overrun Interrupt Mask
#define SSI_IM_RT								1							//	Receive Timeout Interrupt Mask
#define SSI_IM_RX								2							//	Receive  Buffer Interrupt Mask
#define SSI_IM_TX								3							//	Transmit Buffer Interrupt Mask

// Raw Interrupt Status Register (SSIRIS)
#define SSI_RIS_ROR							0							//	Receive Overrun Interrupt Status
#define SSI_RIS_RT							1							//	Receive Timeout Interrupt Status
#define SSI_RIS_RX							2							//	Receive  Buffer Interrupt Status
#define SSI_RIS_TX							3							//	Transmit Buffer Interrupt Status

// Masked Interrupt Status Register (SSIMIS)
#define SSI_MIS_ROR							0							//	Receive Overrun Interrupt Status
#define SSI_MIS_RT							1							//	Receive Timeout Interrupt Status
#define SSI_MIS_RX							2							//	Receive  Buffer Interrupt Status
#define SSI_MIS_TX							3							//	Transmit Buffer Interrupt Status

// Interrupt Clear Register (SSIICR)
#define SSI_ICR_RORIC						0							//	Receive Overrun Interrupt Clear
#define SSI_ICR_RTIC						1							//	Receive Timeout Interrupt Clear

// NVIC Enable Register
#define NVIC_EN0_SSI0						7
#define NVIC_EN1_SSI1						2
#define NVIC_EN1_SSI2						25
#define NVIC_EN1_SSI3						26



/******************************************************************************************************************
*																			Miscellaneous macros and shorthands																					*
******************************************************************************************************************/
//	SSI Slave Select Pins
#define SSI0_SS_PIN							PA3
#define SSI1_SS_PIN							PF3
#define SSI2_SS_PIN							PB5
#define SSI3_SS_PIN							PD1

//	SSI Device Mode
#define SSI_Master_Mode					1
#define SSI_Slave_Mode_OutEn		2
#define SSI_Slave_Mode_OutDis		3

//	SSI Clock Source
#define SSI_Clk_SystemClock			1
#define SSI_Clk_PIOSC						2

//	SSI Frame Format
#define SSI_FreescaleFormat			0
#define SSI_TiFormat						1
#define SSI_uWireFormat					2

//	SSI Data Size
#define SSI_Data_4bit						0x3
#define SSI_Data_5bit						0x4
#define SSI_Data_6bit						0x5
#define SSI_Data_7bit						0x6
#define SSI_Data_8bit						0x7
#define SSI_Data_9bit						0x8
#define SSI_Data_10bit					0x9
#define SSI_Data_11bit					0xA
#define SSI_Data_12bit					0xB
#define SSI_Data_13bit					0xC
#define SSI_Data_14bit					0xD
#define SSI_Data_15bit					0xE
#define SSI_Data_16bit					0xF

// @InterruptsNeedToBeEnabled
#define SSI_NoInterrupts				0
#define SSI_InterruptRxOverrun	1
#define SSI_InterruptRxTimeout	2
#define SSI_InterruptRxFIFO			3
#define SSI_InterruptTxFIFO			4
#define SSI_InterruptTxRxBoth		5



/******************************************************************************************************************
*																					APIs Supported by this Driver																						*
*		Below are the prototypes for driver APIs																																			*
*		Definitions for these can be found in TM4C123xxSSI_DRIVER.c file																							*
******************************************************************************************************************/
void SSIInit(uint8_t SSIx, uint8_t DeviceMode, uint8_t ClockSource, uint8_t ClockPrescalar, uint8_t SerialClockRate, uint8_t Phase, uint8_t Polarity, uint8_t FrameFormat, uint8_t DataSize);
void SSIDeInit(uint8_t SSIx);
void SSIClockControl(uint8_t SSIx,uint8_t	EnorDi);

void SSIStart(uint8_t SSIx, uint8_t DeviceMode, uint8_t InterruptMode);
void SSIStartK(uint8_t SSIx, uint8_t DeviceMode);

ssi_reg* GetSSIAddressOf(uint8_t SSIx);

void SSISendData(uint8_t SSIx, uint16_t* DataBuf, uint8_t Len);
void SSIRecvData(uint8_t SSIx, uint16_t* DataBuf, uint8_t Len);

void SSISendWithIntr(uint8_t SSIx, uint16_t* DataBuf, uint8_t Len);
void SSIRecvWithIntr(uint8_t SSIx, uint16_t* DataBuf, uint8_t Len);

void SSIIntrSend(uint8_t SSIx, uint8_t SS_pin);
void SSIIntrReceive(uint8_t SSIx, uint8_t SS_pin);

extern uint16_t* SSIIntrTxBuf[4];
extern uint16_t* SSIIntrRxBuf[4];

extern uint8_t SSIIntrTxCount[4];
extern uint8_t SSIIntrRxCount[4];

//extern uint8_t SSIIntrMaskPosition[4];

#endif
