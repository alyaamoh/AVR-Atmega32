/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: TWI    			******************/
/***************		Date: 12-10-2020		******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum{
	
	NoError,
	StartConditionErr,
	RepeatedStartErr,
	SlaveAddressWithWriteErr,
	SlaveAddressWithReadErr,
	MasterWriteByteErr,
	MasterReadByteErr,
	
}TWI_ErrStatus;

//pass 0 to the address argument if this master node will not be addressed
void TWI_voidInitMaster(u8 Copy_u8Address);

void TWI_voidInitSlave(u8 Copy_u8Address);

TWI_ErrStatus TWI_SendStartCondition(void);

TWI_ErrStatus TWI_SendRepeatedStart(void);

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);

TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);

TWI_ErrStatus TWI_MasterSendDataByte(u8 Copy_u8DataByte);

TWI_ErrStatus TWI_MasterReadDataByte(u8* Copy_u8DataByte);

void TWI_voidSendStopCondition(void);

#endif
