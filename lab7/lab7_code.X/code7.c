/*
 * File:   code7.c
 * Author: babyt
 *
 * Created on April 24, 2022, 9:33 AM
 */
#define F_CPU 8000000UL
#include <xc.h>
#include <avr/interrupt.h>

void Timer1_init(){
    TCCR1A = 0x00; // Normal mode
    TCCR1B |= (1<<CS12); // Pre-scalar 256 @8MHz
    TCNT1 = 59285; // Delay real-time 0.2 second but in Proteus will show 2 second
    TIMSK1 |= (1<<TOIE1); // Enable timer overflow interrupt
}

ISR(TIMER1_OVF_vect){
    if((PIND&(1<<PORTD4))==0){
        TCNT1 = 59285;
        PORTC ^= (1<<PORTC0);      
    } 
    else {
        PORTC &= ~(1<<PORTC0);
    }
}

int main(void) {
    // Enable internal pull-up
    PORTD |= (1 << PORTD4);
    // LED setting
    DDRC |= (1 << PORTC0);
    PORTC &= ~(1 << PORTC0); 
    Timer1_init();
    sei();
    while(1){  
    }
    return 0;
}
