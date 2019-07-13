#include "hal_timer.h"
#include "data_type.h"
#include "stm8s.h"
#include "timeout.h"
//#include "stm8s_it.h"
//#include "stm8s_it.c"

//static void (*Hal_Timer_Hdl_Cb)(void);

unsigned char Hal_TimerInit(void)
{
        TIM4_DeInit();//复位TIM4全部參数
        TIM4_TimeBaseInit(TIM4_PRESCALER_128,125-1);//定时1ms (16M/128/125 = 1000)
        
        TIM4_ClearFlag(TIM4_FLAG_UPDATE);              //清除标志位
        TIM4_Cmd(ENABLE);//使能计时器
        TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);//使能TIM4中断
	return TRUE;
}     

//unsigned char Hal_RegTimeHdl(void(*cb)(void))
//{
//	if(!cb){
//		return FALSE;
//	}
//	Hal_Timer_Hdl_Cb = cb;
//
//	return TRUE;
//}

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23){
       TIM4_ClearITPendingBit(TIM4_IT_UPDATE); //清除中断标志

	TimeOutDet_DecHandle();
}
