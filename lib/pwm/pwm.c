#include "stm32f103xb.h"

void pwm_init(uint8_t canal, uint32_t frec)
{
        uint8_t TIM3_CH1 =  GPIOA -> IDR & (1<<6); //PA6;
        uint8_t TIM3_CH2 =  GPIOA -> IDR & (1<<7); //PA7
        uint8_t TIM3_CH3 =  GPIOB -> IDR & (1<<0); //PB0
        uint8_t TIM3_CH4 =  GPIOB -> IDR & (1<<1); //PB1

    switch(canal){
        case 1: 
            RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
            RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
            RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
            GPIOA -> CRL     &=~    (0xF << (TIM3_CH1)*4); //PP-AF
            GPIOA -> CRL     |=     (0xB << (TIM3_CH1)*4); //limpio OC1M
            TIM3 -> CCMR1    &=~    (0b111 << 4); //limpio OC1M
            TIM3 -> CCMR1    &=     (0b110 <<4); //OC1M : 110 -> PWM MODE
            TIM3 -> CCER     |=     TIM_CCER_CC1E; //HABILITA LA SALIDA 
        break;
                case 2: 
            RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
            RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
            RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
            GPIOA -> CRL     &=~    (0xF << (TIM3_CH2)*4); //PP-AF
            GPIOA -> CRL     |=     (0xB << (TIM3_CH2)*4); //limpio OC1M
            TIM3 -> CCMR1    &=~    (0b111 << 4); //limpio OC1M
            TIM3 -> CCMR1    &=     (0b110 <<4); //OC1M : 110 -> PWM MODE
            TIM3 -> CCER     |=     TIM_CCER_CC1E; //HABILITA LA SALIDA 
        break;
                case 3: 
            RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
            RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
            RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
            GPIOA -> CRL     &=~    (0xF << (TIM3_CH3)*4); //PP-AF
            GPIOA -> CRL     |=     (0xB << (TIM3_CH3)*4); //limpio OC1M
            TIM3 -> CCMR1    &=~    (0b111 << 4); //limpio OC1M
            TIM3 -> CCMR1    &=     (0b110 <<4); //OC1M : 110 -> PWM MODE
            TIM3 -> CCER     |=     TIM_CCER_CC1E; //HABILITA LA SALIDA 
        break;
                case 4: 
            RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
            RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
            RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
            GPIOA -> CRL     &=~    (0xF << (TIM3_CH4)*4); //PP-AF
            GPIOA -> CRL     |=     (0xB << (TIM3_CH4)*4); //limpio OC1M
            TIM3 -> CCMR1    &=~    (0b111 << 4); //limpio OC1M
            TIM3 -> CCMR1    &=     (0b110 <<4); //OC1M : 110 -> PWM MODE
            TIM3 -> CCER     |=     TIM_CCER_CC1E; //HABILITA LA SALIDA 
        break;
        default:
        break;
    }
        TIM3 -> PSC= 7;
        TIM3 -> ARR = ((1000000 / frec)-1); 
        TIM3 -> EGR |= TIM_EGR_UG;
        TIM3 -> CR1 |= TIM_CR1_CEN;
}

void pwm(uint8_t canal , uint8_t duty)
{
    if(duty>100) duty = 100;

         if(canal == 1)
                              TIM3 -> CCR1 = ((TIM3 -> ARR + 1)*duty/100);
            else if(canal==2) TIM3 -> CCR2 = ((TIM3 -> ARR + 1)*duty/100);
            else if(canal==3) TIM3 -> CCR3 = ((TIM3 -> ARR + 1)*duty/100);
            else if(canal==4) TIM3 -> CCR4 = ((TIM3 -> ARR + 1))*duty/100;

    
}