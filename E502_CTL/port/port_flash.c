#include "hal_flash.h"
#include "stm8s.h"
#include "port_flash.h"
#include "port_pushrod.h"
#include "app_task.h"

FLASH_DATA  Memory_data_stu;
unsigned int  Motor_A_up_test = 0;	
unsigned int  Motor_B_up_test = 0;
unsigned int  Motor_C_up_test = 0;
unsigned int  Motor_A_down_test = 0;
unsigned int  Motor_B_down_test = 0;
unsigned int  Motor_C_down_test = 0;
unsigned char return_position_A = 0 ; 
unsigned char return_position_B = 0 ; 
unsigned char return_position_C = 0 ; 

Stop_type Stop_flg = {0,0,0,0,0,0};  //推杆控制停止標誌/ 回到記憶停止標誌
__Current_position Current_Post = {0,0,0,0,0,0};   //最大位置  /回到記憶位置
extern App_Obj_t App_Obj;
  

void FLASH_Initializes(void)
{
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);  //内部FLASH初始化
}

void FLASH_WriteNByte(u32 WriteAddr,u16 pBuffer)
{
  unsigned int i;
  FLASH_Unlock(FLASH_MEMTYPE_PROG);              //解锁
  while(FLASH_GetFlagStatus(FLASH_FLAG_PUL) == RESET);
  i=pBuffer;
  FLASH_ProgramByte(WriteAddr, i);
  
  i=pBuffer>>8;
  FLASH_ProgramByte(WriteAddr+1, i);
  
  FLASH_WaitForLastOperation(FLASH_MEMTYPE_PROG);
  FLASH_Lock(FLASH_MEMTYPE_PROG);                //上锁
}

unsigned int FLASH_ReadNByte(u32 ReadAddr)
{   
    unsigned int pBuffer;
    pBuffer = FLASH_ReadByte(ReadAddr+1);
    pBuffer<<=8;
    pBuffer |= FLASH_ReadByte(ReadAddr);
    return pBuffer;
}

unsigned int Flash_Writen_pfun(unsigned int Erase_writen_adr, FLASH_DATA *p , Flash_Write Flash_Writen_fun)  //记忆位置                                  
{

  Flash_Writen_fun(Erase_writen_adr,   p->Memory_A_POTION);      
  Flash_Writen_fun(Erase_writen_adr+2, p->Memory_B_POTION);      
  Flash_Writen_fun(Erase_writen_adr+4, p->Memory_C_POTION);      
  Flash_Writen_fun(Erase_writen_adr+6, p->Memory_2A_POTION);      
  Flash_Writen_fun(Erase_writen_adr+8, p->Memory_2B_POTION);      
  Flash_Writen_fun(Erase_writen_adr+10,p->Memory_2C_POTION);      
  Flash_Writen_fun(Erase_writen_adr+12,p->Memory_3A_POTION);      
  Flash_Writen_fun(Erase_writen_adr+14,p->Memory_3B_POTION);      
  Flash_Writen_fun(Erase_writen_adr+16,p->Memory_3C_POTION);      

  return 0xff;
}

unsigned int Flash_Writen_current_position(unsigned int Erase_writen_adr       //记忆当前位置    0x0100  
                             ,FLASH_DATA *p
                             ,Flash_Write Flash_Writen_fun)
{

    Flash_Writen_fun(Erase_writen_adr,   p->Memory_Moter_a_now);      
    Flash_Writen_fun(Erase_writen_adr+2, p->Memory_Moter_b_now);      
    Flash_Writen_fun(Erase_writen_adr+4, p->Memory_Moter_c_now);      
    Flash_Writen_fun(Erase_writen_adr+6, 0XCCDD);        

    return 0xffff;
}

