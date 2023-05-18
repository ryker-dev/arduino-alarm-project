/*
 * Get password typed with keypad and check if it is correct.
 * Character # works as a 'submit password' button and * as backspace.
 *
 * Source of inspiration:
 * https://circuitdigest.com/microcontroller-projects/keypad-interfacing-with-avr-atmega32
 */ 

#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

// Bitmasks for handling the correct pins from ports D and B
// that the keypad is connected to (Arduino Uno digital pins 6-13)
#define BITMASK_D 0b11000000
#define BITMASK_B 0b00111111

void led_test(void){
    PORTD &= ~(1 << PD3);
    _delay_ms(1000);
    PORTD |= (1 << PD3);
    _delay_ms(1000);
    PORTD &= ~(1 << PD3);
    _delay_ms(1000);
}

// Compare user given password with the correct password
int compare(char *password, char *given_password){
	printf("%c", given_password);
	printf("%s", password);
	if (strncmp(password, given_password, 4) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int check_password(void)
{
    /********************testing****************************/
    /*char input;
    FILE uart_output = FDEV_SETUP_STREAM(USART_transmit, NULL, _FDEV_SETUP_WRITE);
    FILE uart_input = FDEV_SETUP_STREAM(NULL, USART_receive, _FDEV_SETUP_READ);
    
    USART_init(UBRR);
    
    stdout = &uart_output;
    stdin = &uart_input;*/
    /******************************************************/
    
    char *password = "0123";
    char given_password[30];
	char *pass_start = &given_password;
	memset(given_password,0,30);
    int idx = 0;
    
    uint8_t key_pressed = 0;
    uint8_t keypad_vals;
    uint8_t portb_vals;
    uint8_t portd_vals;
    
    // Set digital pins 6-9 (rows) as input and 10-13 (columns) as output
    DDRD &= 0b00111111;
    DDRB &= 0b11111100;
    DDRB |= 0b00111100;
    _delay_ms(1);
    
    // Power the row pins
    PORTD |= 0b11000000;
    PORTB |= 0b00000011;
    _delay_ms(1);
    
    while (1) 
    {
        // Read row values into variable keypad_vals
        portd_vals = ((PIND & BITMASK_D) >> 6);
        portb_vals = ((PINB & BITMASK_B) << 2);
        keypad_vals = portd_vals | portb_vals;
        keypad_vals &= 0b00001111;
		
		// Make rows as output and columns as input
		DDRD |= 0b11000000;
		DDRB = 0b00000011;
		_delay_ms(1);
		            
		// Power the column pins
		PORTB = 0b00111100;
		PORTD &= 0b00111111;
		_delay_ms(1);
        
        if (keypad_vals != 0b00001111) {     // If any of the row pins goes low // This bit doesn't work on second try
            key_pressed = keypad_vals;
            
            // Read column values into variable keypad_vals
            portd_vals = ((PIND & BITMASK_D) >> 6);
            portb_vals = ((PINB & BITMASK_B) << 2);
            keypad_vals = portd_vals | portb_vals;
            keypad_vals &= 0b11110000;
            
            // Combine row and column values
            key_pressed |= keypad_vals;
            
            
            if (key_pressed == 0b01110111) {
                // Key 1 pressed
                given_password[idx] = '1';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b01111011) {
                // Key 2 pressed
                given_password[idx] = '2';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b01111101) {
                // Key 3 pressed
                given_password[idx] = '3';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b01111110) {
                // A
                given_password[idx] = 'A';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b10110111) {
                // 4
                given_password[idx] = '4';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b10111011) {
                // 5
                given_password[idx] = '5';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b10111101) {
                // 6
                given_password[idx] = '6';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b10111110) {
                // B
                given_password[idx] = 'B';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b11010111) {
                // 7
                given_password[idx] = '7';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b11011011) {
                // 8
                given_password[idx] = '8';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b11011101) {
                // 9
                given_password[idx] = '9';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b11011110) {
                // C
                given_password[idx] = 'C';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b11100111) {
                // Backspace button (*)
                given_password[idx - 1] = '\0';
                idx -= 2;
                printf("\n\r");
				printf(given_password);
				continue;
            }
            else if (key_pressed == 0b11101011) {
                // 0
                given_password[idx] = '0';
				printf(&given_password[idx]);
            }
            else if (key_pressed == 0b11101101) {
                // #
				//printf("%c", given_password);
                int pw_validity = compare(password, given_password);
                printf("\n\rpw_validity %d\n\r", pw_validity);
				idx = 0;
				return pw_validity;
				//given_password[0] = '\0';
            }
            else if (key_pressed == 0b11101110) {
                // D
                given_password[idx] = 'D';
				printf(&given_password[idx]);
            }
            
            /* Initialization for new iteration of while loop */
            // Set digital pins 6-9 (rows) as input and 10-13 (columns) as output
            DDRD &= 0b00111111;
            DDRB &= 0b11111100;
            DDRB |= 0b00111100;
            _delay_ms(1);
            
            // Power the row pins
            PORTD |= 0b11000000;
            PORTB |= 0b00000011;
            PORTB &= 0b11000011;
            _delay_ms(1);

            key_pressed = 0;
            idx +=1;
			_delay_ms(500); // Delay to avoid one key press to be interpreted as two
        }
    }
}
