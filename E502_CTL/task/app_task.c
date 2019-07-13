#include "app_task.h"
#include "pushrod_task.h"
#include "memory_task.h"
#include "hal_init.h"
#include "sys_config.h"
#include "port_flash.h"
#include "timeout.h"

#include "OSAL.h"
#include "osal_timer.h"

#include <string.h>
#include <stdlib.h>

//static unsigned char App_TaskID;
App_Obj_t App_Obj;

static void App_UartRxHandle(void)
{
	App_Obj.rev_buf.buf[App_Obj.rev_buf.len ++] = UART1->DR;
	
	if(App_Obj.rev_buf.buf[0] != START_FIELD){
		App_Obj.rev_buf.len = 0;
		App_Obj.get_key = 0;
		return ;
	}
	
	if(App_Obj.rev_buf.len >= (BUF_SIZE)){
		
		if(App_Obj.rev_buf.buf[1] != MSG_ID){
			App_Obj.rev_buf.len = 0;
			App_Obj.get_key = 0;
			return ;
		}

		if(App_Obj.rev_buf.buf[5] != 0xfb){
			App_Obj.rev_buf.len = 0;
			App_Obj.get_key = 0;
			return ;
		}
		
		if(App_Obj.rev_buf.buf[4] != (App_Obj.rev_buf.buf[0] + App_Obj.rev_buf.buf[1] + App_Obj.rev_buf.buf[2] + App_Obj.rev_buf.buf[3])){
			App_Obj.rev_buf.len = 0;
			App_Obj.get_key = 0;
			return ;
		}

		App_Obj.get_key = App_Obj.rev_buf.buf[3];	
		App_Obj.rev_buf.len = 0;
//		osal_set_event(App_TaskID, EVENT_REV_MSG);
	}
}

//static void TimeHandle(void)
//{
//	OSAL_TimerUpdata();
//}
//
//static void Pushrod_HeadCloseHandle(void)
//{
//	#ifdef PUSHROD_HEAD_FUNC_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_A_CLOSE);
//	#endif
//}
//
//static void Pushrod_HeadOpenHandle(void)
//{
//	#ifdef PUSHROD_HEAD_FUNC_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_A_OPEN);
//	#endif
//}
//
//static void Pushrod_LumbarCloseHandle(void)
//{	
//	#ifdef PUSHROD_LUMBAR_FUNC_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_B_CLOSE);		
//	#endif
//}
//
//static void Pushrod_LumbarOpenHandle(void)
//{	
//	#ifdef PUSHROD_LUMBAR_FUNC_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_B_OPEN);	
//	#endif
//}
//
//static void Pushrod_SitCloseHandle(void)
//{	
//	#ifdef PUSHROD_SIT_FUNC_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_C_CLOSE);		
//	#endif
//}
//
//static void Pushrod_SitOpenHandle(void)
//{	
//	#ifdef PUSHROD_SIT_FUNC_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_C_OPEN);	
//	#endif
//}
//
//static void Pushrod_ResetHandle(void)
//{
//	osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_STOP);	
//	OSAL_StopTimer(App_TaskID,EVENT_RESET_MSG);
//	OSAL_StartTimer(App_TaskID,EVENT_RESET_MSG,LONG_PRESS_VALUE,OSAL_TIMER_FLAG_ONE_SHOT);
//	App_Obj.reset_det_flag = TRUE;
//}
//
//static void Back_Memory_A_Handle(void)
//{	
//	#ifdef Back_Memory_A_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Memory_TaskGetID(),EVNET_BACK_MEMORY_A);	
//	#endif
//}
//
//static void Back_Memory_B_Handle(void)
//{	
//	#ifdef Back_Memory_B_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Memory_TaskGetID(),EVNET_BACK_MEMORY_B);	
//	#endif
//}
//
//static void Back_Memory_C_Handle(void)
//{	
//	#ifdef Back_Memory_C_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Memory_TaskGetID(),EVNET_BACK_MEMORY_C);	
//	#endif
//}
//
//static void Memory_A_PositHandle(void)
//{	
//	#ifdef Memory_A_Posit_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Memory_TaskGetID(),EVNET_MEMORY_A_POSIT);	
//	#endif
//}
//
//static void Memory_B_PositHandle(void)
//{	
//	#ifdef Memory_B_Posit_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Memory_TaskGetID(),EVNET_MEMORY_B_POSIT);	
//	#endif
//}
//
//static void Memory_C_PositHandle(void)
//{	
//	#ifdef Memory_C_Posit_ENABLE
//	OSAL_ReStartTime(App_TaskID, EVENT_SYS_AUTO_CLS_MSG);
//	osal_set_event(Memory_TaskGetID(),EVNET_MEMORY_C_POSIT);	
//	#endif
//}
//
//static void Light_Handle(void)
//{
//	App_Obj.led_sta = !App_Obj.led_sta;
//	if(App_Obj.led_sta){
//		LIGHT_PORT_OPEN;
//		OSAL_StartTimer(App_TaskID, EVENT_LIGHT_AUTO_CLS_MSG,LIGHT_AUTO_CLOSE,OSAL_TIMER_FLAG_ONE_SHOT);
//	}else{
//		LIGHT_PORT_CLOSE;
//		OSAL_StopTimer(App_TaskID, EVENT_LIGHT_AUTO_CLS_MSG);
//	}
//}