void Read_position_data(void)
{
  
   Memory_data_stu.Memory_A_POTION   = FLASH_ReadNByte(0x8f00);
   Memory_data_stu.Memory_B_POTION   = FLASH_ReadNByte(0x8f02);
   Memory_data_stu.Memory_C_POTION   = FLASH_ReadNByte(0x8f04);
   Memory_data_stu.Memory_2A_POTION  = FLASH_ReadNByte(0x8f06);
   Memory_data_stu.Memory_2B_POTION  = FLASH_ReadNByte(0x8f08);
   Memory_data_stu.Memory_2C_POTION  = FLASH_ReadNByte(0x8f0A);
   Memory_data_stu.Memory_3A_POTION  = FLASH_ReadNByte(0x8f0C);
   Memory_data_stu.Memory_3B_POTION  = FLASH_ReadNByte(0x8f0E);
   Memory_data_stu.Memory_3C_POTION  = FLASH_ReadNByte(0x8f10);

}

void Read_current_position(void)
{

   Memory_data_stu.Moter_now_check  = FLASH_ReadNByte(0x9f06);
   if(Memory_data_stu.Moter_now_check == 0XCCDD ){
             Memory_data_stu.Moter_a_now  = FLASH_ReadNByte(0x9f00);
             Memory_data_stu.Moter_b_now  = FLASH_ReadNByte(0x9f02);
             Memory_data_stu.Moter_c_now  = FLASH_ReadNByte(0x9f04);
    }
   else {
      Memory_data_stu.Moter_a_now  = 0;
      Memory_data_stu.Moter_b_now  = 0;
      Memory_data_stu.Moter_c_now  = 0;
      Memory_data_stu.Moter_a_now  = FLASH_ReadNByte(0x9f00);
      Memory_data_stu.Moter_b_now  = FLASH_ReadNByte(0x9f02);
      Memory_data_stu.Moter_c_now  = FLASH_ReadNByte(0x9f04);
   }

}  

static void  Stop_back_position(void){   
    Set_Push1A_Out(0);
    Set_Push1B_Out(0);  
    Set_Push2A_Out(0);
    Set_Push2B_Out(0);   
    Set_Push3A_Out(0);
    Set_Push3B_Out(0);      
    return_position_A =  0 ;                                       
    return_position_B =  0 ;                                       
    return_position_C =  0 ;      
}


void Detect_Port(void)
{
   static u8 A_port_static = 0,C_port_static = 0,B_port_static = 0;  
   
   if(App_Obj.cur_key == KEY1_VALUE)
   { 
        Stop_flg.Motor_A_stop = 1;  	
        Motor_A_up_test++;
      if((A_Port)&&(!A_port_static))      
        {            
           Memory_data_stu.Moter_a_now++; 
           Motor_A_up_test = 0 ;
        }
   }
   else if( App_Obj.cur_key == KEY2_VALUE)
     {
          Stop_flg.Motor_A_stop =1;  	
          Motor_A_down_test++;         
         if((A_Port)&&(!A_port_static))      
        {
             Motor_A_down_test= 0;
          if(Memory_data_stu.Moter_a_now != 0) 
             Memory_data_stu.Moter_a_now--; 
        }
     }
	  A_port_static = A_Port;


    if(App_Obj.cur_key == KEY3_VALUE)
     { 
              Stop_flg.Motor_B_stop =1;  	  
               Motor_B_up_test++;
      if((B_Port)&&(!B_port_static))
      {            
         Memory_data_stu.Moter_b_now++; 
         Motor_B_up_test = 0 ;
      } 
     }
     else if(App_Obj.cur_key == KEY4_VALUE)
     {   
         Stop_flg.Motor_B_stop =1;  	  
         Motor_B_down_test++;
       if((B_Port)&&(!B_port_static))
        {
            Motor_B_down_test = 0;
          if(Memory_data_stu.Moter_b_now != 0) 
             Memory_data_stu.Moter_b_now--; 
        }
      }
          B_port_static = B_Port;			 

      if(App_Obj.cur_key == KEY5_VALUE) { 
           Stop_flg.Motor_C_stop =1;  	   	  	   
       Motor_C_up_test++;
      if((C_Port)&&(!C_port_static))
      {            
         Memory_data_stu.Moter_c_now++; 
         Motor_C_up_test = 0 ;
      } 
     }
     else if(App_Obj.cur_key == KEY6_VALUE)
     {
         Stop_flg.Motor_C_stop =1;  	       	
         Motor_C_down_test++;
         if((C_Port)&&(!C_port_static))
        {
              Motor_C_down_test = 0;
          if(Memory_data_stu.Moter_c_now != 0) 
             Memory_data_stu.Moter_c_now--; 
        }
     }	
         C_port_static = C_Port;     
                
}

