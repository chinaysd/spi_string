#include "system.h"



TIMEOUT_PARA TimeOut_Para[2];

void System_Init(void)
{
     TimeOutDet_Init();
     Led_Init();
     Timer_Init();
     Spi_Init();
     enableInterrupts();
}



void System_Handle(void)
{
    #if 1
    static unsigned char Cnts;
    if(TimeOutDet_Check(&TimeOut_Para[0])){
        TimeOut_Record(&TimeOut_Para[0],10);
        CS_SET(0);
        Protocol_Send(0xfa,0xfb,0x1101);
        CS_SET(1);
        ++ Cnts;
        if(Cnts & 0x01){
           LED_SET(1);
        }else{
           LED_SET(0);
        }
    }
    #endif
}
