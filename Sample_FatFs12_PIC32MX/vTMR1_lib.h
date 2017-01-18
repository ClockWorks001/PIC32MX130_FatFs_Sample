/*******************************************************************************
 *	処理タイミング用 TIMER1 設定
 *  1000Hz 1msec interval
 *	author  :hiroshi murakami
 *	created :20161225
 *	modified:-
 ******************************************************************************/

/*****************************
 * VARIABLES
 *****************************/
#if defined TMR1_LIB
//    static volatile
volatile unsigned int uiTMR001, uiTMR002, uiTMR003 ;
#else
volatile extern unsigned int uiTMR001, uiTMR002, uiTMR003;
#endif

/*****************************
 * PROTOTYPES
 *****************************/
void Intrupt_TMR1(void);    //decrease timer parameter step by 1msec.
#define IS_uiTMR001_FINISH (uiTMR001==0)
#define IS_uiTMR002_FINISH (uiTMR002==0)
#define IS_uiTMR003_FINISH (uiTMR003==0)


