#ifndef PORT_FLASH_H_
#define PORT_FLASH_H_

#include "data_type.h"
#include"stm8s.h"

typedef unsigned int (*Flash_Read) (u32);
typedef void (*Flash_Write)(u32,u16);

typedef  struct __Flash{ 										//记忆位置
		unsigned int Memory_A_POTION;  
		unsigned int Memory_B_POTION;  
		unsigned int Memory_C_POTION;  
		unsigned int Memory_2A_POTION;  
		unsigned int Memory_2B_POTION;  
		unsigned int Memory_2C_POTION;  
		unsigned int Memory_3A_POTION;  
		unsigned int Memory_3B_POTION;  
		unsigned int Memory_3C_POTION;  		
    unsigned int  Moter_a_now;
    unsigned int  Moter_b_now;
    unsigned int  Moter_c_now;
    unsigned int  Memory_Moter_a_now;
    unsigned int  Memory_Moter_b_now;
    unsigned int  Memory_Moter_c_now;
    unsigned int  Moter_now_check;    
		unsigned int  Memory_Check;  		
}FLASH_DATA;

extern FLASH_DATA  Memory_data_stu;

typedef struct __Stop_flag {
    unsigned char Motor_A_stop :1;
    unsigned char Motor_B_stop :1;
    unsigned char Motor_C_stop :1;
    unsigned char Back_Memory_A_stop :1;
    unsigned char Back_Memory_B_stop :1;
    unsigned char Back_Memory_C_stop :3;
}Stop_type;

typedef struct  current_position{

//    unsigned int  Memory_A_position;
//    unsigned int  Memory_B_position;
//    unsigned int  Memory_C_position;    
    unsigned int  Max_Moter_val_A;          //最大位置值
    unsigned int  Max_Moter_val_B;
    unsigned int  Max_Moter_val_C;
    unsigned int  Back_position__A;         //回到记忆位置值
    unsigned int  Back_position__B;
    unsigned int  Back_position__C;    
}__Current_position;

extern __Current_position Current_Post;

#define  A_Port                    GPIO_ReadInputPin(GPIOA, GPIO_PIN_0) 
#define  B_Port                    GPIO_ReadInputPin(GPIOA, GPIO_PIN_2) 
#define  C_Port                    GPIO_ReadInputPin(GPIOA, GPIO_PIN_4) 
#define  Pushrod_End_Time          (unsigned int)1000


extern void Read_position_data(void);
extern void Read_current_position(void);
extern void Position_cnt(void);
extern void Detect_Port(void);
extern unsigned char Prot_Back_Memory_A(unsigned char id);
extern unsigned char Prot_Back_Memory_B(unsigned char id);
extern unsigned char Prot_Back_Memory_C(unsigned char id);
extern unsigned char Prot_Memory_A_Posit(unsigned char id);
extern unsigned char Prot_Memory_B_Posit(unsigned char id);
extern unsigned char Prot_Memory_C_Posit(unsigned char id);
extern unsigned char Port_MemoryInit(unsigned int id);
void FLASH_Initializes(void);
void FLASH_WriteNByte(u32 WriteAddr,u16 pBuffer);
unsigned int FLASH_ReadNByte(u32 ReadAddr);



#endif