#ifndef HAL_FLASH_H_
#define HAL_FLASH_H_


/**
	@function: The number of the push rod
*/
#define Memory_SUM										(6)

/*
	@function :get push rod running status 
*/
//#define PUSHROD_GET_RUNNING_STATUS_FUNC

/*
	@function: reverse switch(defaults to shut down)
	@brief: can use a switch ,to control the push rod reverse
*/
//#define PUSHROD_REVERSE_SWITCH_FUNC	

/**
	@brief:push rod id
*/
#define BACK_MEMORY_A										(0)
#define BACK_MEMORY_B										(1)
#define BACK_MEMORY_C										(2)
#define MEMORY_A_POSIT									        (3)
#define MEMORY_B_POSIT									        (4)
#define MEMORY_C_POSIT									        (5)

//typedef enum{	
//	PUSHROD_CMD_STOP = 0,
//	PUSHROD_CMD_OPEN,
//	PUSHROD_CMD_CLOSE,
//	PUSHROD_CMD_SET_REVERSE,
//	PUSHROD_CMD_GET_RUN_STA,
//}Pushrod_Cmd_t;

unsigned char Hal_MemoryInit(unsigned char sum);

unsigned char Hal_MemoryControl(unsigned char id);

#endif