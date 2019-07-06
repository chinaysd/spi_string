#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "stm8s_conf.h"
#include "bsp_spi.h"
#include "TimeOut.h"
#include "bsp_timer.h"
#include "bsp_led.h"








void System_Init(void);
void System_Handle(void);

#endif
