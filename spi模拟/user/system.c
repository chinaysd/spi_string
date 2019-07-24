#include "system.h"

TIMEOUT_PARA TimeOut_Para[2];
u8 UC_Buf[7]={0xfa,0xfb,0x00,0x01,0x55,0x0d,0x0a};

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
    //static unsigned char Cnts;
    //if(TimeOutDet_Check(&TimeOut_Para[0])){
    //   TimeOut_Record(&TimeOut_Para[0],1);
        #ifdef spi_master      //主机发送
        Simulate_Spi_Write_Data(0xfa,0xfb,0x1101);
        #endif
        #if 0
        for(Cnts = 0; Cnts < 7; Cnts ++){
        SPI_Moni_Write_Buf(0xfa,&UC_Buf[Cnts],7);
        }
        if(Cnts == 7){
        Cnts = 0;
        }
        #endif
    //}
    #ifdef spi_slave       //从机接收
    RevDataHandle();       
    #endif
}