unsigned char Prot_Back_Memory_A(unsigned char id)
{
	if(id == 0)
        {
          
           if(return_position_A ||return_position_B ||return_position_C){
                Stop_back_position();
             } 
            else{					     
                Current_Post.Back_position__A = Memory_data_stu.Memory_A_POTION;
                Current_Post.Back_position__B = Memory_data_stu.Memory_B_POTION;
                Current_Post.Back_position__C = Memory_data_stu.Memory_C_POTION;                    
           if(Memory_data_stu.Moter_a_now  > Current_Post.Back_position__A)
             {
                  Set_Push1A_Out(1);
                  Set_Push1B_Out(0);                 
             }
             else if(Memory_data_stu.Moter_a_now < Current_Post.Back_position__A )
             {
                  Set_Push1A_Out(0);
                  Set_Push1B_Out(1);                                   
             }           
             if(Memory_data_stu.Moter_b_now  >  Current_Post.Back_position__B)
              {
                  Set_Push2A_Out(1);
                  Set_Push2B_Out(0);                         
              }
              else if (Memory_data_stu.Moter_b_now < Current_Post.Back_position__B )
              {                           
                  Set_Push2A_Out(0);
                  Set_Push2B_Out(1);                                    
              }
              if(Memory_data_stu.Moter_c_now  >  Current_Post.Back_position__C)
              {
                  Set_Push3A_Out(1);
                  Set_Push3B_Out(0);                                             
              }
              else if (Memory_data_stu.Moter_c_now < Current_Post.Back_position__C )
              {                           
                  Set_Push3A_Out(0);
                  Set_Push3B_Out(1);                                     
              }       					
       
                return_position_A =  1 ;                                       
                return_position_B =  1 ;                                       
                return_position_C =  1 ;   
            }
           return id;
        }     
	    return 0XFF;
        
}

unsigned char Prot_Back_Memory_B(unsigned char id)
{
	if(id == 1)
        {
          
           if(return_position_A ||return_position_B ||return_position_C){
                Stop_back_position();
             } 
            else{					     
                Current_Post.Back_position__A = Memory_data_stu.Memory_2A_POTION;
                Current_Post.Back_position__B = Memory_data_stu.Memory_2B_POTION;
                Current_Post.Back_position__C = Memory_data_stu.Memory_2C_POTION;                    
           if(Memory_data_stu.Moter_a_now  > Current_Post.Back_position__A)
             {
                  Set_Push1A_Out(1);
                  Set_Push1B_Out(0);                 
             }
             else if(Memory_data_stu.Moter_a_now < Current_Post.Back_position__A )
             {
                  Set_Push1A_Out(0);
                  Set_Push1B_Out(1);                                   
             }           
             if(Memory_data_stu.Moter_b_now  >  Current_Post.Back_position__B)
              {
                  Set_Push2A_Out(1);
                  Set_Push2B_Out(0);                         
              }
              else if (Memory_data_stu.Moter_b_now < Current_Post.Back_position__B )
              {                           
                  Set_Push2A_Out(0);
                  Set_Push2B_Out(1);                                    
              }
              if(Memory_data_stu.Moter_c_now  >  Current_Post.Back_position__C)
              {
                  Set_Push3A_Out(1);
                  Set_Push3B_Out(0);                                             
              }
              else if (Memory_data_stu.Moter_c_now < Current_Post.Back_position__C )
              {                           
                  Set_Push3A_Out(0);
                  Set_Push3B_Out(1);                                     
              }       					
       
                return_position_A =  1 ;                                       
                return_position_B =  1 ;                                       
                return_position_C =  1 ;   
            } 
           return id;
        }       
	    return 0XFF;
        
}

