#include "hal_spi.h"

unsigned char RevNum,RevData,RevString[RevDataSize];
unsigned int RevTempData;

unsigned char Simulate_Spi_Read_Byte(void);
void Simulate_Spi_Write_Byte(unsigned char data);

static void Delay_Time_us(unsigned int Delay)
{
    static unsigned int Counts;
    while(Delay --){
          for(Counts = Delay_Time; Counts > 0; Counts --);
    }
}

#ifdef spi_master                      //主机
void Spi_Init(SPI_t *addr)
{
    GPIO_Init(SCK_PORT,(GPIO_Pin_TypeDef)addr->ui_SCK,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(MOSI_PORT,(GPIO_Pin_TypeDef)addr->ui_MOSI,GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(MISO_PORT,(GPIO_Pin_TypeDef)addr->ui_MISO,GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(CS_PORT,(GPIO_Pin_TypeDef)addr->ui_CS,GPIO_MODE_OUT_PP_HIGH_FAST);
}
#endif
#ifdef spi_slave                      //从机
void Spi_Init(SPI_t *addr) 
{
    GPIO_Init(SCK_PORT,(GPIO_Pin_TypeDef)addr->ui_SCK,GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(MOSI_PORT,(GPIO_Pin_TypeDef)addr->ui_MOSI,GPIO_MODE_IN_FL_NO_IT);//GPIO_MODE_IN_FL_NO_IT
    GPIO_Init(MISO_PORT,(GPIO_Pin_TypeDef)addr->ui_MISO,GPIO_MODE_IN_FL_NO_IT);     //GPIO_MODE_OUT_PP_HIGH_FAST
    GPIO_Init(CS_PORT,(GPIO_Pin_TypeDef)addr->ui_CS,GPIO_MODE_IN_FL_NO_IT);
}
#endif

void Simulate_Spi_Write_Byte(unsigned char data)
{
    unsigned char kk;
    SPI_CS_SET(0);
    SPI_SCK_SET(0);
    Delay_Time_us(Delay_Time);
    for(kk = 0; kk < 8 ; kk ++){
        if((data & 0x80) == 0x80){
            SPI_MOSI_SET(1);
        }else{
            SPI_MOSI_SET(0);
        }
        Delay_Time_us(Delay_Time);
        SPI_SCK_SET(1);
        Delay_Time_us(Delay_Time);
        SPI_SCK_SET(0);
        data = data << 1;
    }
    SPI_CS_SET(1);
}

static unsigned char Simulate_Spi_Write_ByteHandle(SPI_PROTOCOL_t *p)
{
     static unsigned char i;
     
     for(i = 0 ; i < DataSize; i ++)
     {
         Simulate_Spi_Write_Byte(p->SPI_Buf[i]);
     }
     return 0;
}

unsigned char Simulate_Spi_Write_Data(unsigned char addr,unsigned char id,unsigned int Data)
{
    SPI_PROTOCOL_t spi_buf;
    memset(&spi_buf,0,sizeof(spi_buf));
    spi_buf.SpiData_Format.SPI_ADDR = addr;
    spi_buf.SpiData_Format.SPI_ID = id;
    spi_buf.SpiData_Format.SPI_DATA1 = Hight(Data);
    spi_buf.SpiData_Format.SPI_DATA2 = Low(Data);
    spi_buf.SpiData_Format.SPI_CHECKSUM = (unsigned char)(spi_buf.SpiData_Format.SPI_ADDR+spi_buf.SpiData_Format.SPI_ID+spi_buf.SpiData_Format.SPI_DATA1+spi_buf.SpiData_Format.SPI_DATA2);
    spi_buf.SpiData_Format.SPI_STOP1 = 0x0d;
    spi_buf.SpiData_Format.SPI_STOP2 = 0x0a;
    return Simulate_Spi_Write_ByteHandle(&spi_buf);
}

unsigned char Simulate_Spi_Read_Byte(void)
{
    unsigned char kk,ret = 0;
    SPI_CS_SET(0);
    SPI_SCK_SET(0);
    Delay_Time_us(Delay_Time);
    for(kk = 0; kk < 8 ; kk ++){
        SPI_SCK_SET(1);
        if(SPI_MOSI_Read()){
           ret |= 0x01;
        }
        Delay_Time_us(Delay_Time);
        SPI_SCK_SET(0);
        Delay_Time_us(Delay_Time);
        ret = ret << 1;
    }
    SPI_CS_SET(1);
    return ret;
}

static unsigned char RevComplete(void)
{
    if(RevNum & 0x80){
        RevNum = 0x00;
        return 1;
    }else{
        return 0;
    }
}

static void RevProcessHandle(void)
{
    static unsigned char CntsTemp;
    RevData = Simulate_Spi_Read_Byte();
    #if 1
    if(RevData == 0xfa){
       ++ CntsTemp;
       if(CntsTemp & 0x01){
          LED_SET(1);
       }else{
          LED_SET(0);
       }
    }
    #endif
    if((RevNum & 0x80) == 0x00){
        if(RevNum == 0x40){
           if(RevData == 0x0a){
              RevNum = 0x80;
           }else{
              RevNum = 0x00;
           }
        }else{
           if(RevData == 0x0d){
              RevNum = 0x40;
           }else{
              RevString[RevNum] = RevData;
              RevNum ++;
              if(RevString[0] != 0xFA){
                 RevNum = 0x00;
                 //memset(&RevString,0,sizeof(RevString));
              }
              if(RevNum > RevDataSize){
                 RevNum = 0x00;
                 //memset(&RevString,0,sizeof(RevString));
              }
           }
        }
    }
}

void RevDataHandle(void)
{
    RevProcessHandle();
    if(RevComplete()){
       RevTempData = (unsigned int)Get32Bit(RevString[2],RevString[3]);
       memset(&RevString,0,sizeof(RevString));
    }
    switch(RevTempData)
    {
        case 0x1101:
              LED_SET(1);
        break;
        case 0x1102:
             LED_SET(0);
        break;
        case 0x1104:

        break;
        case 0x1108:

        break;
        default:
        break;
    }
}














