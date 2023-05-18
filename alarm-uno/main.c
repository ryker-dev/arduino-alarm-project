#include "uart.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "password.h"

#define IDLE 'i'
#define DISARMED 'p'
#define TRIGGERED 't'
#define ALARM_WRONGPASSWORD 'w'
#define ALARM_TIMEOUT 'o'

// Wait for the sensor to detect motion
int motionDetection(void) {
    // Set the motion sensor pin (Uno digital pin 3) as an input
    DDRD |= (0 << DDD3);
    
    // Wait until motion is detected and return 1
    while (1) {
        if (PIND & (1 << PD3))
        {
            return 1;
        }
    }
}

int main(void) {
    //char input;
	
	/* Hook URT stream to std */
    FILE uart_output = FDEV_SETUP_STREAM(USART_transmit, NULL, _FDEV_SETUP_WRITE);
    FILE uart_input = FDEV_SETUP_STREAM(NULL, USART_receive, _FDEV_SETUP_READ);
    stdout = &uart_output;
    stdin = &uart_input;
    
    USART_init(UBRR);
    
    motionDetection();
    
    int valid_password = 0;
    while(1) { 
        
		//printf("\n\rGive password:\n\r");
		valid_password = check_password();
		if (valid_password) {
			USART_transmit(DISARMED);
		}
		
		_delay_ms(1000);
    }
}

