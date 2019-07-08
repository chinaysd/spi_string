#include "bsp_spi.h"
#include "system.h"

extern TIMEOUT_PARA TimeOut_Para[4];


static void CS_Init(void)
{
    GPIO_Init(CS_PORT,CS_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    CS_SET(1);
}


void Spi_Init(void)
{
    CS_Init();

    SPI_DeInit();
 
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);
 
    GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);
 
    GPIO_Init(GPIOC,GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
 
    SPI_Init(SPI_FIRSTBIT_MSB,SPI_BAUDRATEPRESCALER_2,\
             SPI_MODE_MASTER, SPI_CLOCKPOLARITY_LOW,\
             SPI_CLOCKPHASE_1EDGE,\
             SPI_DATADIRECTION_2LINES_FULLDUPLEX,\
             SPI_NSS_SOFT,7);
    SPI_Cmd(ENABLE);
}

void Delay_Time(unsigned char Time)
{
    static unsigned char Cnts,Counts;
    for(Cnts = Time;Cnts > 0 ; Cnts --)
    {
        for(Counts = 100;Counts > 0 ; Counts--);
    }
}

static u8 spi_rw(u8 byte)
{
    Delay_Time(100);
    while(SPI_GetFlagStatus(SPI_FLAG_TXE)==RESET);
    SPI_SendData(byte);
    Delay_Time(100);
    while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
    byte=SPI_ReceiveData();
    Delay_Time(100);
    return byte;
 
}


static unsigned char SendData(PROTOCOL_TX *p)
{
    static unsigned char i;
    for(i = 0;i < SendBufSize; i ++)
    {
        spi_rw(p->Buf[i]);
    }
    return 0;
}

unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned int Data)
{
    PROTOCOL_TX buf;
    memset(&buf,0,sizeof(buf));
    buf.Data_Format.ADDR = addr;
    buf.Data_Format.ID   = id;
    buf.Data_Format.DATA1 = Hight(Data);
    buf.Data_Format.DATA2 = Low(Data);
    buf.Data_Format.CHECKSUM = (unsigned char)(buf.Data_Format.ADDR+buf.Data_Format.ID+buf.Data_Format.DATA1+buf.Data_Format.DATA2);
    buf.Data_Format.STOP1 = 0x0d;
    buf.Data_Format.STOP2 = 0x0a;
    return SendData(&buf);
}





