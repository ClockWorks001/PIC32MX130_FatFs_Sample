/*******************************************************************************
 *	UART_入力処理
 *	UART2を使用 
 *	author  :hiroshi murakami
 *	created :20161225
 *	modified:-
 ******************************************************************************/
#define UART_CMND_LIB

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include "./integer.h"
#include "./xprintf.h"
#include "./vFIFO.h"
#include "./vUART_CMND_lib.h"

//xprintf FIFO
FIFO_STRUCT TxFifo;
BYTE TxBuff[256];

//******************************************************************************
//* initialization
//******************************************************************************
void vUART_CMND_Init(void) {
    vFifo_init (&TxFifo, sizeof(TxBuff), &TxBuff[0]);

	ucCPtr = 0;							// バッファクリアの指示。バッファポインタを戻す

	xdev_out(vUART_CMND_Putc);

}

//******************************************************************************
//* コマンド文字列取得,コマンドモード移行
//* 1文字づつ受信したデータをコマンドバッファに格納する。
//* エコーバック処理を行う
//******************************************************************************
enum eUART_CMND eUART_CMND_Getc(void) {
	//	static char ch;
	unsigned char ucRxData;
	//		BYTE numBytesRead;

	if(UART2_DataReady) {		//受信が有ったら、
		// PIR1bits.RC1IF = 0;
		ucRxData = UART2_Read();			//受信データを取り込む

		switch(ucRxData) {						//取り込んだ1文字をチェック
		case 0x00:								//null
			break;
		case '\b':	// BS
			if(ucCPtr > 0) {
				ucCPtr--;						//バッファから1文字削除
				//コマンド・バッファから1文字削除されたとき消されたように表示する
				xputs("\b \b");		//1文字もどってクリア
			}
			return eUART_CMND_Wait;
			break;
            
		case '\n':	// LFは破棄
			break;
		case '\r':	// Enter(コマンド確定)
			if(ucCPtr < CMND_BUFFER_SIZE) {
				//まだコマンドバッファに登録できるとき
				cCmdBuf[ucCPtr] = 0x00;			//NULLコード
			} else {
				//コマンドバッファが満杯のとき
				cCmdBuf[CMND_BUFFER_SIZE] = 0x00;		//NULLコード
			}
			ucCPtr = 0 ;						//コマンドバッファをクリア
            xputs("\n");
			return eUART_CMND_Exec;
			break;

		case '\x7F':	// (DEL)入力のキャンセル
			ucCPtr = 0 ;						//コマンドバッファをクリア
			xputs("\nDelete the Command\n>");
			return eUART_CMND_Del;
			break;

		case '\x1B':	// (ESC)メニュー階層のエスケープ
			ucCPtr = 0 ;						//コマンドバッファをクリア
			xputs("\nEscape the Command\n>");
			return eUART_CMND_Esc;
			break;

		default:	// コマンド文字列の取得
			if(ucCPtr < CMND_BUFFER_SIZE) {
				//まだコマンドバッファに登録できるとき
				cCmdBuf[ucCPtr] = ucRxData;			//コマンド文字を登録
				xputc (ucRxData);	//1文字エコーバック
				ucCPtr++;							//次の登録位置
			} else {
                ucCPtr = 0 ;						//コマンドバッファをクリア
				xputs("\nCommand Over Flow\n>");
				return eUART_CMND_Err;
			}
		}

	}
	return eUART_CMND_Wait;
}

/* Put a byte into Tx FIFO */
void vUART_CMND_Putc(BYTE d)
{
	while (TxFifo.ct >= TxFifo.buffer_size){
        vUART_TxPutc();
    } ;	/* Wait while Tx FIFO is full */
    vFifo_putc (&TxFifo, d);
}

void vUART_TxPutc(void){
    while(!(UART2_StatusGet() & UART2_TX_FULL) && vFifo_test(&TxFifo)){
        UART2_Write(vFifo_getc(&TxFifo));
    }
}