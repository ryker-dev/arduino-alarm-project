/*
 * ex_9_1.c
 *
 * Created: 28.3.2023 10:11:30
 * Author : ainoal
 */ 

#define F_CPU 1000000
#define FOSC 16000000	// Clock speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

#include <avr/io.h>
#include <util/setbaud.h>
#include <stdio.h>

void USART_init(unsigned int ubrr);
void USART_transmit(unsigned char data);
unsigned char USART_receive(void);

int main(void) {
	char input;
	FILE uart_output = FDEV_SETUP_STREAM(USART_transmit, NULL, _FDEV_SETUP_WRITE);
	FILE uart_input = FDEV_SETUP_STREAM(NULL, USART_receive, _FDEV_SETUP_READ);
	
	USART_init(UBRR);
    
	stdout = &uart_output;
	stdin = &uart_input;
	
	while(1) {
		puts("Hello world!");
		input = getchar();
		printf("%c\n", input);
		
	}
}

void USART_init(unsigned int ubrr) {
	// Set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	// Enable receiver and transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	// Set frame format: 8data, 2stop bit
	UCSR0C = (1<<USBS0) | (3<<UCSZ00);
}

void USART_transmit(unsigned char data) {
	// Wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)));
	
	// Put data into buffer, send the data
	UDR0 = data;
}

unsigned char USART_receive(void) {
	// Wait for data to be received
	while(!(UCSR0A & (1<<RXC0)));
	
	// Get and return received data from buffer
	return UDR0;
}


