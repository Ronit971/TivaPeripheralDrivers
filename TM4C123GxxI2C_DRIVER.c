#include"TM4C123GxxI2C_DRIVER.h"

/******************************************************************************************************************
*																					Pins Available for I2C Functions																				*
*		Module				SCL					SDA																																									*
*		I2C 0					PB2					PB3																																									*
*		I2C 1					PA6					PA7																																									*
*		I2C 2					PE4					PE5																																									*
*		I2C 3					PD0					PD1																																									*
******************************************************************************************************************/



/******************************************************************************************************************
*																					APIs Supported by this Driver																						*
*																																																									*
*	I2CClockControl()		-	Enable or Disable clock for an I2C Module.																								*
*	I2CInit()						-	Initialize an I2C Module.																																	*
*	I2CDeInit()					-	Reset and turn off an I2C Module.																													*
*	I2CGetAddress()			-	Get address of an I2C Module.																															*
******************************************************************************************************************/



/******************************************************************************************************************
* @I2CClockControl()																																															*
* @brief	-	Enable or Disable clock for an I2C Module.																														*
* @I2Cx		-	Name of the I2C module.																																								*
*	@EnorDi	-	Specifies whether the clock need to be enabled or disabled.																						*
* @return	-	None.																																																	*
*																																																									*
* @Note		-	If an invalid I2C module name is given to this function, no module will be affected. Access to the		*
*						intended module may generate a bus fault in this case.																								*
******************************************************************************************************************/
uint8_t I2CClockControl(uint8_t I2Cx,uint8_t	EnorDi)
{
	if(EnorDi == ENABLE)
	{
		switch(I2Cx)
		{
			case I2C0:		I2C0_PCLK_EN();				break;
			case I2C1:		I2C1_PCLK_EN();				break;
			case I2C2:		I2C2_PCLK_EN();				break;
			case I2C3:		I2C3_PCLK_EN();				break;
			default:			return 1;							//	Return 1 in case of a mismatch.
		}
	}
	else
	{
		switch(I2Cx)
		{
			case I2C0:		I2C0_PCLK_DIS();				break;
			case I2C1:		I2C1_PCLK_DIS();				break;
			case I2C2:		I2C2_PCLK_DIS();				break;
			case I2C3:		I2C3_PCLK_DIS();				break;
			default:			return 1;							//	Return 1 in case of a mismatch.
		}
	}
	
	return 0;		//	Return 0 in case of successful execution of this function.
}



/******************************************************************************************************************
* @I2CInit()																																																			*
* @brief				-	Initialize an I2C Module.																																				*
* @I2Cx					-	Name of the I2C module.																																					*
*	@SpeedMode		-	Speed mode : Standard, Fast Mode, Fast Mode+, High Speed Mode																		*
*	@ACKControl		-	Enable or Disable Auto Acknowledge mode.																												*
* @return				-	None.																																														*
*																																																									*
* @Note		-	If an invalid I2C module name is given to this function, no module will be affected. Access to the		*
*						intended module, at a later stage in the code may generate a bus fault in this case.									*
******************************************************************************************************************/
//void I2CInit(uint8_t I2Cx, uint8_t SpeedMode, uint8_t ClkSpeed, uint8_t ACKControl)
//{
//	uint8_t Error = I2CClockControl(I2Cx, ENABLE);						//	Enable clock to the module and get error code.
//	
//	if(Error)		return;																				//	Break out of the function in case of an error.
//	
//	I2C_reg* pI2Cx = I2CGetAddress(I2Cx);
//	
//	uint8_t I2C_SCL_PIN = GetSCLPin(I2Cx);
//	uint8_t I2C_SDA_PIN = GetSDAPin(I2Cx);
//	
//	uint8_t I2C_SCL_PIN_NUM = getPinNumber(I2C_SCL_PIN);
//	uint8_t I2C_SDA_PIN_NUM = getPinNumber(I2C_SDA_PIN);
//	
//	GPIO_reg* pGPIO = getPortAddr(I2C_SCL_PIN, APB_BUS);
//	
//	
//	GPIO_ClockControl(getPortName(I2C_SCL_PIN), ENABLE);			//	Step 2 of section 16.4
//	
//	pGPIO->GPIO_AFSEL SET_BIT( I2C_SCL_PIN_NUM );							//	Step 3 of section 16.4
//	pGPIO->GPIO_AFSEL SET_BIT( I2C_SDA_PIN_NUM );
//	
//	pGPIO->GPIO_ODR SET_BIT( I2C_SCL_PIN_NUM );								//	Step 4 of section 16.4
//	pGPIO->GPIO_ODR SET_BIT( I2C_SDA_PIN_NUM );
//	
//	pGPIO->GPIO_PCTL &= ~(0xF<<I2C_SCL_PIN_NUM);							//	Step 5 of section 16.4	(The bit positions are cleared first and
//	pGPIO->GPIO_PCTL &= ~(0xF<<I2C_SDA_PIN_NUM);							//													 then set appropriately)
//	
//	pGPIO->GPIO_PCTL |= (0x3<<I2C_SCL_PIN_NUM);
//	pGPIO->GPIO_PCTL |= (0x3<<I2C_SDA_PIN_NUM);
//	
//	//pI2Cx->MCR SET_BIT(I2C_MCR_MFE);													//	Step 6 of section 16.4
//	
//	//Step7 : Set desired spd mode & clock speed
//	switch(SpeedMode)																					//	Enable/Disable High speed mode
//	{
//		case I2C_SPEED_MODE_HS: pI2Cx->MTPR SET_BIT( I2C_MTPR_HSE );							break;
//		default:								pI2Cx->MTPR CLR_BIT( I2C_MTPR_HSE );							break;
//	}
//	
//	uint8_t TimerPRD = ( SYS_CLK/(20*ClkSpeed) ) - 1;					//	Timer Period
//	
//	pI2Cx->MTPR |= TimerPRD<<I2C_MTPR_TPR;										//	Step 7 of section 16.4
//	
//	/*Step 8 : Set Master's Slave Address*/
//	
//	
//	/* Step 9 and further are for sending data. They will be implemented in the send data api */
//	
//	
//	//
//}



