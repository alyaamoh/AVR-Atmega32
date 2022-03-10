/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: TWI    			******************/
/***************		Date: 12-10-2020		******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TWI_interface.h"
#include "TWI_register.h"
#include "TWI_config.h"
#include "TWI_private.h"

//pass 0 to the address argument if this master node will not be addressed
void TWI_voidInitMaster(u8 Copy_u8Address){

	//generate clock speed=400KHz with 8MHz system frequency
	//1-set bit rate register to 2
	TWBR=2;

	//2-clear the prescaler bits
	CLR_BIT(TWSR,TWSR_TWPS0);
	CLR_BIT(TWSR,TWSR_TWPS1);

	//enable Acknowledge bit generation
	SET_BIT(TWCR,TWCR_TWEA);

	//check if the node will be addressed
	if(Copy_u8Address != 0){

		//assign the required address in 7MSB in the address register
		TWAR=Copy_u8Address<<1;
	}

	//enable TWI
	SET_BIT(TWCR,TWCR_TWEN);

}

void TWI_voidInitSlave(u8 Copy_u8Address){

	//enable Acknowledge bit generation
	SET_BIT(TWCR,TWCR_TWEA);

	//assign the required address in 7MSB in the address register
	TWAR=Copy_u8Address<<1;

	//enable TWI
	SET_BIT(TWCR,TWCR_TWEN);

}

TWI_ErrStatus TWI_SendStartCondition(void){

	TWI_ErrStatus Local_Error=NoError;

	//send start condition on the bus
	SET_BIT(TWCR,TWCR_TWSTA);

	//clear the interrupt flag to start the previous operation
	SET_BIT(TWCR,TWCR_TWINT);

	//wait until the operation complete and the flag is raised again
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	//check the operation status
	if((TWSR & 0xF8) != START_ACK){

		Local_Error=StartConditionErr;
	}

	return Local_Error;
}

TWI_ErrStatus TWI_SendRepeatedStart(void){

	TWI_ErrStatus Local_Error=NoError;

	//send start condition on the bus
	SET_BIT(TWCR,TWCR_TWSTA);

	//clear the interrupt flag to start the previous operation
	SET_BIT(TWCR,TWCR_TWINT);

	//wait until the operation complete and the flag is raised again
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	//check the operation status
	if((TWSR & 0xF8) != REP_START_ACK){

		Local_Error=RepeatedStartErr;
	}

	return Local_Error;
}

TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress){

	TWI_ErrStatus Local_Error=NoError;


	//set the required slave address in 7MSB on the bus
	TWDR=Copy_u8SlaveAddress<<1;

	//set the write request
	CLR_BIT(TWDR,0);

	//clear start condition bit
		CLR_BIT(TWCR,TWCR_TWSTA);

	//clear the interrupt flag to start the previous operation
	SET_BIT(TWCR,TWCR_TWINT);

	//wait until the operation complete and the flag is raised again
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	//check the operation status
	if((TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK){

		Local_Error=SlaveAddressWithWriteErr;
	}

	return Local_Error;
}

TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress){

	TWI_ErrStatus Local_Error=NoError;

	//clear start condition bit
	CLR_BIT(TWCR,TWCR_TWSTA);

	//set the required slave address in 7MSB on the bus
	TWDR=Copy_u8SlaveAddress<<1;

	//set the read request
	SET_BIT(TWDR,0);

	//clear the interrupt flag to start the previous operation
	SET_BIT(TWCR,TWCR_TWINT);

	//wait until the operation complete and the flag is raised again
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	//check the operation status
	if((TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK){

			Local_Error=SlaveAddressWithReadErr;
		}
	return Local_Error;
}

TWI_ErrStatus TWI_MasterSendDataByte(u8 Copy_u8DataByte){

	TWI_ErrStatus Local_Error=NoError;

	//send the data on the bus
	TWDR = Copy_u8DataByte;

	//clear the interrupt flag to start the previous operation
	SET_BIT(TWCR,TWCR_TWINT);

	//wait until the operation complete and the flag is raised again
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	//check the operation status
	if((TWSR & 0xF8) != MSTR_WR_BYTE_ACK){

			Local_Error=MasterWriteByteErr;
		}

	return Local_Error;
}

TWI_ErrStatus TWI_MasterReadDataByte(u8* Copy_u8DataByte){

	TWI_ErrStatus Local_Error=NoError;

	//clear the interrupt flag to allow the slave to send the data
	SET_BIT(TWCR,TWCR_TWINT);

	//wait until the operation complete and the flag is raised again
	while(GET_BIT(TWCR,TWCR_TWINT)==0);

	//check the operation status
	if((TWSR & 0xF8) != MSTR_RD_BYTE_WITH_ACK){

			Local_Error=MasterReadByteErr;
		}
	else{

		//read the data
		*Copy_u8DataByte=TWDR;
	}

	return Local_Error;
}

void TWI_voidSendStopCondition(void){

	//Set the stop condition bit
	SET_BIT(TWCR,TWCR_TWSTO);

	//clear the interrupt flag to allow the slave to send the data
	SET_BIT(TWCR,TWCR_TWINT);

}
