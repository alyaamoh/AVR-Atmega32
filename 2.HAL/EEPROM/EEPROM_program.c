#include "STD_TYPES.h"
#include <util\delay.h>

#include "TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"

void EEPROM_voidWriteDataByte(u16 Copy_u16LocationAddress,u8 Copy_u8DataByte){

	u8 Local_u8AddressPacket;

	Local_u8AddressPacket=EEPROM_FIXED_ADDRESS | (A2_CONNECTION<<2) | (u8)(Copy_u16LocationAddress>>8);

	//generate start condition on the bus
	TWI_SendStartCondition();

	//send the address packet
	TWI_SendSlaveAddressWithWrite(Local_u8AddressPacket);

	//send the rest 8 bits of the address
    TWI_MasterSendDataByte((u8)Copy_u16LocationAddress);

	//send the data to the memory location
    TWI_MasterSendDataByte(Copy_u8DataByte);

	//send stop condition
    TWI_voidSendStopCondition();
	//delay 10msec to wait for the memory write cycle
	_delay_ms(10);
}

u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress){
	    u8 Local_u8AddressPacket,Local_u8ReceivedData;

		Local_u8AddressPacket=EEPROM_FIXED_ADDRESS | (A2_CONNECTION<<2) | (u8)(Copy_u16LocationAddress>>8);

		//generate start condition on the bus
		TWI_SendStartCondition();

		//send the address packet
		TWI_SendSlaveAddressWithWrite(Local_u8AddressPacket);

		//send the rest 8 bits of the address
		TWI_MasterSendDataByte((u8)Copy_u16LocationAddress);

		//generate repeated start
		TWI_SendRepeatedStart();

		//read request
		TWI_SendSlaveAddressWithRead(Local_u8AddressPacket);

		//read the data
		TWI_MasterReadDataByte(&Local_u8ReceivedData);

		//end the communication
		TWI_voidSendStopCondition();

		return Local_u8ReceivedData;
}
