/*
 * File:   code8_2.c
 * Author: babyt
 *
 * Created on April 24, 2022, 10:21 PM
 */

#define F_CPU 8000000UL
#include <xc.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1<<PORTB1); // input
    PORTB &= ~(1<<PORTB1);
//    DDRD = 0xFF; // output
    
    TCCR1A = 0; // Normal mode
    TCCR1B |= (1<<CS10) | (1<<ICNC1);
    
    while(1){
        PORTC |= (1<<PORTC1);
        _delay_us(20);
        PORTC &= ~(1<<PORTC1);
        
        TCCR1B |= (1<<ICES1);
        
        while(!(TIFR1 &(1<<ICF1)));
        TIFR1 |= (1<<ICF1);
        TCNT1 = 0; // count from 1
        
        TCCR1B &= ~(1<<ICF1);
        
        while(!(TIFR1 & (1<<ICF1)));
        TIFR1 |= (1<<ICF1);
        
        float pulseCount = ICR1;
        uint8_t distance = (pulseCount / 1000000.0 * 340.0) / 2.0*100.0;
        PORTD = distance;
        _delay_ms(1000);
    }
    return 0;
}
