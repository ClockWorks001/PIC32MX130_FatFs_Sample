/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

//#ifdef __XC32
//    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
//#endif

//#include <plib.h>            /* Include to use PIC32 peripheral libraries     */
//#include "system.h"         /* System funct/params, like osc/periph config    */
#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "user.h"            /* variables/params used by user.c               */


#include "vRTCC_lib.h"
#include "vTimer1_lib.h"
#include "vUSART_Menu_lib.h"
#include "vUSART_CMND_lib.h"
//#include "vWait_lib.h"


#define LED0	LATBbits.LATB6 //Min routin check blink!
//#define LED1	LATBbits.LATB12 //Min routin check blink!

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* TODO Initialize User Ports/Peripherals/Project here */
void InitApp(void)
{
		
	//unsigned int pll_startup_counter = 100;
	//while(pll_startup_counter--);

	/* Setup analog functionality and port direction */
	// (1)Define PortB
//    TRISB = 0x0000AB1E;    // 32bit I/O SETTING
//    LATB  = 0x00000000;    // 32bit OUTPUT REGiSTER
//    PORTB = 0x00000000;    // 32bit INPUT REGiSTER

	// (1)Define PortA
//    TRISA = 0x0000000F;    // 32bit I/O SETTING
//    LATA  = 0x00000000;    // 32bit OUTPUT REGiSTER
//    PORTA = 0x00000000;    // 32bit INPUT REGiSTER

	// (2)Define ANSEL (All Degital Port)
    ANSELA = 0;
    ANSELB = 0;

	// (3)モジュール初期化
//	vTIMER1_init();
//	vRTCC_init();
	vUSART_menu_init();

	//Initialize SPI port
//	init_spi();

	//vWait_100ms(3);

}


//*****************************************************************************
void user_main(void) {

	static int i10msecInterval=0;		// 10msec
	static int i1secInterval=0;			// 1sec
	
	//開始処理
	//	LED0 = 1;						//LEDを点灯
	//	xprintf("Test Start!\r\n");		//開始のメッセージ

	while(1) {

		PowerSaveIdle();
		
		if(iIntervalOn(&i10msecInterval,10)) {
//		if(cFlag10mSec) {
//			cFlag10mSec = 0;
			vModeUartControl11();		// UART Menu contorol
		}

		if(iIntervalOn(&i1secInterval,1000)) {
//			cFlagSec = 0;
//			xprintf( "\n\riIntervalTimer1 is %d", i1secInterval);
			LED0 = ~LED0;
		}

		if(cFlag1Minute) {
			cFlag1Minute = 0;
		}

	}
}