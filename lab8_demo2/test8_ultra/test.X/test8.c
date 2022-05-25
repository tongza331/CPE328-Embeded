/*
 * File:   code_lab8.c
 * Author: babyt
 *
 * Created on April 24, 2022, 3:55 PM
 */


#define F_CPU 8000000UL
#include <xc.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define LCD_DATA_DDR DDRD
#define LCD_DATA_PORT PORTD

#define LCD_RS_DDR DDRC
#define LCD_RS_PORT PORTC
#define LCD_RS_PIN PORTC0

#define LCD_RW_DDR DDRC
#define LCD_RW_PORT PORTC
#define LCD_RW_PIN PORTC1

#define LCD_E_DDR DDRC
#define LCD_E_PORT PORTC
#define LCD_E_PIN PORTC2

#define ECHO PORTB0
#define TRI_PIN PORTB1

void sendLCDCommand(uint8_t command) {
    LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
    LCD_RW_PORT &= ~(1 << LCD_RW_PIN);
    LCD_DATA_PORT = command;
    LCD_E_PORT |= (1 << LCD_E_PIN);
    _delay_us(500);
    LCD_E_PORT &= ~(1 << LCD_E_PIN);
    _delay_ms(1);
}

void sendLCDData(uint8_t data){
    LCD_RS_PORT |= (1 << LCD_RS_PIN);
    LCD_RW_PORT &= ~(1 << LCD_RW_PIN);
    LCD_DATA_PORT = data;
    LCD_E_PORT |= (1 << LCD_E_PIN);
    _delay_us(500);
    LCD_E_PORT &= ~(1 << LCD_E_PIN);
    _delay_ms(1);
}

void initLCD(){
    LCD_DATA_DDR = 0xFF;
    LCD_E_DDR |= (1 << LCD_E_PIN);
    LCD_E_PORT &= ~(1 << LCD_E_PIN);
    LCD_RW_DDR |= (1 << LCD_RW_PIN);
    LCD_RW_PORT &= ~(1 << LCD_RW_PIN);
    LCD_RS_DDR |= (1 << LCD_RS_PIN);
    LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
    
    sendLCDCommand(0x38);
    sendLCDCommand(0x0E);
    sendLCDCommand(0x01);
    sendLCDCommand(0x14);
    _delay_ms(2);
}

void sendString(const char* word){
    int i = 0;
    while(word[i] != '\0'){
        sendLCDData(word[i]);
        i += 1;
    }
}

void LCD_Clear(){
    sendLCDCommand(0x01);
    _delay_ms(2);
    sendLCDCommand(0x80);
}

void TIMER1_Init() {
    TCCR1B |= (1 << ICNC1) | (1 << CS11);
}

uint16_t ultrasonic(){
      //phase 1: start
      ////trig high
      PORTB |= (1 << TRI_PIN);
      //delay 10 us
      _delay_us(10);

      //trig low
      PORTB &= ~(1 << TRI_PIN);
      
      //phase 2: capture wave rising
      //set to capture rising edge
      TCCR1B |= (1 << ICES1);
      //check ICF1 high for capture event
      while (!(TIFR1 & (1 << ICF1)));
      //set TCNT1 to 0
      TCNT1 = 0;
      //reset ICF1 flag
      TIFR1 |= (1 << ICF1);

      //phase 3: capture wave falling
      //set to capture falling edge
      TCCR1B &= ~(1 << ICES1);
      //check ICF1 high for capture event
      while (!(TIFR1 & (1 << ICF1)));
      TIFR1 |= (1 << ICF1);
      //copy 16-bit data out from ICR1
      uint16_t data = ICR1;
      //reset ICF1 flag
      TIFR1 |= (1 << ICF1);

      return data;
}

int main(void) {
    
    //set trig port to output, low
    initLCD();
    
    //set trig port to output low
    DDRB |= (1 << TRI_PIN);
    PORTB &= ~(1 << TRI_PIN);
    
    TIMER1_Init();
    
    char output_string[20] = {};
    
//    uint8_t distance = 10.0;
//    sprintf(output_string,"Distance: %d cm\n", distance);
//    sendString(output_string);

    while(1){
        //Read value from ultrasonic
        uint16_t pulseCount = ultrasonic();

        //phase 4: convert and output
        //convert
        uint8_t distance = ((pulseCount / 1000000.0) * 340 * 100) / 2.0;
        sprintf(output_string, "Distance: %d cm\n", distance);
        //output
        LCD_Clear();
        sendString(output_string);
        _delay_ms(1000);
    }
    return 0;
}
    
        
        

    
