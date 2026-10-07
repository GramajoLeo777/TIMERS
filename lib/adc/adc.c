#include "adc.h"

/*Crear una librería para el control de los 10 canales de ADC que tiene la bluepill. 
Se tendrán dos funciones:
*/
/*
● 1. Habilitar clocks del GPIO y del ADC.
● 2. Configurar el clock del ADC con un divisor válido.
● 3. Configurar el pin como entrada analógica.
● 4. Encender y calibrar el ADC.
● 5. Seleccionar el canal en la secuencia regular.
● 6. Elegir el tiempo de muestreo.
● 7. Iniciar la conversión.
● 8. Esperar EOC.
● 9. Leer DR.
*/


void adc_init(){
    //ENCIENDO CLOCK
    RCC-> APB2ENR |= (RCC_APB2ENR_ADC1EN);
    RCC -> APB2ENR |= (RCC_APB2ENR_IOPAEN);
    RCC -> APB2ENR |= (RCC_APB2ENR_IOPBEN);
    //encender y calibrar  adc
    //encender → esperar estabilización → reset de calibración → calibrar → esperar fin.
    ADC1 -> CR2 |= ADC_CR2_ADON; //ENCENDER EL ADC
        for( int i= 0; i<1000; i++); //ESPERAR ESTABILIZACIÓN
    ADC1 -> CR2 |= ADC_CR2_RSTCAL; //RESET
        while(ADC1->CR2&ADC_CR2_RSTCAL);
    ADC1 -> CR2 |= ADC_CR2_CAL; //CALIBRO
        while(ADC1->CR2&ADC_CR2_CAL);
      ADC1->CR2 |= ADC_CR2_EXTSEL;   //DEFINO COMO SE DISPARA (issue 2)
      ADC1->CR2 |= ADC_CR2_EXTTRIG;
}

int adc_read(unsigned int canal){
    //CNF = 00 y MODE = 00.
    if(canal <  8){
        GPIOA -> CRL &=~ (0xF << canal*4); //PA0-PA7
    }else{
    GPIOB->CRL&=~(0xF<<(canal%2)*4); //PB0 o PB1 (issue 1)
}
    ADC1 -> SQR3 |= canal ; //ESCRIBO NUM DE CANAL EN CH1
    ADC1 -> SMPR2  |= (0b111 << canal*3) ; //SET TIEMPO MUESTREO
    ADC1 -> CR2 |= ADC_CR2_SWSTART; //INICIAR CONVERSION
        while (~(ADC1 -> SR & ADC_SR_EOC)); //TERMINO LA CONVERSION?
    return ADC1 -> DR;//VALOR DIGITAL FINAL
}