void Key_Handle(void){
	switch(App_Obj.get_key){
		case KEY1_VALUE:{
			if(App_Obj.cur_key != KEY1_VALUE){
				App_Obj.cur_key = KEY1_VALUE;
				/*key handle*/
				Hal_PushrodControl(PUSHROD_B,PUSHROD_CMD_CLOSE,0);
			}
			break;
		} 
		case KEY2_VALUE:{
			if(App_Obj.cur_key != KEY2_VALUE){
				App_Obj.cur_key = KEY2_VALUE;
				/*key handle*/
				Hal_PushrodControl(PUSHROD_A,PUSHROD_CMD_CLOSE,0);
			}
			break;
		}
		case KEY3_VALUE:{
			if(App_Obj.cur_key != KEY3_VALUE){
				App_Obj.cur_key = KEY3_VALUE;
				/*key handle*/
				Hal_PushrodControl(PUSHROD_A,PUSHROD_CMD_OPEN,0);	
			}
			break;
		}
		case KEY4_VALUE:{
			if(App_Obj.cur_key != KEY4_VALUE){
				App_Obj.cur_key = KEY4_VALUE;
				/*key handle*/		
				Hal_PushrodControl(PUSHROD_B,PUSHROD_CMD_OPEN,0);	
			}
			break;
		}                                           
		case KEY5_VALUE:{
			if(App_Obj.cur_key != KEY5_VALUE){
				App_Obj.cur_key = KEY5_VALUE;
				/*key handle*/
                                Hal_PushrodControl(PUSHROD_A,PUSHROD_CMD_STOP,0);
                                Hal_PushrodControl(PUSHROD_B,PUSHROD_CMD_STOP,0);
                                Hal_PushrodControl(PUSHROD_C,PUSHROD_CMD_STOP,0);
			}
			break;
		}
		case KEY6_VALUE:{
			if(App_Obj.cur_key != KEY6_VALUE){
				App_Obj.cur_key = KEY6_VALUE;
				/*key handle*/
				Hal_PushrodControl(PUSHROD_C,PUSHROD_CMD_OPEN,0);
			}
			break;
		}                
		case KEY7_VALUE:{
			if(App_Obj.cur_key != KEY7_VALUE){
				App_Obj.cur_key = KEY7_VALUE;
				/*key handle*/
				Hal_PushrodControl(PUSHROD_C,PUSHROD_CMD_CLOSE,0);
			}
			break;
		}                

		case KEY8_VALUE:{
			if(App_Obj.cur_key != KEY8_VALUE){
				App_Obj.cur_key = KEY8_VALUE;
				/*key handle*/
				Hal_MemoryControl(BACK_MEMORY_A);
			}
			break;
		}
		case KEY9_VALUE:{
			if(App_Obj.cur_key != KEY9_VALUE){
				App_Obj.cur_key = KEY9_VALUE;
				/*key handle*/
				Hal_MemoryControl(BACK_MEMORY_B);
			}
			break;
		}
		case KEY10_VALUE:{
			if(App_Obj.cur_key != KEY10_VALUE){
				App_Obj.cur_key = KEY10_VALUE;
				/*key handle*/		
				Hal_MemoryControl(BACK_MEMORY_C);
			}
			break;
		}                                           
		case KEY11_VALUE:{
			if(App_Obj.cur_key != KEY11_VALUE){
				App_Obj.cur_key = KEY11_VALUE;
				/*key handle*/
				Hal_MemoryControl(MEMORY_A_POSIT);
			}
			break;
		}
		case KEY12_VALUE:{
			if(App_Obj.cur_key != KEY12_VALUE){
				App_Obj.cur_key = KEY12_VALUE;
				/*key handle*/
				Hal_MemoryControl(MEMORY_B_POSIT);
			}
			break;
		}                
		case KEY13_VALUE:{
			if(App_Obj.cur_key != KEY13_VALUE){
				App_Obj.cur_key = KEY13_VALUE;
				/*key handle*/
				Hal_MemoryControl(MEMORY_C_POSIT);
			}
			break;
		}                                
                
		default:{
//			if(App_Obj.cur_key){
//				App_Obj.cur_key = 0;
//				#ifdef PUSHROD_FUNC_ENABLE
//					osal_set_event(Pushrod_TaskGetID(),EVNET_PUSHROD_STOP);
//				#endif
//				if(App_Obj.reset_det_flag){
//					App_Obj.reset_det_flag = FALSE;
//					OSAL_StopTimer(App_TaskID,EVENT_RESET_MSG);	
//					#ifdef LED_FUNC_ENABLE
//						Light_Handle();
//					#endif
//				}
//			}
			break;
		}
	}
}

