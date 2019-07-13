#include "hal_heat_cool.h"
#include "port_heat_cool.h"

typedef struct{	
	Object_t parent;
	unsigned char sup_flag:1;
}HC_Obj_t;

static XDATA HC_Obj_t HC_Obj[HEAT_COOL_SUM];

unsigned char Hal_HeatCoolInit(unsigned char sum)
{
	int i;
	if(sum > HEAT_COOL_SUM)
		return PARA_ERROR;

	for(i = 0; i < HEAT_COOL_SUM;i ++){
		if(Port_HeatCoolInit(i) != i)
			break;
		HC_Obj[i].parent.id = i;
		HC_Obj[i].parent.mode = HC_STOP_MODE;
		HC_Obj[i].sup_flag = FALSE;
	}
	
	if(i != sum )
		return PARA_ERROR;
		
	return SUCCEED;
}

static unsigned char _Hal_HeatCoolSetCool(unsigned char id,unsigned char set)
{
	if(id > HEAT_COOL_SUM)
		return PARA_ERROR;
	
	if(set == HC_OPEN){		
		if(Port_CoolSet(id, HC_CLOSE) != id)
			return SET_ERROR;
		if(Port_HeatSet(id,HC_OPEN) != id)
			return SET_ERROR;
	}else if(set == HC_CLOSE){
		if(Port_CoolSet(id, HC_CLOSE) != id)
			return SET_ERROR;
		if(Port_HeatSet(id,HC_CLOSE) != id)
			return SET_ERROR;
	}else{
		return PARA_ERROR;
	}	
	return SUCCEED;
}

static unsigned char _Hal_HeatCoolSetHeat(unsigned char id,unsigned char set)
{	
	if(id > HEAT_COOL_SUM)
		return PARA_ERROR;
	if(set == HC_OPEN){		
		if(Port_CoolSet(id, HC_OPEN) != id)
			return SET_ERROR;
		if(Port_HeatSet(id,HC_OPEN) != id)
			return SET_ERROR;
	}else if(set == HC_CLOSE){
		if(Port_CoolSet(id, HC_CLOSE) != id)
			return SET_ERROR;
		if(Port_HeatSet(id,HC_CLOSE) != id)
			return SET_ERROR;
	}else{
		return PARA_ERROR;
	}
	return SUCCEED;
}

static unsigned char _Hal_HeatCoolSetFan(unsigned char id,unsigned char set)
{	
	if(id > HEAT_COOL_SUM)
		return PARA_ERROR;
	if(Port_FanSet(id, set) != id)
		return SET_ERROR;
	return SUCCEED;
}

static unsigned char _Hal_HeatCoolSetMode(unsigned char id,unsigned char mode)
{
	if(id > HEAT_COOL_SUM)
		return PARA_ERROR;
	HC_Obj[id].parent.mode = (HC_Mode_t)mode;
	if(mode == HC_STOP_MODE){
		HC_Obj[id].sup_flag = FALSE;
	}
	return SUCCEED;
}

static unsigned char _Hal_HeatCoolGetMode(unsigned char id,unsigned char *mode)
{	
	if(id > HEAT_COOL_SUM)
		return PARA_ERROR;
	*mode = (unsigned char)HC_Obj[id].parent.mode;
	return SUCCEED;
}
 
static unsigned char _Hal_HeatCoolSupend(unsigned char id)
{
	if(id > HEAT_COOL_SUM)
		return PARA_ERROR;
	if(HC_Obj[id].parent.mode == HC_COOL_MODE){
		HC_Obj[id].sup_flag = TRUE;
		if(_Hal_HeatCoolSetCool(id,HC_CLOSE) != id)
			return SET_ERROR;
	}
	else if(HC_Obj[id].parent.mode == HC_HEAT_MODE){
		HC_Obj[id].sup_flag = TRUE;
		if(_Hal_HeatCoolSetHeat(id, HC_CLOSE) != id)
			return SET_ERROR;
	}
	else{
		return SUCCEED;
	}
	return SUCCEED;
}

static unsigned char _Hal_HeatCoolGetSupSta(unsigned char id,unsigned char *sta)
{
	if(id > HEAT_COOL_SUM)
		return PARA_ERROR;
	*sta = HC_Obj[id].sup_flag;
	return SUCCEED;
}

static unsigned char _Hal_HeatCoolResume(unsigned char id)
{
	if(id > HEAT_COOL_SUM)
		return PARA_ERROR;
	if(HC_Obj[id].parent.mode == HC_COOL_MODE){
		if(HC_Obj[id].sup_flag){
			HC_Obj[id].sup_flag = FALSE;
			if(_Hal_HeatCoolSetCool(id,HC_OPEN) != id)
				return SET_ERROR;
		}
	}
	else if(HC_Obj[id].parent.mode == HC_HEAT_MODE){
		if(HC_Obj[id].sup_flag){
			HC_Obj[id].sup_flag = FALSE;
			if(_Hal_HeatCoolSetHeat(id, HC_OPEN) != id)
				return SET_ERROR;
		}
	}
	else{
		return SUCCEED;
	}
	return SUCCEED;
}

unsigned char Hal_HeatCoolControl(unsigned char id,unsigned char cmd,void *arg)
{
	if(id > HEAT_COOL_SUM)
		return PARA_ERROR;

	switch(cmd){
		case HC_CMD_SET_COOL:{
			unsigned char set = *(unsigned char*)arg;
			return _Hal_HeatCoolSetCool(id, set);
		}

		case HC_CMD_SET_HEAT:{
			unsigned char set = *(unsigned char*)arg;
			return _Hal_HeatCoolSetHeat(id, set);
		}

		case HC_CMD_SET_FAN:{
			unsigned char set = *(unsigned char*)arg;
			return _Hal_HeatCoolSetFan(id, set);
		}

		case HC_CMD_GET_MODE:{
			return _Hal_HeatCoolGetMode(id, (unsigned char *)arg);
		}

		case HC_CMD_SET_MODE:{
			unsigned char mode = *(unsigned char*)arg;
			return _Hal_HeatCoolSetMode(id, mode);
		}

		case HC_CMD_SUPEND:{
			return _Hal_HeatCoolSupend(id);
		}

		case HC_CMD_RESUME:{
			return _Hal_HeatCoolResume(id);
		}

		case HC_CMD_GET_SUPED_STA:{
			return _Hal_HeatCoolGetSupSta(id, (unsigned char *)arg);
		}
		
		default:
			return PARA_ERROR;
	}
}
