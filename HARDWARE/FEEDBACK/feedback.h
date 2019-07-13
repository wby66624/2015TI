#ifndef __FEEDBACK_H
#define __FEEDBACK_H
#include "sys.h"

extern u16 adc_size;
extern u8 adc_flag;
float average(u16 average[],u16 size);
u16 ADC_Filtration(u16 *result,u16 n,u16 choose_n);
float Filter_Init(float *adcx,u16 n);
//float Filter_ave_Init(float *adc,u16 x);
void kongzhi(int *pwm);
#endif
