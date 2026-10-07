#include "timer.h"

//iniciar
volatile short overflow = 0;
void delay_init() //sin interrupciones
{
        RCC ->  APB1ENR |= (RCC_APB1ENR_TIM2EN); //RCC_APB2ENR_ADC1EN
        TIM2 -> ARR = 0xFFFF; //LIMITE 4 BITS
        TIM2 -> PSC = 7; //PRESCALER
        TIM2 -> CNT = 0; //CONTADOR
        TIM2 -> EGR |= (TIM_EGR_UG); // ACTIVA LA GENERACIÓN DE EVENTOS
    //    TIM2 -> CR1 |= (TIM_CR1_CEN); //EMPIEZA A CONTAR NS SI VA A O NO
}
//micros
void delay_us(uint32_t us)
{ //me ingresan unos micros, me fijo en CNT si son menores a los q estan o no
    TIM2 -> CR1 |= (TIM_CR1_CEN); //EMPIEZA A CONTAR
    
            while(TIM2->CNT < us){  //tiempo inicial
        }
}               
//milli
void delay_ms(uint32_t ms)
{//me ingresan unos millis, me fijo en CNT si son menores a los q estan o no
         TIM2 -> CR1 |= (TIM_CR1_CEN); //EMPIEZA A CONTAR
         int t=0;
                 while(t<ms){  //tiempo inicial
                     delay_us(1000);
                     t++;
                }

}
//iniciar timer
void timer_init() //contiene interrupciones
{
        RCC ->  APB1ENR |= (RCC_APB1ENR_TIM2EN); //RCC_APB2ENR_ADC1EN
        TIM2 -> ARR = 0xFFFF; //LIMITE 4 BITS
        TIM2 -> PSC = 7; //PRESCALER
        TIM2 -> CNT = 0; //CONTADOR
        TIM2 -> EGR |= (TIM_EGR_UG); // ACTIVA LA GENERACIÓN DE EVENTOS
        TIM2 -> DIER |= (TIM_DIER_UIE); //habilito interrupciones  
        TIM2 -> SR |= (TIM_SR_UIF); //flags
        NVIC_EnableIRQ(TIM2_IRQn);//NVIC
}
//milli
uint32_t timer_millis()
{
        TIM2 -> CR1 |= (TIM_CR1_CEN); //EMPIEZA A CONTAR
        uint16_t t_actual = TIM2->CNT;
        uint16_t resultado = (t_actual + overflow*(0xFFFF+1))/1000;
        return(resultado); 
}
void TIM2_IRQHandler(){
        if(TIM2 -> SR & TIM_SR_UIF){
            TIM2 -> SR &=~ TIM_SR_UIF;
                overflow++;
        }
    }

