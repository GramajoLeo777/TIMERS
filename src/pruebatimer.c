#include "stm32f103xb.h"
#include "timer.h"
#include "pwm.h"
#include "adc.h"
/*2. Hacer un código de ejemplo que modifique la intensidad de un led con pwm 
mediante la variacion de un potenciómetro leído por el ADC de la placa.*/
const int canal = 1, frecuencia = 1000, led = 26, potencio = 30;

int main(void)
{
        delay_init();
        pwm_init(canal, frecuencia);
     while(1)
{

        uint16_t lectura = adc_read(canal);             // 0 a 4095
          uint8_t duty = (lectura * 100UL) / 4095;   // 0 a 100 % UL para que no desborde
        pwm(1, duty);
        delay_ms(50);
}
}








