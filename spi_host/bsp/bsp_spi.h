#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_

#include "stm8s_conf.h"
#include "string.h"


#define CS_PORT      GPIOA
#define CS_PIN       GPIO_PIN_3
#define CS_SET(X)    ((X)?(GPIO_WriteHigh(CS_PORT,CS_PIN)):(GPIO_WriteLow(CS_PORT,CS_PIN)))


#define SendBufSize     7
#define Hight(x)        ((x>>8)&0xff)
#define Low(x)          ((x)&0xff)
typedef struct 
{
    unsigned char ADDR;
    unsigned char ID;
    unsigned char DATA1;
    unsigned char DATA2;
    unsigned char CHECKSUM;
    unsigned char STOP1;
    unsigned char STOP2;
}
DATA_FORMAT_t;

typedef union 
{
    /* data */
    unsigned char Buf[SendBufSize];
    DATA_FORMAT_t Data_Format;
}
PROTOCOL_TX;











void Spi_Init(void);
//u8 spi_rw(u8 byte);
unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned int Data);


#endif
