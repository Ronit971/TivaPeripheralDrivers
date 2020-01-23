#ifndef TM4C123XXI2C_DRIVER_H
#define TM4C123XXI2C_DRIVER_H

#include "TM4C123xx.h"

/******************************************************************************************************************
*																								Bit Position Macros																								*
******************************************************************************************************************/

// Master Control/Status Register (I2CMCSR)
	/*	Read-Only Status Bits */
#define I2C_MCS_BUSY				0							//	I2C Controller is Busy
#define I2C_MCS_ERROR				1							//	Error in last operation
#define I2C_MCS_ADRACK			2							//	Address Acknowledge
#define I2C_MCS_DATAACK			3							//	Data Acknowledge
#define I2C_MCS_ARBLST			4							//	Arbitration Lost
#define I2C_MCS_IDLE				5							//	I2C Controller is Idle
#define I2C_MCS_BUSBUSY			6							//	Bus Busy
#define I2C_MCS_CLKTO				7							//	Clock Timeout Error

/* Write-Only Control Bits */
#define I2C_MCS_RUN					0							//	Master Enable
#define I2C_MCS_START				1							//	Generate START/Repeated START
#define I2C_MCS_STOP				2							//	Generate STOP
#define I2C_MCS_ACK					3							//	Data Auto-ACK Enable
#define I2C_MCS_HS					4							//	High Speed Enable

// Master Timer Period (I2CMTPR)
#define I2C_MTPR_TPR				0							//	Timer Period
#define I2C_MTPR_HSE				7							//	High Speed Enable

// Master Interrupt Mask Register (I2CMIMR)
#define I2C_MIM_IM					0							//	Master Interrupt Mask
#define I2C_MIM_CLKIM				1							//	Clock Timeout Interrupt Mask

// Master Raw Interrupt Status (I2CMRIS)
#define I2C_MRIS_RIS				0							//	Master Interrupt Status (Unmasked)
#define I2C_MRIS_CLKRIS			1							//	Clock Timeout Interrupt Status (Unmasked)

// Master Masked Interrupt Status (I2CMMIS)
#define I2C_MMIS_MIS				0							//	Master Interrupt Status (Masked)
#define I2C_MMIS_CLKMIS			1							//	Clock Timeout Interrupt Status (Masked)

// Master Interrupt Clear (I2CMIC)
#define I2C_MIC_IC					0							//	Master Interrupt Clear
#define I2C_MIC_CLKIC				1							//	Clock Timeout Interrupt Clear

// Master Configuration (I2CMCR)
#define I2C_MCR_LPBK				0							//	Loopback
#define I2C_MCR_MFE					4							//	Master Function Enable
#define I2C_MCR_SFE					5							//	Slave  Function Enable
#define I2C_MCR_GFE					6							//	Glitch Filter Enable

// Master Bus Monitor (I2CMBMON)
#define I2C_MBMON_SCL				0							//	SCL Line
#define I2C_MBMON_SDA				1							//	SDA Line

// Master Configuration 2 (I2CMCR2)
#define I2C_MCR2_GFPW 			4							//	Glitch Filter Pulse Width

// Slave Control/Status Register	(I2CSCSR)
#define I2C_SCSR_RREQ				0							//	Receive Request
#define I2C_SCSR_TREQ				1							//	Transmit Request
#define I2C_SCSR_FBR				2							//	First Byte Received
#define I2C_SCSR_OAR2SEL		3							//	OAR2 Address Matched

// Slave Interrupt Mask Register	(I2CSIMR)
#define I2C_SIMR_DATA				0							//	Data Received / Data Requested Interrupt Mask
#define I2C_SIMR_START			1							//	"START Condition" Interrupt Mask
#define I2C_SIMR_STOP				2							//	"STOP Condition" Interrupt Mask

// Slave Raw Interrupt Status			(I2CSRIS)
#define I2C_SRIS_DATA				0							//	Data Received / Data Requested Interrupt Status (Unmasked)
#define I2C_SRIS_START			1							//	"START Condition" Interrupt Status (Unmasked)
#define I2C_SRIS_STOP				2							//	"STOP Condition" Interrupt Status (Unmasked)

