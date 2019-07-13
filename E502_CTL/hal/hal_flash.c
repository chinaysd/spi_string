#include "hal_flash.h"
#include "port_flash.h"
#include "sys_config.h"

typedef enum{
	Back_Memory_A,
	Back_Memory_B,
	Back_Memory_C
}Memory_Status_t;

typedef struct{
	Object_t parent;
}Memory_Obj_t;

static Memory_Obj_t Memory_Obj[Memory_SUM]; 

static unsigned char _Hal_Back_Memory_A(unsigned char id)
{
	if(id > Memory_SUM)
		return PARA_ERROR ;
	
	if(Prot_Back_Memory_A(Memory_Obj[id].parent.id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

static unsigned char _Hal_Back_Memory_B(unsigned char id)
{
	if(id > Memory_SUM)
		return PARA_ERROR ;
	
	if(Prot_Back_Memory_B(Memory_Obj[id].parent.id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

static unsigned char _Hal_Back_Memory_C(unsigned char id)
{
	if(id > Memory_SUM)
		return PARA_ERROR ;
	
	if(Prot_Back_Memory_C(Memory_Obj[id].parent.id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

static unsigned char _Hal_Memory_A_Posit(unsigned char id)
{
	if(id > Memory_SUM)
		return PARA_ERROR ;
	
	if(Prot_Memory_A_Posit(Memory_Obj[id].parent.id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

static unsigned char _Hal_Memory_B_Posit(unsigned char id)
{
	if(id > Memory_SUM)
		return PARA_ERROR ;
	
	if(Prot_Memory_B_Posit(Memory_Obj[id].parent.id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

static unsigned char _Hal_Memory_C_Posit(unsigned char id)
{
	if(id > Memory_SUM)
		return PARA_ERROR ;
	
	if(Prot_Memory_C_Posit(Memory_Obj[id].parent.id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

unsigned char Hal_MemoryInit(unsigned char sum)
{
	unsigned char i =0;

	for(i = 0;i < sum;i ++){
		if( i != Port_MemoryInit(i))
			break;
	}		
	if(i != sum )
		return PARA_ERROR;
	return SUCCEED;
}

unsigned char Hal_MemoryControl(unsigned char id)
{
	switch(id){
		case BACK_MEMORY_A:{
			return _Hal_Back_Memory_A(id);
		}

		case BACK_MEMORY_B:{
			return _Hal_Back_Memory_B(id);
		}

		case BACK_MEMORY_C:{
			return _Hal_Back_Memory_C(id);
		}
		case MEMORY_A_POSIT:{
			return _Hal_Memory_A_Posit(id);
		}

		case MEMORY_B_POSIT:{
			return _Hal_Memory_B_Posit(id);
		}

		case MEMORY_C_POSIT:{
			return _Hal_Memory_C_Posit(id);
		}		
		default:
			return PARA_ERROR;
	}
}