unsigned char Prot_Back_Memory_C(unsigned char id)
{
	if(id == 2)
        {
          
           if(return_position_A ||return_position_B ||return_position_C){
                Stop_back_position();
             } 
            else{					     
                Current_Post.Back_position__A = Memory_data_stu.Memory_3A_POTION;
                Current_Post.Back_position__B = Memory_data_stu.Memory_3B_POTION;
                Current_Post.Back_position__C = Memory_data_stu.Memory_3C_POTION;                    
           if(Memory_data_stu.Moter_a_now  > Current_Post.Back_position__A)
             {
                  Set_Push1A_Out(1);
                  Set_Push1B_Out(0);                 
             }
             else if(Memory_data_stu.Moter_a_now < Current_Post.Back_position__A )
             {
                  Set_Push1A_Out(0);
                  Set_Push1B_Out(1);                                   
             }           
             if(Memory_data_stu.Moter_b_now  >  Current_Post.Back_position__B)  
              {
                  Set_Push2A_Out(1);
                  Set_Push2B_Out(0);                         
              }
              else if (Memory_data_stu.Moter_b_now < Current_Post.Back_position__B )
              {                           
                  Set_Push2A_Out(0);
                  Set_Push2B_Out(1);                                    
              }
              if(Memory_data_stu.Moter_c_now  >  Current_Post.Back_position__C) 
              {
                  Set_Push3A_Out(1);
                  Set_Push3B_Out(0);                                             
              }
              else if (Memory_data_stu.Moter_c_now < Current_Post.Back_position__C )
              {                           
                  Set_Push3A_Out(0);
                  Set_Push3B_Out(1);                                     
              }       					
       
                return_position_A =  1 ;                                       
                return_position_B =  1 ;                                       
                return_position_C =  1 ;   
            }
           return id;
        }       
	    return 0XFF;
        
}

unsigned char Prot_Memory_A_Posit(unsigned char id)
{
	if(id == 3)
        {
             Memory_data_stu.Memory_A_POTION  = Memory_data_stu.Moter_a_now;
             Memory_data_stu.Memory_B_POTION  = Memory_data_stu.Moter_b_now;
             Memory_data_stu.Memory_C_POTION  = Memory_data_stu.Moter_c_now;                         
             Flash_Writen_pfun(0x8F00 ,&Memory_data_stu ,FLASH_WriteNByte);  										//记忆位置                                                                   
             
             Memory_data_stu.Memory_Moter_a_now = Memory_data_stu.Moter_a_now;
             Memory_data_stu.Memory_Moter_b_now = Memory_data_stu.Moter_b_now;
             Memory_data_stu.Memory_Moter_c_now = Memory_data_stu.Moter_c_now;                
             Flash_Writen_current_position(0x9F00 ,&Memory_data_stu ,FLASH_WriteNByte);      //记忆当前位置   
             
            return id;
	}
	return 0XFF;
}

unsigned char Prot_Memory_B_Posit(unsigned char id)
{
	if(id == 4)
        {
             Memory_data_stu.Memory_2A_POTION  = Memory_data_stu.Moter_a_now;
             Memory_data_stu.Memory_2B_POTION  = Memory_data_stu.Moter_b_now;
             Memory_data_stu.Memory_2C_POTION  = Memory_data_stu.Moter_c_now;                         
             Flash_Writen_pfun(0x8F00 ,&Memory_data_stu ,FLASH_WriteNByte);  										//记忆位置                                                                   
             
             Memory_data_stu.Memory_Moter_a_now = Memory_data_stu.Moter_a_now;
             Memory_data_stu.Memory_Moter_b_now = Memory_data_stu.Moter_b_now;
             Memory_data_stu.Memory_Moter_c_now = Memory_data_stu.Moter_c_now;                
             Flash_Writen_current_position(0x9F00 ,&Memory_data_stu ,FLASH_WriteNByte);      //记忆当前位置   
             
            return id;
	}
	return 0XFF;
}

