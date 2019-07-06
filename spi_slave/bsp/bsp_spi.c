#include "bsp_spi.h"



void Spi_Init(void)
{
    #if 0
    SPI_DeInit();
 
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_FAST);//
 
    GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);//
 
    GPIO_Init(GPIOC,GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
 
    SPI_Init(SPI_FIRSTBIT_MSB,SPI_BAUDRATEPRESCALER_2,\
             SPI_MODE_SLAVE, SPI_CLOCKPOLARITY_LOW,\
             SPI_CLOCKPHASE_1EDGE,\
             SPI_DATADIRECTION_2LINES_FULLDUPLEX,\
             SPI_NSS_SOFT,7);
 
    SPI_Cmd(ENABLE);
    #else
     SPI_DeInit(); 

     /* 初始化SPI , 从机和主机的相位有效沿一定要一致*/ 
     GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_FAST);//
 
     GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);//
 
     //GPIO_Init(GPIOC,GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);

     SPI_Init(SPI_FIRSTBIT_MSB, SPI_BAUDRATEPRESCALER_2,SPI_MODE_SLAVE,SPI_CLOCKPOLARITY_LOW, SPI_CLOCKPHASE_1EDGE, SPI_DATADIRECTION_2LINES_FULLDUPLEX, SPI_NSS_SOFT, 0x07); 
            

     SPI_ITConfig(SPI_IT_RXNE,ENABLE); 

     SPI_NSSInternalSoftwareCmd(DISABLE);//产生SSI从机信号，也可放在外部中断里来使能从机中断 

     SPI_Cmd(ENABLE); 
    #endif
}

 u8 SPI_SLAVE_SendByte(u8 byte)//把while判断非空标志全部去掉，不然等待时间太长会错帧，判断等待交给主机做 

 { 

   /* Loop while DR register in not emplty */ 

   while (SPI_GetFlagStatus( SPI_FLAG_TXE) == RESET); 

   /* Send byte through the SPI1 peripheral */ 

   SPI_SendData(byte); 

   /* Wait to receive a byte */ 

   while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET); 

   /* Return the byte read from the SPI bus */ 

   return SPI_ReceiveData();   

  } 
#if 0
unsigned char Spi_Handle(unsigned char byte)
{
    while(SPI_GetFlagStatus(SPI_FLAG_TXE)==RESET);
 
    SPI_SendData(byte);
 
    while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
 
    byte=SPI_ReceiveData();
 
 
    return byte;

}
#endif