// Slave Masked Interrupt Status	(I2CSMIS)
#define I2C_SMIS_DATA				0							//	Data Received / Data Requested Interrupt Status (Masked)
#define I2C_SMIS_START			1							//	"START Condition" Interrupt Status (Masked)
#define I2C_SMIS_STOP				2							//	"STOP Condition" Interrupt Status (Masked)

// Slave Interrupt Clear Register (I2CSICR)
#define I2C_SICR_DATA				0							//	Data Received / Data Requested Interrupt Clear
#define I2C_SICR_START			1							//	"START Condition" Interrupt Clear
#define I2C_SICR_STOP				2							//	"STOP Condition" Interrupt Clear


// Slave Own Address Register 2 (I2CSOAR2)
#define I2C_SOAR2_ADDR			0							//	Slave Own Address 2
#define I2C_SOAR2_EN				7							//	Slave Own Address 2 Enable

// Slave Acknowledge Control (I2CSACKCTL)
#define I2C_SACKCTL_OEN			0							//	Slave ACK Override Enable
#define I2C_SACKCTL_OVAL		1							//	Slave ACK Override Value

// Peripheral Properties (I2CPP)
#define I2C_PP_HSC					0							//	High Speed Capable

// Peripheral Configuration (I2CPC)
#define I2C_PC_HSE					0							//	High Speed Enable



/******************************************************************************************************************
*																			Miscellaneous macros and shorthands																					*
******************************************************************************************************************/

#define I2C_SPEED_MODE_STD			0
#define I2C_SPEED_MODE_FM				1
#define I2C_SPEED_MODE_FMP			2
#define I2C_SPEED_MODE_HS				3

#define I2C_AUTO_ACK_DISABLE		0
#define I2C_AUTO_ACK_ENABLE			1

#define I2C0_SCL_PIN						PB2
#define I2C0_SDA_PIN						PB3

#define I2C1_SCL_PIN						PA6
#define I2C1_SDA_PIN						PA7

#define I2C2_SCL_PIN						PE4
#define I2C2_SDA_PIN						PE5

#define I2C3_SCL_PIN						PD0
#define I2C3_SDA_PIN						PD1



/******************************************************************************************************************
*																								I2C Handle Structure																							*
* >> provide description of all parameters here
******************************************************************************************************************/
typedef struct
{
	I2C_reg* pI2Cx;
	uint8_t I2Cx;
	uint8_t SpeedMode;
	uint32_t ClkSpeed;
	uint8_t ACKControl;
	uint8_t MasterAddress;
	uint8_t UseAsSlave;

}I2CHandle;

/******************************************************************************************************************
*																					APIs Supported by this Driver																						*
*		Below are the prototypes for driver APIs																																			*
*		Definitions for these can be found in TM4C123xxI2C_DRIVER.c file																							*
******************************************************************************************************************/
void I2CInit(uint8_t I2Cx, uint8_t SpeedMode, uint32_t ClkSpeed, uint8_t ACKControl);
void I2CInit2(I2CHandle* pI2CHandle);
void I2CDeInit(uint8_t I2Cx);

uint8_t I2CClockControl(uint8_t I2Cx,uint8_t	EnorDi);

uint8_t I2CMasterSendData(I2CHandle* pI2CHandle, uint8_t SlaveAddress, uint8_t* TxBuf, uint8_t Len);
uint8_t I2CMasterSendData2(uint8_t I2Cx, uint8_t SlaveAddress, uint8_t* TxBuf, uint8_t Len);
uint8_t I2CMasterSendByte(uint8_t I2Cx, uint8_t SlaveAddress, uint8_t Data);

uint8_t GetSCLPin(uint8_t I2Cx);
uint8_t GetSDAPin(uint8_t I2Cx);

I2C_reg* I2CGetAddress(uint8_t I2Cx);

#endif
