#include "key.h"
void KEY_Init(void)
{
	
GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOC, ENABLE);//使能GPIOB时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
  GPIO_Init(GPIOF, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
  GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
  GPIO_Init(GPIOG, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode =   GPIO_Mode_Out_PP; 		 
  GPIO_Init(GPIOC, &GPIO_InitStructure);	//根据设定参数初始化GPIOA.8
}
int KEY_Scan()
{
//	static u8 key_up=1;(key_up==1)&&
	if ((KEY1 == 0 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0|| KEY5==0|| KEY6==0))
	{
		delay_ms(60);
//		key_up =0;
		if (KEY1 == 0) return 3;//左键
		if (KEY2 == 0) return 2;//下键
		if (KEY3 == 0) return 4;//右键
		if (KEY4 == 0) return 5;//确认
		if (KEY5 == 0) return 1;//上键
		if (KEY6 == 0) return 6;//返回
	}
//	else if((KEY1 == 1)&& (KEY2 == 1)&& (KEY3 == 1) && (KEY4 == 1)&& (KEY5==1)&&( KEY6==1))key_up =1;
	return 0;
}










