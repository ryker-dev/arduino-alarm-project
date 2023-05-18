/*
 * UART communication between UNO and computer
 */ 

#include "uart.h"
#include <avr/io.h>
#include <util/setbaud.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern uint8_t timerCount;

void USART_init(unsigned int ubrr) {
	// Set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	// Set frame format: 8data, 2stop bit
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void USART_transmit(char data) {
	// Wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)));
    
	// Put data into buffer, send the data
	UDR0 = data;
}

char USART_receive(void) {
    
	// Wait for data to be received
	while(!(UCSR0A & (1<<RXC0))) {
        if (timerCount >= TIMEOUT) { // If timer has run for 3s
            printf("TIME RAN OUT (IN UART)");
            
            // Stop timer
            TIMSK1 = (0 << OCIE1A);
            timerCount = 0;
        }
    }
	printf("UART state: %c\n\r", UDR0);
	char result = UDR0;
	UCSR0A |= (1 << 0);
	//RXC0 |= (1 << 0);
	// Get and return received data from buffer
	return result;
}


