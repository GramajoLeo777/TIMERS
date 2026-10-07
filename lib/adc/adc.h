#ifndef ADC_H
#define ADC_H
#include "stm32f103xb.h"
//iniciar
void adc_init();
//leer++
int adc_read(unsigned int canal);

#endif