/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: USART   			******************/
/***************		Date: 6-10-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

/*options: 1-CHARSIZE_5BIT
 *         2-CHARSIZE_6BIT
 *         3-CHARSIZE_7BIT
 *         4-CHARSIZE_8BIT
 *         5-CHARSIZE_9BIT */
#define CHARSIZE    CHARSIZE_8BIT


/*OPTIONS: 1-ASYNCHRONOUS
 *         2-SYNCHRONOUS */
#define USART_MODE  ASYNCHRONOUS


/*OPTIONS: 1-PARITY_DISABLED
 *         2-EVEN_PARITY
 *         3-ODD_PARITY */
#define PARITY_MODE  PARITY_DISABLED


/*options: 1-STOP_BIT_1
 *         2-STOP_BIT_2 */
#define STOP_BIT    STOP_BIT_1


#define FOSC        8000000
#define BAUD_RATE   9600


/*options: 1- ENABLE
 *         2- DISABLE */
#define USART_RECEIVER_STATE     ENABLE
#define USART_TRANSMITTER_STATE  ENABLE




#endif
