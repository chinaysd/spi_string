#ifndef APP_TASK_H_
#define APP_TASK_H_

#include "sys_config.h"

/**
	@brief:event id
*/
#define EVENT_REV_MSG					0X0001
#define EVENT_HEAT_AUTO_CLS_MSG			0X0002
#define EVENT_COOL_AUTO_CLS_MSG		0X0004
#define EVENT_WARN_AUTO_CLS_MSG		0X0008
#define EVENT_MSGE_AUTO_CLS_MSG			0X0010
#define EVENT_SYS_AUTO_CLS_MSG			0X0020
#define EVENT_KEY_LOCK_MSG				0X0040
#define EVENT_RESET_MSG					0X0080
#define EVENT_LIGHT_AUTO_CLS_MSG		0X0100
#define EVENT_FAULT_ERROR_MSG			0X8000

#define BUF_SIZE							6
#define START_FIELD						0X5A
#define MSG_ID							0X02
#define STOP_MESSAGE						0X0D0A

/**
	@brief:按键值
*/
#define KEY1_VALUE						0X01
#define KEY2_VALUE						0X02
#define KEY3_VALUE						0X03
#define KEY4_VALUE						0X04
#define KEY5_VALUE						0X05
#define KEY6_VALUE						0X06
#define KEY7_VALUE						0X07
#define KEY8_VALUE						0X08
#define KEY9_VALUE						0X09
#define KEY10_VALUE						0X0a
#define KEY11_VALUE						0X0b
#define KEY12_VALUE						0X0c
#define KEY13_VALUE						0X0d

/**
	@brief:自动关机
*/ 
#define HEAT_AUTO_CLOSE					3600000
#define WARN_AUTO_CLOSE				3600000
#define COOL_AUTO_CLOSE					7200000
#define MASS_AUTO_CLOSE					1800000
#define SYSTEM_AUTO_CLOSE				14400000	
#define LIGHT_AUTO_CLOSE					14400000
#define FATAL_ERROR_TIME					5000


/*
	@brief:After the upper machine disconnects, the lower machine protective shutdown
*/
#define LOST_CTL_VALUE					5000

#define LONG_PRESS_VALUE				1000

#define LIGHT_PORT_OPEN						GPIO_WriteHigh(GPIOB, GPIO_PIN_4)
#define LIGHT_PORT_CLOSE                                        GPIO_WriteLow(GPIOB, GPIO_PIN_4) 

#define P_STOP							0
#define P_CLOSE							1
#define P_OPEN							2

typedef struct{
	u8 buf[BUF_SIZE];
	u8 len;
}Rev_Buf_t;

typedef struct{
	Rev_Buf_t rev_buf;
	unsigned char get_key,cur_key;
	unsigned int led_sta;
	u8 reset_det_flag:1;
	unsigned char pushrod_sta[2],sw_cnt[2];
}App_Obj_t;












unsigned char App_TaskInit(void);

//unsigned short App_TaskProcessEvent(unsigned char task_id,unsigned short events);

void Key_Handle(void);



#endif

