#ifndef PORT_PUSHROD_H_
#define PORT_PUSHROD_H_

#include "stm8s.h"
#include "data_type.h"
//#include "sys_config.h"

/**
	@brief:port layer
*/

#define PUSH1A_PIN				P21
#define PUSH1B_PIN				P20
#define PUSH2A_PIN				P27
#define PUSH2B_PIN				P13

#define Set_Push1A_Out(X)			((X)?(GPIO_WriteHigh(GPIOC, GPIO_PIN_7)):(GPIO_WriteLow(GPIOB, GPIO_PIN_7)))	
#define Set_Push1B_Out(X)			((X)?(GPIO_WriteHigh(GPIOC, GPIO_PIN_6)):(GPIO_WriteLow(GPIOB, GPIO_PIN_6)))	
#define Set_Push2A_Out(X)			((X)?(GPIO_WriteHigh(GPIOC, GPIO_PIN_5)):(GPIO_WriteLow(GPIOB, GPIO_PIN_5)))	
#define Set_Push2B_Out(X)			((X)?(GPIO_WriteHigh(GPIOC, GPIO_PIN_4)):(GPIO_WriteLow(GPIOB, GPIO_PIN_4)))	
#define Set_Push3A_Out(X)			((X)?(GPIO_WriteHigh(GPIOC, GPIO_PIN_3)):(GPIO_WriteLow(GPIOB, GPIO_PIN_3)))	
#define Set_Push3B_Out(X)			((X)?(GPIO_WriteHigh(GPIOC, GPIO_PIN_2)):(GPIO_WriteLow(GPIOB, GPIO_PIN_2)))










unsigned char Port_PushrodInit(unsigned char id);

unsigned char Prot_PushrodOpen(unsigned char id);

unsigned char Prot_PushrodClose(unsigned char id);

unsigned char Prot_PushrodStop(unsigned char id);


#endif

