/*****************************************************************/
/*****************************************************************/
/***************		Author: Alyaa Mohamed	******************/
/***************		Layer: MCAL				******************/
/***************		SWC: WATCH DOG			******************/
/***************		Date: 1-10-2020			******************/
/***************		Version: 1.00			******************/
/*****************************************************************/
/*****************************************************************/

#ifndef WATCHDOG_INTERFACE_H_
#define WATCHDOG_INTERFACE_H_

#define WDT_16ms     0
#define WDT_32ms     1
#define WDT_64ms     2
#define WDT_0.125s   3
#define WDT_0.25s    4
#define WDT_0.5s     5
#define WDT_1s       6
#define WDT_2s       7
#define WDT_4s       8
#define WDT_8s       9

void WDT_voidEnable(void);

void WDT_voidDisable(void);

u8 WDT_u8Sleep(u8 Copy_u8SleepTime);

#endif