/******************************************************************************************************************
* @fnName
* @brief	-
* @param	-
* @return	-
*																																																									*
* @Note		-
******************************************************************************************************************/
void I2CInit2(I2CHandle* pI2CHandle)
{
	uint8_t I2Cx, SpeedMode, ClkSpeed, ACKControl, UseAsSlave;
	
	I2Cx				= pI2CHandle->I2Cx;
	SpeedMode		= pI2CHandle->SpeedMode;
	ClkSpeed 		= pI2CHandle->ClkSpeed;
	ACKControl	= pI2CHandle->ACKControl;
	UseAsSlave	= pI2CHandle->UseAsSlave;
	
	
	uint8_t Error = I2CClockControl(I2Cx, ENABLE);						//	Enable clock to the module and get error code.
	
	if(Error)		return;																				//	Break out of the function in case of an error.
	
	I2C_reg* pI2Cx = I2CGetAddress(I2Cx);
	pI2CHandle->pI2Cx = pI2Cx;
	
	uint8_t I2C_SCL_PIN = GetSCLPin(I2Cx);
	uint8_t I2C_SDA_PIN = GetSDAPin(I2Cx);
	
	uint8_t I2C_SCL_PIN_NUM = getPinNumber(I2C_SCL_PIN);
	uint8_t I2C_SDA_PIN_NUM = getPinNumber(I2C_SDA_PIN);
	
	GPIO_reg* pGPIO = getPortAddr(I2C_SCL_PIN, APB_BUS);
	
	
	GPIO_ClockControl(getPortName(I2C_SCL_PIN), ENABLE);			//	Step 2 of section 16.4
	
	pGPIO->GPIO_AFSEL SET_BIT( I2C_SCL_PIN_NUM );							//	Step 3 of section 16.4
	pGPIO->GPIO_AFSEL SET_BIT( I2C_SDA_PIN_NUM );
	
	pGPIO->GPIO_ODR CLR_BIT( I2C_SCL_PIN_NUM );								//	Step 4 of section 16.4
	pGPIO->GPIO_ODR SET_BIT( I2C_SDA_PIN_NUM );
	
	pGPIO->GPIO_PCTL &= ~(0xF<<I2C_SCL_PIN_NUM);							//	Step 5 of section 16.4	(The bit positions are cleared first and
	pGPIO->GPIO_PCTL &= ~(0xF<<I2C_SDA_PIN_NUM);							//													 then set appropriately)
	
	pGPIO->GPIO_PCTL |= (0x3<<I2C_SCL_PIN_NUM);
	pGPIO->GPIO_PCTL |= (0x3<<I2C_SDA_PIN_NUM);
	
	//pI2Cx->MCR SET_BIT(I2C_MCR_MFE);													//	Step 6 of section 16.4
	
	/*Step7 : Set desired spd mode & clock speed*/
	switch(SpeedMode)																					//	Enable/Disable High speed mode
	{
		case I2C_SPEED_MODE_HS: pI2Cx->MTPR SET_BIT( I2C_MTPR_HSE );
														pI2Cx->MCS	SET_BIT( I2C_MCS_HS );							break;
		default:								pI2Cx->MTPR CLR_BIT( I2C_MTPR_HSE );
														pI2Cx->MCS	CLR_BIT( I2C_MCS_HS );							break;
	}
	
	uint8_t TimerPRD = ( SYS_CLK/(20*ClkSpeed) ) - 1;					//	Timer Period
	
	pI2Cx->MTPR |= TimerPRD<<I2C_MTPR_TPR;										//	Step 7 of section 16.4
	
	switch(ACKControl)																				//	Enable/Disable Auto ACK
	{
		case I2C_AUTO_ACK_ENABLE:		pI2Cx->MCS SET_BIT( I2C_MCS_ACK );
		case I2C_AUTO_ACK_DISABLE:	pI2Cx->MCS CLR_BIT( I2C_MCS_ACK );
	}
	
	switch(UseAsSlave)
	{
		case YES:		pI2Cx->SCSR SET_BIT(1);			break;
		case NO:		pI2Cx->SCSR CLR_BIT(1);			break;
	}
	
	pI2Cx->SOAR |= ( (pI2CHandle->MasterAddress)<<0 );				//	Set Master's Own Address
	
	pI2Cx->MCLKOCNT |= (0x10)<<0;															//	Set a timeout of 256 Clk cycles for clock stretching.
	
	/* Step 8 and further are for sending data. They will be implemented in the send data api */
}



