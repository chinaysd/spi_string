#include "osal_timer.h"
#include "OSAL.H"
#include "comdef.h"
#include <string.h>

typedef struct{
	u8 flag:1;
	u8 task_id:7;
	u16 event_id;
	u32 base_cnt,time_out;
}OSAL_Timer_t;

static OSAL_Timer_t OSAL_Timer[MAX_TIMER_NUM];

void OSAL_TimerInit(void)
{
	memset(OSAL_Timer,0,sizeof(OSAL_Timer));
}

u8 OSAL_StartTimer(const u8 task_id, const u16 event_id,const u32 timeout_value ,const u8 flag)
{
	int i;
	for(i = 0; i < MAX_TIMER_NUM;i ++){
		if(!(OSAL_Timer[i].flag & OSAL_TIMER_FLAG_ACTIVATED)){
			OSAL_Timer[i].flag = flag|OSAL_TIMER_FLAG_ACTIVATED;
			OSAL_Timer[i].base_cnt = 0;
			OSAL_Timer[i].event_id = event_id;
			OSAL_Timer[i].task_id = task_id;
			OSAL_Timer[i].time_out = timeout_value;
			return SUCCESING;
		}
	}
	return FAILURE;
}

u8 OSAL_ReStartTime(const u8 task_id, const u16 event_id)
{	
	int i;
	for(i = 0; i < MAX_TIMER_NUM;i ++){
		if(OSAL_Timer[i].flag & OSAL_TIMER_FLAG_ACTIVATED){
			if((OSAL_Timer[i].task_id == task_id) && (OSAL_Timer[i].event_id == event_id)){
				OSAL_Timer[i].base_cnt = 0;				
				return SUCCESING;
			}
		}
	}	
	return FAILURE;
}

u8 OSAL_StopTimer(const u8 task_id,const u16 event_id)
{
	int i;
	for(i = 0; i < MAX_TIMER_NUM;i ++){
		if((OSAL_Timer[i].flag & OSAL_TIMER_FLAG_ACTIVATED) && (OSAL_Timer[i].task_id == task_id) && (OSAL_Timer[i].event_id == event_id)){
			OSAL_Timer[i].flag &= ~OSAL_TIMER_FLAG_ACTIVATED;
			OSAL_Timer[i].base_cnt = 0;
			OSAL_Timer[i].event_id = 0;
			OSAL_Timer[i].task_id = 0;
			OSAL_Timer[i].time_out = 0;
			return SUCCESING;
		}
	}	
	return FAILURE;
}

#ifdef OSAL_GET_TIME_STA_FUNC_ENABLE
u8 OSAL_GetTimerSta(const u8 task_id,const u16 event_id)
{
	int i;
	for(i = 0; i < MAX_TIMER_NUM;i ++){
		if((OSAL_Timer[i].flag & OSAL_TIMER_FLAG_ACTIVATED) && (OSAL_Timer[i].task_id == task_id) && (OSAL_Timer[i].event_id == event_id)){
			return TRUE;
		}
	}	
	return FALSE;
}
#endif

void OSAL_TimerUpdata(void)
{
	int i;
	for(i = 0; i < MAX_TIMER_NUM;i ++){
		if(OSAL_Timer[i].flag & OSAL_TIMER_FLAG_ACTIVATED){
			if(OSAL_Timer[i].base_cnt ++ > OSAL_Timer[i].time_out){
 				if(OSAL_Timer[i].flag & OSAL_TIMER_FLAG_PERIODIC){
					OSAL_Timer[i].base_cnt = 0;
				}else{
					OSAL_Timer[i].flag &= ~OSAL_TIMER_FLAG_ACTIVATED;
				}
 				osal_set_event(OSAL_Timer[i].task_id, OSAL_Timer[i].event_id);
 			}
		}
	}
}

