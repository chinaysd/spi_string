#include "hal_init.h"


unsigned char App_TxBuf[6];

void Hal_Init(void)
{
	Hal_TimerInit();
	Hal_PushrodInit(PUSHROD_SUM);
        Hal_MemoryInit(3);
	Hal_UartInit(UART0_ID, App_TxBuf, sizeof(App_TxBuf));
}

void Hal_ProcessPoll(void)
{
	
}

