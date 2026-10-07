#include "stm32f103xb.h"
#ifndef TIMER_H
#define TIMER_H
//iniciar
void delay_init(); //sin interrupciones
//micros
void delay_us(uint32_t us);
//milli
void delay_ms(uint32_t ms);
//iniciar timer
void timer_init(); //contiene interrupciones
//milli
uint32_t timer_millis();


#endif