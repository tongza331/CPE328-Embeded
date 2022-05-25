/*
 * File:   main_build.c
 * Author: babyt
 *
 * Created on April 27, 2022, 11:41 PM
 */

// TEST
//        PORTB |= (1<<PORTB1);
//        _delay_ms(100);
//        PORTB &= ~(1<<PORTB1);
//        _delay_ms(100);

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

// LED PB1
// BUTTON PB0 
// POT PC4

void initADC(){
  // Set reference voltage to AVcc
  ADMUX |= (1 << REFS0);
  // Enable ADC with prescalar 128
  ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

int main(void) {
    
    DDRB |= (1 << DDB1); // OUTPUT LED
    DDRB &= ~(1 << DDB0); //INPUT BUTTON
    PORTB |= (1<<PORTB0);
    initADC();
    
    while (1) {
        ADCSRA |= (1<<ADSC);
        while (ADCSRA&(1<<ADSC));
        uint16_t adcValue = ADC;
        
        if(!(PINB&(1<<PORTB0))==0){
            PORTB |= (1<<PORTB1);
        } else {
            PORTB &= ~(1<<PORTB1);
        }
        
    } 
}
