#include "system.h"
#include "string.h"

 
void System_Init(void)
{
     CS_Init();
     Led_Init();
     Spi_Init();
}

void System_Handle(void)
{
     RevProcessHandle();
     Spi_Handle();
}
