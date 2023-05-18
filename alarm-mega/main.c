#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"    // lcd header file made by Peter Fleury

// States for state machine
#define IDLE 'i'
#define DISARMED 'p'
#define ALARM 2
#define TRIGGERED_WRONGPASSWORD 3
#define TRIGGERED_TOOSLOW 4
char state = IDLE;

void alarm_sound(void);

char display_buffer[16];

int filterResult(char ret) {
	if (ret == IDLE || ret == DISARMED || ret == ALARM || ret == TRIGGERED_TOOSLOW || ret == TRIGGERED_WRONGPASSWORD) {
		return 1;
	}
	return 0;
}

int main(void)
{   
    // Set up passive buzzer ports and pins
    DDRE |= (1 << PE3); // OC3A is located in digital pin 5
    
	/* Hook URT stream to std */
	FILE uart_output = FDEV_SETUP_STREAM(USART_transmit, NULL, _FDEV_SETUP_WRITE);
	FILE uart_input = FDEV_SETUP_STREAM(NULL, USART_receive, _FDEV_SETUP_READ);
	stdout = &uart_output;
	stdin = &uart_input;
	
	USART_init(UBRR);
    
    // Enable interrupts
    sei();
    
    // initialize display, cursor off
    lcd_init(LCD_DISP_ON);
	lcd_clrscr();
     
    // For alarm: set up the 16-bit timer/counter3, mode 9
    TCCR3B = 0;         // Reset timer/counter 3
    TCNT3  = 0;
    TCCR3A |= (1 << 6); // Set compare output mode to toggle
    // Mode 9 phase correct
    TCCR3A |= (1 << 0); // Set register A WGM[1:0] bits
    TCCR3B |= (1 << 4); // Set register B WBM[3:2] bits
    TIMSK3 |= (1 << 1); // Enable compare match A interrupt
	
	char temp = UDR0;
    while (1) 
    {
		printf("Out of switch state: %c\n\r", state);
        // State machine
        switch(state) {
            case IDLE:
                // Clear display and print string
                lcd_clrscr();
                lcd_puts("Alarm system on");
            
                // Wait for data to be received
                //while (!(UCSR0A & (1<<RXC0)));
				char result = USART_receive();
				if (filterResult(result) == 1) {
					state = result;
				}
				//state = UDR0;
				printf("Inside idle state: %c\n\r", state);
                
                // Read the received data into state variable
                break;
                
            case DISARMED:
                lcd_clrscr();
                lcd_puts("Disarmed");
                _delay_ms(10);
                
                // Wait for data to be received and read the received data
                // TODO: should it only be possible to change the state to idle from here? 
                while (!(UCSR0A & (1<<RXC0)));
                state = UDR0;
                break;
                
            case ALARM:
                lcd_clrscr();
                lcd_puts("Give password");
                                
                // Wait for data to be received and read the received data
                while (!(UCSR0A & (1<<RXC0)));
                state = UDR0;
                break;
                
            case TRIGGERED_WRONGPASSWORD:
                lcd_clrscr();
                lcd_puts("Wrong password");
                _delay_ms(2000);
                alarm_sound();                        
                break;
                
            case TRIGGERED_TOOSLOW:
                lcd_clrscr();
                lcd_puts("Time ran up");
                _delay_ms(2000);
                alarm_sound();
                break;
                
            default:
                state = IDLE;
                break;
        }
    }
}

void alarm_sound() {
    // Make alarm go off
    OCR3A = 15296; //  C5 523 Hz, no prescaler
    // Enable timer/counter
    TCCR3B |= (1 << 0); // set prescaling to 1 (no prescaling)
}
