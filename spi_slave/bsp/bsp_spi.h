#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_

#include "stm8s_conf.h"



#define Get32Bit(x,y)       ((((x)<<8)|y)&0xffff)








void Spi_Init(void);
//unsigned char Spi_Handle(unsigned char byte);
 u8 SPI_SLAVE_SendByte(u8 byte);//把while判断非空标志全部去掉，不然等待时间太长会错帧，判断等待交给主机做 

#endif


