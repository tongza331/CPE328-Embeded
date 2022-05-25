/*
 * File:   PWM_code.c
 * Author: babyt
 *
 * Created on April 25, 2022, 3:36 PM
 */


#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>

void initPWM(){ 
    TCCR0A |= (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (1 << CS01) | (1 << CS00);
}

void PWMOut(uint8_t duty){
    OCR0B = duty;
}

void Wait(){
    _delay_ms(30);
}

int main(void) {
    DDRD |= (1<<PORTD5);
    PORTD &= ~(1<<PORTD5);
    initPWM();
    
    int brightness = 0;
    int PWM_Fade[16] = {0,1,2,3,4,6,8,12,16,23,32,45,64,90,128,180,255};
    while(1){
        for(brightness = 0; brightness<16; brightness++){
            PWMOut(PWM_Fade[brightness]);
            Wait();
        }
        for(brightness = 16; brightness>=0; brightness--){
            PWMOut(PWM_Fade[brightness]);
            Wait();
        }
    }
    return 0;
}
