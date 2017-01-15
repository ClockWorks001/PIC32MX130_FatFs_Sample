/*******************************************************************************
 *	UART_Menu
 *	author  :hiroshi murakami
 *	created :20161225
 *	modified:-
 ******************************************************************************/
#include "ff.h"		//FatFs定義体取得の為

/*****************************
 * VARIABLES
 *****************************/
enum eModeC2 {
	eModeC2_menu_msg1,					//Start message
	eModeC2_menu_init,
	eModeC2_vGetsCMND,
	eModeC2_vExecCmd,					//コマンド分岐
	eModeC2_Command_error,
	eModeC2_end
};


#if defined UART_MENU_LIB

	enum eModeC2 eModeStatusC2;
	unsigned char *ucPtr1, *ucPtr2;			// Pointer for Byte data
	//long p1, p2;

#else
	extern enum eModeC2 eModeStatusC2;
#endif


/*****************************
 * PROTOTYPES
 *****************************/
void vUART_menu_init(void);
void vModeUartControl11(void);

void vCommand_TimeSet(void);
void vCommand_DateSet(void);

void vComandFormatCheck_7Digit(void);	//Comand format check 7digit
void vShowNowTimeMessage(void);			//時間の表示

void vCommand_FatFs(void);
//void vCommand_FatFs_b(void);
//void vCommand_FatFs_d(void);

void vXputs_return(void);
void put_rc (FRESULT rc);				//ステータスOUTPUT


