/*
 * File:   code_lab8.c
 * Author: babyt
 *
 * Created on April 24, 2022, 3:55 PM
 */


#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LCD_Dir DDRB
#define LCD_Port PORTB
#define LCD_RS_DDR DDRD
#define LCD_RS_PORT PORTD
#define LCD_RS_PIN PORTD0
#define LCD_RW_DDR DDRD
#define LCD_RW_PORT PORTD
#define LCD_RW_PIN PORTD1
#define LCD_E_DDR DDRD
#define LCD_E_PORT PORTD
#define LCD_E_PIN PORTD2

void sendLCDCommand(uint8_t command){
    LCD_RS_PORT &= ~(1<<LCD_RS_PIN);
    LCD_RW_PORT &= ~(1<<LCD_RW_PIN);
    LCD_Port = command;
    LCD_E_PORT |= (1<<LCD_E_PIN);
    _delay_us(500);
    LCD_E_PORT &= ~(1<<LCD_E_PIN);
    _delay_ms(1);
}
void sendLCDData(uint8_t data){
    LCD_RS_PORT |= (1<<LCD_RS_PIN);
    LCD_RW_PORT &= ~(1<<LCD_RW_PIN);
    LCD_Port = data;
    LCD_E_PORT |= (1<<LCD_E_PIN);
    _delay_us(500);
    LCD_E_PORT &= ~(1<<LCD_E_PIN);
    _delay_ms(1);
}

void initLCD(){
    LCD_Dir = 0xFF;
    LCD_E_DDR |= (1<<LCD_E_PIN);
    LCD_E_PORT &= ~(1<<LCD_E_PIN);
    LCD_RW_DDR |= (1<<LCD_RW_PIN);
    LCD_RW_PORT &= ~(1<<LCD_RW_PIN);
    LCD_RW_DDR |= (1<<LCD_RS_PIN);
    LCD_RS_PORT &= ~(1<<LCD_RS_PIN);
    
    sendLCDCommand(0x38);
    sendLCDCommand(0x0E);
    sendLCDCommand(0x01);
    sendLCDCommand(0x14);
}

int main(void){
    initLCD();
    _delay_ms(1);
    const char* word = "Hello";
    int i = 0;
    while(word[i] != '\0'){
        sendLCDData(word[i]);
        i += 1;
    }
    return 0;
}