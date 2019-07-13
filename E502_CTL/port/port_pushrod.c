#include "port_pushrod.h"

unsigned char Port_PushrodInit(unsigned char id)
{
	if(id == 0){
		GPIO_Init(GPIOC, (GPIO_PIN_7 | GPIO_PIN_6 ), GPIO_MODE_OUT_PP_HIGH_FAST); 
		Set_Push1A_Out(0);
		Set_Push1B_Out(0);
		return id;
	}else if(id == 1){
		GPIO_Init(GPIOC, (GPIO_PIN_5 | GPIO_PIN_4 ), GPIO_MODE_OUT_PP_HIGH_FAST); 
		Set_Push2A_Out(0);
		Set_Push2B_Out(0);
		return id;
	}else if(id == 2){
                GPIO_Init(GPIOC, (GPIO_PIN_3 | GPIO_PIN_2 ), GPIO_MODE_OUT_PP_HIGH_FAST); 
		Set_Push3A_Out(0);
		Set_Push3B_Out(0);
		return id;
        }
	return 0XFF;
}

unsigned char Prot_PushrodOpen(unsigned char id)
{
	if(id == 0){
		Set_Push1A_Out(1);
		Set_Push1B_Out(0);
		return id;
	}else if(id == 1){
		Set_Push2A_Out(1);
		Set_Push2B_Out(0);
		return id;
	}else if(id == 2){
		Set_Push3A_Out(1);
		Set_Push3B_Out(0);
		return id;        
        }
	return 0XFF;
}

unsigned char Prot_PushrodClose(unsigned char id)
{
	if(id == 0){
		Set_Push1A_Out(0);
		Set_Push1B_Out(1);
		return id;
	}else if(id == 1){
		Set_Push2A_Out(0);
		Set_Push2B_Out(1);
		return id;
	}else if(id == 2){
		Set_Push3A_Out(0);
		Set_Push3B_Out(1);
		return id;        
        }
	return 0XFF;
}

unsigned char Prot_PushrodStop(unsigned char id)
{
	if(id == 0){
		Set_Push1A_Out(0);
		Set_Push1B_Out(0);
		return id;
	}else if(id == 1){
		Set_Push2A_Out(0);
		Set_Push2B_Out(0);
		return id;
	}else if(id == 2){
		Set_Push3A_Out(0);
		Set_Push3B_Out(0);
		return id;        
        }
	return 0XFF;
}


