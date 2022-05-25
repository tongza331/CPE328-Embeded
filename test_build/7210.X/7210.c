/*
 * File:   7210.c
 * Author: babyt
 *
 * Created on May 20, 2022, 9:47 AM
 */
#define F_CPU 8000000L

#include <avr/io.h>
#include <avr/io.h>

void initADC()
{
  //Set referance voltage to AVcc
  ADMUX |= (1 << REFS0);
  
  // Enable ADC with prescalar 128
  ADCSRA |= (1 << ADEN)|(1 << ADPS1)|(1 << ADPS0);
}

int main(void) {
    /* Replace with your application code */
    DDRB |= (1<<DDB1);// set  PB1 as output
    PORTB |= (1<<PORTB7); //Turn on internal resister
    initADC();
    ADCSRA |= (1 << ADSC);
    while(ADCSRA & (1 << ADSC));
    uint16_t adcValue = ADC;
    
    while(1){
        if(PINB&(1<<7)){
            uint16_t t = adcValue/1024.0*5000.0;
            if(t>5){
                PORTB |= (1<<PORTB1);
            }
            else{
                PORTB &= ~(1<<PORTB1);
            }
        }
        else{
            PORTB &= ~(1<<PORTB1);
        }
  }
}
