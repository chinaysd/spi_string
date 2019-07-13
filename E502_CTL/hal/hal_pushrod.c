#include "hal_pushrod.h"
#include "port_pushrod.h"
#include "sys_config.h"

typedef enum{
	PUSH_STOP = 0,
	PUSH_OPEN,
	PUSH_CLOSE
}Push_Status_t;

typedef struct{
	Object_t parent;
	#ifdef PUSHROD_REVERSE_SWITCH_FUNC
	unsigned char ReverseFlag:1;
	#endif
}Push_Obj_t;

static Push_Obj_t Push_Obj[PUSHROD_SUM]; 

#ifdef PUSHROD_REVERSE_SWITCH_FUNC
static unsigned char _Hal_PushrodSetReverseFlag(unsigned char id,unsigned char flag){
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	Push_Obj[id].ReverseFlag = flag;
	return SUCCEED;
}
#endif

#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
static unsigned char _Hal_PushrodGetRunFlag(unsigned char id,unsigned char *flag){
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	*flag = (Push_Obj[id].parent.sta != PUSH_STOP);
	return SUCCEED;
}
#endif

static unsigned char _Hal_PushrodOpen(unsigned char id)
{
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	
	#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
		Push_Obj[id].parent.sta = PUSH_OPEN;
	#endif
	
	if(Prot_PushrodOpen(Push_Obj[id].parent.id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

static unsigned char _Hal_PushrodClose(unsigned char id)
{
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	
	#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
		Push_Obj[id].parent.sta = PUSH_CLOSE;
	#endif
	
	if(Prot_PushrodClose(Push_Obj[id].parent.id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

static unsigned char _Hal_PushrodStop(unsigned char id)
{
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	
	#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
		Push_Obj[id].parent.sta = PUSH_STOP;
	#endif
	
	if(Prot_PushrodStop(Push_Obj[id].parent.id) == id)
		return SUCCEED;
	else 	
		return SET_ERROR;
}

unsigned char Hal_PushrodInit(unsigned char sum)
{
	unsigned char i =0;
	if(sum > PUSHROD_SUM)
		return PARA_ERROR;

	for(i = 0;i < sum;i ++){
		if( i != Port_PushrodInit(i))
			break;
		Push_Obj[i].parent.id = i;
		#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
		Push_Obj[i].parent.sta = FALSE;
		#endif
		Push_Obj[i].parent.sta = PUSH_STOP;
	}	
	
	if(i != sum )
		return PARA_ERROR;
	return SUCCEED;
}

unsigned char Hal_PushrodControl(unsigned char id,unsigned char cmd,void *arg)
{
	if(id > PUSHROD_SUM)
		return PARA_ERROR ;
	switch(cmd){
		case PUSHROD_CMD_STOP:{
			return _Hal_PushrodStop(id);
		}

		case PUSHROD_CMD_OPEN:{
			return _Hal_PushrodOpen(id);
		}

		case PUSHROD_CMD_CLOSE:{
			return _Hal_PushrodClose(id);
		}
		
		#ifdef PUSHROD_REVERSE_SWITCH_FUNC
		case PUSHROD_CMD_SET_REVERSE:{
			unsigned char set = *(unsigned char*)arg;
			return _Hal_PushrodSetReverseFlag(id, set);
		}
		#endif

		#ifdef PUSHROD_GET_RUNNING_STATUS_FUNC
		case PUSHROD_CMD_GET_RUN_STA:{
			return _Hal_PushrodGetRunFlag(id, (unsigned char *)arg);
		}
		#endif
		
		default:
			return PARA_ERROR;
	}
}
