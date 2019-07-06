#include "system.h"
#include "string.h"

unsigned int MyData;
extern u8 RxBuf[7]; 
extern u8 spi_cnt;
 
void System_Init(void)
{
     CS_Init();
     Led_Init();
     Spi_Init();
     enableInterrupts();
}

unsigned char RevComplete(void)
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
     if(RevComplete()){
         MyData = Get32Bit(RxBuf[2],RxBuf[3]);
         memset(&RxBuf,0,sizeof(RxBuf));
     }
     switch (MyData)
     {
         case 0x1101:
         LED_SET(0);
         break;
         case 0x1102:
         LED_SET(1);
         break;
         default:

         break;
     }
}

void System_Handle(void)
{
     Spi_Handle();
}