unsigned char App_TaskInit(void)
{
//	App_TaskID = task_id;	
	memset(&App_Obj,0,sizeof(App_Obj_t));	
	
	Hal_RegUartRxHdl(UART0_ID,App_UartRxHandle);
//	Hal_RegTimeHdl(TimeHandle);
        TimeOutDet_Init();
        Detect_Port();
        Read_position_data();
        Read_current_position();
        
//	GPIO_Init(GPIOB, GPIO_PIN_5 , GPIO_MODE_OUT_PP_HIGH_FAST);
// 	OSAL_StartTimer(App_TaskID, EVENT_FAULT_ERROR_MSG,FATAL_ERROR_TIME,OSAL_TIMER_FLAG_ONE_SHOT);
	return SUCCEED;
}

//unsigned short App_TaskProcessEvent(unsigned char task_id,unsigned short events)
//{	
//	(void)task_id;
//	if(events & EVENT_REV_MSG){			
//		OSAL_ReStartTime(App_TaskID, EVENT_FAULT_ERROR_MSG);
//		Key_Handle();
//		return (events ^ EVENT_REV_MSG);
//	}
//
//	if(events & EVENT_RESET_MSG){
//		App_Obj.reset_det_flag = FALSE;
//		osal_set_event(Pushrod_TaskGetID(), EVNET_PUSHROD_B_CLOSE);
//		OSAL_StopTimer(Pushrod_TaskGetID(), EVNET_PUSHROD_A_CLOSE);
//		OSAL_StartTimer(Pushrod_TaskGetID(), EVNET_PUSHROD_A_CLOSE, 100,OSAL_TIMER_FLAG_ONE_SHOT);
//		return (events ^ EVENT_RESET_MSG);
//	}
//
//	if(events & EVENT_LIGHT_AUTO_CLS_MSG){
//		Light_Handle();
//		return events ^ EVENT_LIGHT_AUTO_CLS_MSG;
//	}
//	
//	if(events & EVENT_FAULT_ERROR_MSG){
//		while(1);	/*WDT reset*/
//	}
//	return 0;
//}