unsigned char Prot_Memory_C_Posit(unsigned char id)
{
	if(id == 5)
        {
             Memory_data_stu.Memory_3A_POTION  = Memory_data_stu.Moter_a_now;
             Memory_data_stu.Memory_3B_POTION  = Memory_data_stu.Moter_b_now;
             Memory_data_stu.Memory_3C_POTION  = Memory_data_stu.Moter_c_now;                         
             Flash_Writen_pfun(0x8F00 ,&Memory_data_stu ,FLASH_WriteNByte);  										//记忆位置                                                                   
             
             Memory_data_stu.Memory_Moter_a_now = Memory_data_stu.Moter_a_now;
             Memory_data_stu.Memory_Moter_b_now = Memory_data_stu.Moter_b_now;
             Memory_data_stu.Memory_Moter_c_now = Memory_data_stu.Moter_c_now;                
             Flash_Writen_current_position(0x9F00 ,&Memory_data_stu ,FLASH_WriteNByte);      //记忆当前位置   
             
            return id;
	}
	return 0XFF;
}

unsigned char Port_MemoryInit(unsigned int id)
{
        FLASH_Initializes();
	if(id == 0){
		GPIO_Init(GPIOD, (GPIO_PIN_2), GPIO_MODE_IN_PU_NO_IT); 
		return id;
	}else if(id == 1){
		GPIO_Init(GPIOD, (GPIO_PIN_3), GPIO_MODE_IN_PU_NO_IT); 
		return id;
	}else if(id == 2){
                GPIO_Init(GPIOD, (GPIO_PIN_4), GPIO_MODE_IN_PU_NO_IT); 
		return id;
        }
	return 0XFF;
  
}

void Position_cnt(void) {
        if(Motor_A_up_test >Pushrod_End_Time)
        {
           Motor_A_up_test = 0 ;
          if(Current_Post.Max_Moter_val_A == 0)
          {
            Current_Post.Max_Moter_val_A = Memory_data_stu.Moter_a_now;  
          }              
          else
          {
            Memory_data_stu.Moter_a_now = Current_Post.Max_Moter_val_A ;
          }           
        }     
        if(Motor_A_down_test > Pushrod_End_Time )
        {
           Motor_A_down_test = 0 ;
           Memory_data_stu.Moter_a_now = 0;           
           Current_Post.Max_Moter_val_A = 0 ; 
        }  						            

               if(Motor_B_up_test >Pushrod_End_Time) {
          Motor_B_up_test = 0 ;
        if(Current_Post.Max_Moter_val_B == 0) {
          Current_Post.Max_Moter_val_B = Memory_data_stu.Moter_b_now;
        }              
        else {
          Memory_data_stu.Moter_b_now = Current_Post.Max_Moter_val_B ;
        }            
      }

               if(Motor_B_down_test > Pushrod_End_Time )
        {
           Motor_B_down_test = 0 ;
           Memory_data_stu.Moter_b_now = 0;           
           Current_Post.Max_Moter_val_B = 0 ; 
        }       

                       if(Motor_C_up_test >Pushrod_End_Time)
        {
            Motor_C_up_test	 = 0 ;
          if(Current_Post.Max_Moter_val_C== 0)  //到顶的时候设置最大位置
          {
             Current_Post.Max_Moter_val_C= Memory_data_stu.Moter_c_now;
          }              
          else
          {
             Memory_data_stu.Moter_c_now = Current_Post.Max_Moter_val_C;
          }            
        } 

          if(Motor_C_down_test > Pushrod_End_Time )      // 到底部时候清0 
          {
                 Motor_C_down_test= 0 ;
             Memory_data_stu.Moter_c_now  = 0 ;           
             Current_Post.Max_Moter_val_C = 0 ; 
          }         
}

