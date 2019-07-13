#include "osal_tasks.h"
#include <string.h>

#include "sys_config.h"
#include "pushrod_task.h"
#include "memory_task.h"
#include "app_task.h"


pTaskEventHandlerFn tasksArr[] =
{
	Pushrod_TaskProcessEvent,
        Memory_TaskProcessEvent,
	App_TaskProcessEvent,
};

u8 tasksCnt;
u16 tasksEvents[sizeof(tasksArr) /sizeof(tasksArr[0])];

void OSAL_InitTasks( void )
{
	u8 taskID = 0;
	tasksCnt = sizeof(tasksArr) /sizeof(tasksArr[0]);
	memset( tasksEvents, 0, sizeof(tasksEvents));

	Pushrod_TaskInit(taskID ++);
        Memory_TaskInit(taskID ++);
	App_TaskInit(taskID );
}

