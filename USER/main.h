#ifndef _MAIN_H
#define _MAIN_H

#include "stm32f10x.h"

#define PI 3.1415926
#define ADC_NUM 8
#define NUM_SIZE 256
#define FLASH_SAVE_ADDR  0X08070000
#define FLASH_SAVE_ADDR1   0x0800F000     
extern u16 DMA_ADC[ADC_NUM][3];
extern u16 ADC_1[NUM_SIZE];
extern u16 ADC_2[NUM_SIZE];
extern u16 ADC_3[NUM_SIZE];
extern float validity_i1[NUM_SIZE];
extern float validity_i2[NUM_SIZE];
extern u16 ADC_I0;
extern u16 rrr;
extern int Hz;
extern u16 P2;
#endif 
