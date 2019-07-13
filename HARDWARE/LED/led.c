#include "led.h"
void led_init(void)
{
	GPIO_InitTypeDef  LED;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	LED.GPIO_Mode = GPIO_Mode_Out_PP;
	LED.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	LED.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&LED);
	GPIO_ResetBits(GPIOC,GPIO_Pin_2|GPIO_Pin_3);

}