/******************************************************************************************************************
* @I2CMasterSendData()																																														*
* @brief					-	Send data over an I2C Module in Master mode.																									*
* @pI2CHandle			-	Pointer to the handle structure of I2C Module.																								*
*	@SlaveAddress		-	Address of the device to which data should be sent.																						*
*	@TxBuf					-	Pointer to the data buffer.																																		*
*	@Len						-	Length of the data (in bytes), i.e., the no. of 8 bit packets that are to be sent.						*
* @return					-	Error Code( 1 if transmission error has occured )																							*
*																																																									*
* @Note		-
******************************************************************************************************************/
uint8_t I2CMasterSendData(I2CHandle* pI2CHandle, uint8_t SlaveAddress, uint8_t* TxBuf, uint8_t Len)
{
	I2C_reg* pI2Cx = pI2CHandle->pI2Cx;
	
	pI2Cx->MCR SET_BIT( I2C_MCR_MFE );
	
	pI2Cx->MSA &= 0xFFFFFF00;									//	Step 8 of section 16.4
	pI2Cx->MSA |= ( SlaveAddress<<1 );
	
	uint8_t Data = *TxBuf;
	pI2Cx->MDR |= Data;												//	Step 9 of section 16.4
	
	pI2Cx->MCS SET_BIT( I2C_MCS_ACK );
	pI2Cx->MCS CLR_BIT( I2C_MCS_STOP );
	pI2Cx->MCS SET_BIT( I2C_MCS_START );
	pI2Cx->MCS SET_BIT( I2C_MCS_RUN );
	while(pI2Cx->MCS & 0x1);									//	Wait until the transmission completes.
	if(pI2Cx->MCS & 0x2)				return 1;			//	Return 1 in case of an error.
	TxBuf++;
	Len--;
	
	while(Len>0)
	{
		Data = *TxBuf;
		pI2Cx->MDR |= Data;											//	Step 9 of section 16.4
		
		while(pI2Cx->MCS & 0x1);								//	Wait until the transmission completes.
		if(pI2Cx->MCS & 0x2)				return 1;		//	Return 1 in case of an error.
		
		TxBuf++;
		Len--;
	}
	
	pI2Cx->MCS CLR_BIT( I2C_MCS_START );
	pI2Cx->MCS CLR_BIT( I2C_MCS_RUN );
	pI2Cx->MCS SET_BIT( I2C_MCS_STOP );
	
	return 0;																	//	Return 0 if the transmission was successful.
}



/******************************************************************************************************************
* @I2CDeInit()																																																		*
* @brief				-	Reset and turn off an I2C Module.																																*
* @I2Cx					-	Name of the I2C module.																																					*
******************************************************************************************************************/
void I2CDeInit(uint8_t I2Cx)
{
	SYSCTL->SRI2C SET_BIT( (I2Cx-10) );				//	Reset the I2C Module.
	SYSCTL->SRI2C CLR_BIT( (I2Cx-10) );
	
	I2CClockControl(I2Cx,DISABLE);
}



/******************************************************************************************************************
*	@I2CGetAddress()																																																*
* @I2Cx			-	Name of the I2C module.																																							*
*	@return		-	Module Access Pointer of the given I2C Module.																											*
******************************************************************************************************************/
I2C_reg* I2CGetAddress(uint8_t I2Cx)
{
	switch(I2Cx)
	{
		case I2C0:		return pI2C0;
		case I2C1:		return pI2C0;
		case I2C2:		return pI2C0;
		case I2C3:		return pI2C0;
	}
}



/******************************************************************************************************************
* @GetSCLPin()																																																		*
* @param	-	I2C Module Name.																																											*
* @return	-	SCL Pin of the given I2C Module.																																			*
******************************************************************************************************************/
uint8_t GetSCLPin(uint8_t I2Cx)
{
	switch(I2Cx)
	{
		case I2C0:		return I2C0_SCL_PIN;
		case I2C1:		return I2C1_SCL_PIN;
		case I2C2:		return I2C2_SCL_PIN;
		case I2C3:		return I2C3_SCL_PIN;
	}
}



/******************************************************************************************************************
* @GetSDAPin()																																																		*
* @param	-	I2C Module Name.																																											*
* @return	-	SDA Pin of the given I2C Module.																																			*
******************************************************************************************************************/
uint8_t GetSDAPin(uint8_t I2Cx)
{
	switch(I2Cx)
	{
		case I2C0:		return I2C0_SDA_PIN;
		case I2C1:		return I2C1_SDA_PIN;
		case I2C2:		return I2C2_SDA_PIN;
		case I2C3:		return I2C3_SDA_PIN;
	}
}