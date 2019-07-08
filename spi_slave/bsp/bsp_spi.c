#include "bsp_spi.h"

unsigned int MyData;

u8 RxBuf[7]; 

u8 spi_cnt=0; 

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
            

     //SPI_ITConfig(SPI_IT_RXNE,ENABLE); 

     //SPI_NSSInternalSoftwareCmd(DISABLE);//产生SSI从机信号，也可放在外部中断里来使能从机中断 

     SPI_Cmd(ENABLE); 
    #endif
}

 static u8 SPI_SLAVE_SendByte(u8 byte)//把while判断非空标志全部去掉，不然等待时间太长会错帧，判断等待交给主机做 

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

void RevProcessHandle(void)
{
  uint8_t Rx_byte;  
  //static unsigned char Cnts;
  if(GPIO_ReadInputPin(GPIOA, GPIO_PIN_3) == 0)//确认CS脚拉低的这个判断太慢了，总是出错，另谋他法吧！ 
  { 
    Rx_byte = SPI_SLAVE_SendByte(0x36);//设置下一个字节，同时读回主机当前CLK下的字节 
    #if 0
    if(Rx_byte == 0xfb){
      ++ Cnts;
      if(Cnts & 0x01){
        LED_SET(1);
      }else{
        LED_SET(0);
      }
    }
    #endif
        if((spi_cnt & 0x80) == 0){
        if(spi_cnt == 0x40){
            if(Rx_byte == 0x0a){
              spi_cnt = 0x80;
            }else{
              spi_cnt = 0x00;
            }
        }else{
        if(Rx_byte == 0x0d){
            spi_cnt = 0x40;
        }else{
            RxBuf[spi_cnt] = Rx_byte; //注意，首字会在这个数组里 
            spi_cnt  ++;  //地址+1 
            if((spi_cnt >= 7)||(RxBuf[0] != 0xfa)) //包满归零    
            { 
              memset(&RxBuf,0,sizeof(RxBuf));
              spi_cnt=0; 
              SPI_SLAVE_SendByte(0x12);//设置下一轮发送的首字节0x12 
            } 
        }
      }
    }
  } 
}

static unsigned char RevComplete(void)
{
  if(spi_cnt & 0x80){
     spi_cnt = 0x00;
     return 1;
  }else{
     return 0;
  } 
}

void Spi_Handle(void)
{
     static unsigned char CntsTemp;
     if(RevComplete()){
         MyData = Get32Bit(RxBuf[2],RxBuf[3]);
         memset(&RxBuf,0,sizeof(RxBuf));
     }
     switch (MyData)
     {
         case 0x1101:
         ++ CntsTemp;
         if(CntsTemp & 0x01){
            LED_SET(1);
         }else{
            LED_SET(0);
         }
         break;
         case 0x1102:
         LED_SET(0);
         break;
         default:

         break;
     }
}













