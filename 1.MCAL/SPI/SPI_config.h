/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: SPI    			******************/
/***************		Date: 8-10-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_


/*options:1- MSB
 *        2- LSB */
#define DATA_ORDER       MSB


/*options: 1- SAMPLE
 *         2- SETUP */
#define CLOCK_PHASE     SAMPLE


/*options: 1- LOW_IN_IDLE
 *         2- HIGH_IN_IDLE */
#define CLOCK_POLARITY  LOW_IN_IDLE


/*options:1-DIVIDE_BY_4
 *        2-DIVIDE_BY_16
 *        3-DIVIDE_BY_64
 *        4-DIVIDE_BY_128 */
#define CLOCK_RATE      DIVIDE_BY_16

#endif
