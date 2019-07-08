#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_

#include "stm8s_conf.h"
#include "string.h"
#include "bsp_led.h"


#define Get32Bit(x,y)       ((((x)<<8)|y)&0xffff)








void Spi_Init(void);
void RevProcessHandle(void);
void Spi_Handle(void);



#endif


