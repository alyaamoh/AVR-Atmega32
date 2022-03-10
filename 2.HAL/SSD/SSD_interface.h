/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: HAL				******************/
/***************		SWC: SSD				******************/
/***************		Date: 6-9-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/
#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

typedef struct{
	u8 SSD_PORT;
	u8 SSD_TYPE;
	u8 SSD_EnablePort;
	u8 SSD_EnablePin;
}SSD_T;

void SSD_u8SSDON(SSD_T* CopySSD);
void SSD_u8SSDOFF(SSD_T* CopySSD);
void SSD_u8SSDSetNumber(SSD_T* CopySSD,u8 Copy_u8Number);

#endif
