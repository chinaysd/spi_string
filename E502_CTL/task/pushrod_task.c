#include "pushrod_task.h"
#include "sys_config.h"
#include "stm8s.h"

static unsigned char Pushrod_TaskID;

unsigned char Pushrod_TaskInit(unsigned char task_id)
{
	Pushrod_TaskID = task_id;
	return TRUE;
}

unsigned short Pushrod_TaskProcessEvent(unsigned char task_id,unsigned short events)
{
	(void) task_id;
	if(events & EVNET_PUSHROD_STOP){
		int i;
		for(i = 0; i < PUSHROD_SUM;i ++){
			Hal_PushrodControl(i,PUSHROD_CMD_STOP,0);
		}
		return (events ^ EVNET_PUSHROD_STOP);
	}

	if(events & EVNET_PUSHROD_A_OPEN){
		Hal_PushrodControl(PUSHROD_A,PUSHROD_CMD_OPEN,0);
		return (events ^ EVNET_PUSHROD_A_OPEN);
	}

	if(events & EVNET_PUSHROD_A_CLOSE){
		Hal_PushrodControl(PUSHROD_A,PUSHROD_CMD_CLOSE,0);
		return (events ^ EVNET_PUSHROD_A_CLOSE);
	}

	if(events & EVNET_PUSHROD_B_OPEN){
		Hal_PushrodControl(PUSHROD_B,PUSHROD_CMD_OPEN,0);
		return (events ^ EVNET_PUSHROD_B_OPEN);
	}

	if(events & EVNET_PUSHROD_B_CLOSE){
		Hal_PushrodControl(PUSHROD_B,PUSHROD_CMD_CLOSE,0);
		return (events ^ EVNET_PUSHROD_B_CLOSE);
	}
	if(events & EVNET_PUSHROD_C_OPEN){
		Hal_PushrodControl(PUSHROD_C,PUSHROD_CMD_OPEN,0);
		return (events ^ EVNET_PUSHROD_C_OPEN);
	}

	if(events & EVNET_PUSHROD_C_CLOSE){
		Hal_PushrodControl(PUSHROD_C,PUSHROD_CMD_CLOSE,0);
		return (events ^ EVNET_PUSHROD_C_CLOSE);
	}        
	
	return 0;
}

unsigned char Pushrod_TaskGetID(void)
{
	return Pushrod_TaskID;
}
