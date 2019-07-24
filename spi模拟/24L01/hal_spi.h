#ifndef _HAL_SPI_H_
#define _HAL_SPI_H_

#include "stm8s_conf.h"
#include "string.h"
#include "bsp_led.h"

#define SCK_PORT   GPIOC
#define MOSI_PORT  GPIOC
#define MISO_PORT  GPIOC
#define CS_PORT    GPIOA

#define SCK_PIN    GPIO_PIN_4
#define MOSI_PIN   GPIO_PIN_5
#define MISO_PIN   GPIO_PIN_6  
#define CS_PIN     GPIO_PIN_7

#define SPI_SCK_SET(X)    ((X)?(GPIO_WriteHigh(SCK_PORT,SCK_PIN)):(GPIO_WriteLow(SCK_PORT,SCK_PIN)))
#define SPI_MOSI_SET(X)   ((X)?(GPIO_WriteHigh(MOSI_PORT,MOSI_PIN)):(GPIO_WriteLow(MOSI_PORT,MOSI_PIN)))
#define SPI_MISO_SET(X)   ((X)?(GPIO_WriteHigh(MISO_PORT,MISO_PIN)):(GPIO_WriteLow(MISO_PORT,MISO_PIN)))
#define SPI_MOSI_Read()   GPIO_ReadInputPin(MOSI_PORT,MOSI_PIN)
#define SPI_CS_Read()     GPIO_ReadInputPin(CS_PORT,CS_PIN)

#define SPI_CS_SET(X)     ((X)?(GPIO_WriteHigh(CS_PORT,CS_PIN)):(GPIO_WriteLow(CS_PORT,CS_PIN)))

#define Delay_Time 3
#define DataSize   7
#define Hight(x)   (((x)>>8)&0xff)
#define Low(x)      (x)

#define RevDataSize 7
#define Get32Bit(x,y)    (((x<<8)|y)&0xffff)

typedef struct Spi_Struct
{
    unsigned char ui_SCK;
    unsigned char ui_MOSI;
    unsigned char ui_MISO;
    unsigned char ui_CS;
}
SPI_t;

typedef struct 
{
    unsigned char SPI_ADDR;
    unsigned char SPI_ID;
    unsigned char SPI_DATA1;
    unsigned char SPI_DATA2;
    unsigned char SPI_CHECKSUM;
    unsigned char SPI_STOP1;
    unsigned char SPI_STOP2;
}
SPIDATA_FORMAT_t;

typedef union
{
    /* data */
    unsigned char SPI_Buf[DataSize];
    SPIDATA_FORMAT_t SpiData_Format;
}
SPI_PROTOCOL_t;







void Spi_Init(SPI_t *addr);
//unsigned char Simulate_Spi_Read_Byte(void);
unsigned char Simulate_Spi_Write_Data(unsigned char addr,unsigned char id,unsigned int Data);

void RevDataHandle(void);

u8 SPI_Moni_Write_Buf(u8 Reg,u8 *Buf,u8 len);


#endif
