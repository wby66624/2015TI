//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//All rights reserved
//******************************************************************************/
#include "stm32f10x.h"
#include "delay.h"
#include "menu.h"
#include "OLED.H"
#include "Queue.h"
#include "stack.h"
#include "stdio.h" 

#include "key.h"

#include "stmflash.h"   

#include "math.h"
#include "spwm.h"
#include "adc.h"
#include "dma.h"
#include "main.h"
#include "feedback.h"
#include "sys.h"

#include "stm32f10x.h" 

		//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)

u16 DMA_ADC[ADC_NUM][3] = {0};
//ADC����������ȡ����
u16 ADC_1[NUM_SIZE] = {0};
u16 ADC_2[NUM_SIZE] = {0};
u16 ADC_3[NUM_SIZE] = {0};
float validity_i1[NUM_SIZE] = {0};
float validity_i2[NUM_SIZE] = {0};
u16 rrr;//rrr��װֵ 
u16 percent_w,percent_r,rrrr;	float a=0;//��Ƶ�����
float ADC_I=0,duty=0;	u16 ADC_I0=0;	float ADC_I1=0;int ADC_FACTI;float rr;//��������1  **���յ���   ��ʼ����   ʵ��ad
float sin_p;//���Ұٷֱ�
int Hz = 50;//��·Ƶ�� 4420  657
extern MenuPage firstPage;
extern u16 kk;
u16 kk1,pkp1;
u16 pkp2=3.259;
extern float pkp;
extern int kkint1,kkint2;
u16 kk2=119;
float I_set=1;
 int main(void)
 {		 
	    rrr=1600;
	    STMFLASH_Read(FLASH_SAVE_ADDR,&kk2,1);	
        kkint1=kk2;
		delay_init();	    	 //��ʱ������ʼ��	 
	 	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		TIM2_PWM_Init(rrr,0);
//		TIM4_PWM_Init(8999,0);
	 	TIM3_Int_Init(4999,10);
		Init_Menue(&firstPage);
	 	MYDMA_Config(DMA1_Channel1,(u32)&ADC1->DR,(u32)DMA_ADC[0],ADC_NUM*3);
	    Adc_Init();		  		//ADC��ʼ��	  
		OLED_Init();
		KEY_Init();  
        duty=0.69;
	    sin_max = rrr/2+300;// 339-15// 491-12 363-9   613-15  743-18                                                  30v
//TIM4->CCR1 = 4499;

	while(1)
	{	

	kk1=kkint1;
	sin_max=duty*rrr ;	
	TIM_SetAutoreload(TIM2,rrr-1); 		
	Menue_Show();
	KeyNumGet(KEY_Scan());
	}
}	
