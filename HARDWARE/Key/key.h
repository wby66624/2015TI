#ifndef _key_H
#define _key_H
#include "sys.h"
#include "delay.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_12)
#define KEY2 GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_1)
#define KEY3 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)
#define KEY4 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13)
#define KEY5 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_14)
#define KEY6 GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_15)



void KEY_Init(void);
int KEY_Scan(void);


#endif

