#include "spwm.h"
#include "main.h"
//sin函数的900个点（30000倍）//
const float sin_value_SHIGH[600] ;
const float sin_value_HIGH[810] ;
const float sin_value_LOW[1800] ;




int sin_max;
u16 sin_i0=0;
u16 sin_hhigh=300;
u16 sin_i1=0;	//正弦波1
u16 sin_high=405;
u16 sin_i2=0;
u16 sin_low=900;
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
//		if(Hz<=46)
//		{
//		sin_i2 = (sin_i2+1)%1800;
//		sin_low = (sin_low+1)%1800;
//		TIM2->CCR1 = sin_value_LOW[sin_i2]*sin_max/3200+rrr/2;
//		TIM2->CCR2 = sin_value_LOW[sin_low]*sin_max/3200+rrr/2;
//		}
		
	
//		sin_i1 = (sin_i1+1)%810;
//		sin_high = (sin_high+1)%810;

//		TIM2->CCR3 = sin_value_HIGH[sin_i1]*sin_max/3200+rrr/2;
//		TIM2->CCR2 = sin_value_HIGH[sin_high]*sin_max/3200+rrr/2;
		TIM2->CCR3 =sin_max;
		TIM2->CCR2 = sin_max;
//		 else
//		{
//			sin_i0 = (sin_i0+1)%600;
//		sin_hhigh = (sin_hhigh+1)%600;

//		TIM2->CCR1 = sin_value_SHIGH[sin_i0]*sin_max/3200+rrr/2;
//		TIM2->CCR2 = sin_value_SHIGH[sin_hhigh]*sin_max/3200+rrr/2;
//		
//		}
		

		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

