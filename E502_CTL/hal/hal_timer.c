#include "hal_timer.h"
#include "data_type.h"
#include "stm8s.h"
#include "timeout.h"
//#include "stm8s_it.h"
//#include "stm8s_it.c"

//static void (*Hal_Timer_Hdl_Cb)(void);

unsigned char Hal_TimerInit(void)
{
        TIM4_DeInit();//��λTIM4ȫ������
        TIM4_TimeBaseInit(TIM4_PRESCALER_128,125-1);//��ʱ1ms (16M/128/125 = 1000)
        
        TIM4_ClearFlag(TIM4_FLAG_UPDATE);              //�����־λ
        TIM4_Cmd(ENABLE);//ʹ�ܼ�ʱ��
        TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);//ʹ��TIM4�ж�
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
       TIM4_ClearITPendingBit(TIM4_IT_UPDATE); //����жϱ�־

	TimeOutDet_DecHandle();
}
