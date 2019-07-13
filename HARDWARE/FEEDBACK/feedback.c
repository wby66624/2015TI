#include "feedback.h"
#include "adc.h"
#include "math.h"
#include "main.h"
#include "delay.h"
u8 adc_flag = 1;
u16 adc_size=0;
extern int p,jingdu;
extern float youxiaozhi;
//********************求平均值***************************
float average(u16 average[],u16 size)
{
	u16 i;
	float sum=0;
	for(i=0;i<size;i++)
	{
		sum += average[i];	
	}
	sum /= (float)size;
	return sum;	
}

//********************求有效值通用***************************
	float Filter_Init(float *adcx,u16 n)
	{	
		int i;
		float temp;
		float ADC_Average=0;//有效值
		float ADC_Sum=0;//adc平方和
		for(i=0;i<n;i++)
			{
			temp = adcx[i] * adcx[i];
			ADC_Sum += temp;	
			}
		ADC_Average = sqrt(ADC_Sum/n);
		return ADC_Average;
	}




void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{		
		
		u8 i;
		u16 voltage1[ADC_NUM] = {0};
		u16 current1[ADC_NUM] = {0};
		u16 current2[ADC_NUM] = {0};
		
		if(adc_flag)
		{
			for(i=0;i<ADC_NUM;i++)
			{
				voltage1[i] = DMA_ADC[i][0];
				current1[i] = DMA_ADC[i][1];
				current2[i] = DMA_ADC[i][2];
			}	
			ADC_1[adc_size] = ADC_Filtration(voltage1,ADC_NUM,ADC_NUM/4);
			ADC_2[adc_size] = ADC_Filtration(current1,ADC_NUM,ADC_NUM/4);
			ADC_3[adc_size] = ADC_Filtration(current2,ADC_NUM,ADC_NUM/4);
			ADC_1[adc_size] = ADC_Filtration(ADC_1,ADC_NUM,ADC_NUM/4);
			ADC_2[adc_size] = ADC_Filtration(ADC_2,ADC_NUM,ADC_NUM/4);
			ADC_3[adc_size] = ADC_Filtration(ADC_3,ADC_NUM,ADC_NUM/4);
    	    validity_i1[adc_size]=	ADC_1[adc_size];
	        validity_i2[adc_size]=	ADC_2[adc_size];
			adc_size++;
			
		}
		if(adc_size >= 256)
		{
			
			adc_size = 0;
//			adc_flag = 0;
		}
//		
//		ADC1->CR2 = 0X000001;
//	
//	ADC_DMACmd(ADC1,ENABLE);
//	
//	ADC_Cmd(ADC1, ENABLE);//使能指定的ADC1

//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

		
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

//***********************功能：均值滤波*************************//
//1.数组指针
//2.数组有几个数
//3.去掉几个最值
u16 ADC_Filtration(u16 *result,u16 n,u16 del_num)
{
	u16 i,j;
	u32 temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(result[j]>result[j+1])
			{
				temp=result[j];
				result[j]=result[j+1];
				result[j+1]=temp;
			}
		}
	}
	if(n>2*del_num)
	{
		for(i=del_num,temp=0;i<n-del_num;i++)
		{
			temp+=result[i];
		}
		return temp/(n-2*del_num);
	}
	else
	{
		for(i=0,temp=0;i<n;i++)
		{
			temp+=result[i];
		}
		return temp/n;
	}
}

void kongzhi(int *pwm)
{


////	if(p==1)
////	{	
////	b=(float)target_v*5.3186813187;///4095*3.3*11/12*7200
////	*pwm=(int)b-200;
////		a=0;
////	}
//	
//				if((youxiaozhi<(2599-jingdu)))
//				{				
//					if((youxiaozhi<(2599-jingdu)))
//					{	
//								
//						if((youxiaozhi<(2599-jingdu)))
//		{		
//			
//	    *pwm+=1;
//			delay_ms(1);
//	
//		}    
//	}
//}
//		if((youxiaozhi>(2599+jingdu)))
//		{		
//			if((youxiaozhi>(2599+jingdu)))
//				{		
//					if((youxiaozhi>(2599+jingdu)))
//		     {		*pwm-=1;
//		           delay_ms(1);
//       	 }  
//        }	
//    }
}






