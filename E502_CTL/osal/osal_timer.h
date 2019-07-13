#ifndef OSAL_TIMER_H_
#define OSAL_TIMER_H_

#include "sys_config.h"

/**
	@brief:The maximum number of timers running simultaneously(Set up as needed)
*/
#define MAX_TIMER_NUM										15

/* timer flag*/
#define OSAL_TIMER_FLAG_DEACTIVATED       						0x0             			/**< timer is deactive */
#define OSAL_TIMER_FLAG_ACTIVATED         						0x1           			/**< timer is active */
#define OSAL_TIMER_FLAG_ONE_SHOT         						0x0             			/**< one shot timer */
#define OSAL_TIMER_FLAG_PERIODIC          						0x2            			/**< periodic timer *

/*function options*/
//#define OSAL_GET_TIME_STA_FUNC_ENABLE











/*****************************************************************************
 * Function	  : OSAL_TimerInit
 * Description   : The timer is initialized and must be called during the initialization phase!
 * Input           : void  
 * Output		  : None
 * Return		  : 
 * Others		  : 
 * Record
 * 1.Date		  : 20180711
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
void OSAL_TimerInit(void);

/*****************************************************************************
 * Function	  : OSAL_StartTimer
 * Description   : Start a timer that sends a message to the task when it arrives(The timer is not overloaded)
 * Input           : uint8 task_id : task id        
			    uint16 event_id : event id      
			    uint32 timeout_value  :timeout 
			    uint8 flag: @see timer flag
 * Output		  : None
 * Return		  : SUCCESS->OK,otherwise failed
 * Others		  : 
 * Record
 * 1.Date		  : 20180711
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
u8 OSAL_StartTimer(const u8 task_id, const u16 event_id,const u32 timeout_value ,const u8 flag);

/*****************************************************************************
 * Function	  : OSAL_ReStartTime
 * Description   : Restart the specified timer(It must have been called OSAL_StartTimer before)
 * Input           : uint8 task_id : task id          
			    uint16 event_id : event id       
 * Output		  : None
 * Return		  : SUCCESS->OK,otherwise failed
 * Others		  : 
 * Record
 * 1.Date		  : 20180711
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
u8 OSAL_ReStartTime(const u8 task_id,const u16 event_id);

/*****************************************************************************
 * Function	  : OSAL_StartrReloadTimer
 * Description   : Start a timer that sends a message to the task when it arrives(The timer is overloaded)
 * Input           : uint8 task_id : task id        
			    uint16 event_id : event id      
			    uint32 timeout_value  :timeout 
 * Output		  : None
 * Return		  : SUCCESS->OK,otherwise failed
 * Others		  : 
 * Record
 * 1.Date		  : 20180711
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
#ifdef OSAL_RELOAD_TIME_FUNC
u8 OSAL_StartrReloadTimer(const u8 task_id,const u16 event_id,const u32 timeout_value );
#endif
/*****************************************************************************
 * Function	  : OSAL_StopTimer
 * Description   : Stop specifying the timer 
 * Input           : uint8 task_id : task id       
			    uint16 event_id : event id
 * Output		  : None
 * Return		  : SUCCESS->OK,otherwise faileda
 * Others		  : 
 * Record
 * 1.Date		  : 20180711
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
u8 OSAL_StopTimer(const u8 task_id,const u16 event_id);

/*****************************************************************************
 * Function	  : OSAL_GetTimerSta
 * Description   : Gets the running state of the timer 
 * Input           : uint8 task_id : task id       
			    uint16 event_id : event id
 * Output		  : None
 * Return		  : TRUE->Run,otherwise not
 * Others		  : 
 * Record
 * 1.Date		  : 20180713
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
#ifdef OSAL_GET_TIME_STA_FUNC
u8 OSAL_GetTimerSta(const u8 task_id,const u16 event_id);
#endif

/*****************************************************************************
 * Function	  : OSAL_TimerUpdata
 * Description   : Update timer,It must be executed in a timer(Time base 1 ms) 
 * Input           : void  
 * Output		  : None
 * Return		  : 
 * Others		  : 
 * Record
 * 1.Date		  : 20180711
 *   Author       : marco_zhou
 *   Modification: Created function

*****************************************************************************/
void OSAL_TimerUpdata(void);

#endif

