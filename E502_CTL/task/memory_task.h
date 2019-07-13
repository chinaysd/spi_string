#ifndef TASK_MEMORY_H_
#define TASK_MEMORY_H_

#include "hal_flash.h"



/**
	@brief:event id
*/
#define EVNET_BACK_MEMORY_A								(0X0001)
#define EVNET_BACK_MEMORY_B								(0X0002)
#define EVNET_BACK_MEMORY_C								(0X0004)
#define EVNET_MEMORY_A_POSIT								(0X0008)
#define EVNET_MEMORY_B_POSIT								(0X0010)
#define EVNET_MEMORY_C_POSIT								(0X0020)

unsigned char Memory_TaskInit(unsigned char task_id);


unsigned short Memory_TaskProcessEvent(unsigned char task_id,unsigned short events);


unsigned char Memory_TaskGetID(void);

#endif