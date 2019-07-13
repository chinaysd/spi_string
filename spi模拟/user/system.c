#include "system.h"

TIMEOUT_PARA TimeOut_Para[2];

SPI_t spi_0 = 
{
    .ui_SCK = SCK_PIN,
    .ui_MOSI = MOSI_PIN,
    .ui_MISO = MISO_PIN,
    .ui_CS = CS_PIN,
};

void System_Init(void)
{
     TimeOutDet_Init();
     Led_Init();
     Spi_Init(&spi_0);
     Timer_Init();
}

void System_Handle(void)
{
    if(TimeOutDet_Check(&TimeOut_Para[0])){
       TimeOut_Record(&TimeOut_Para[0],1);
        #ifdef spi_master      //主机发送
        Simulate_Spi_Write_Data(0xfa,0xfb,0x1101);
        #endif
    }
    #ifdef spi_slave       //从机接收
    RevDataHandle();       
    #endif
}


