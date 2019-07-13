#include "memory_task.h"
#include "sys_config.h"
#include "stm8s.h"

static unsigned char Memory_TaskID;

unsigned char Memory_TaskInit(unsigned char task_id)
{
	Memory_TaskID = task_id;
	return TRUE;
}

unsigned short Memory_TaskProcessEvent(unsigned char task_id,unsigned short events)
{
	(void) task_id;

	if(events & EVNET_BACK_MEMORY_A){
		Hal_MemoryControl(BACK_MEMORY_A);
		return (events ^ EVNET_BACK_MEMORY_A);
	}

	if(events & EVNET_BACK_MEMORY_B){
		Hal_MemoryControl(BACK_MEMORY_B);
		return (events ^ EVNET_BACK_MEMORY_B);
	}

	if(events & EVNET_BACK_MEMORY_C){
		Hal_MemoryControl(BACK_MEMORY_C);
		return (events ^ EVNET_BACK_MEMORY_C);
	}

	if(events & EVNET_MEMORY_A_POSIT){
		Hal_MemoryControl(MEMORY_A_POSIT);
		return (events ^ EVNET_MEMORY_A_POSIT);
	}
	if(events & EVNET_MEMORY_B_POSIT){
		Hal_MemoryControl(MEMORY_B_POSIT);
		return (events ^ EVNET_MEMORY_B_POSIT);
	}

	if(events & EVNET_MEMORY_C_POSIT){
		Hal_MemoryControl(MEMORY_C_POSIT);
		return (events ^ EVNET_MEMORY_C_POSIT);
	}        
	
	return 0;
}

unsigned char Memory_TaskGetID(void)
{
	return Memory_TaskID;
}