#include "uart.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "password.h"
    
int main(void) {
    //char input;
	
	/* Hook URT stream to std */
    FILE uart_output = FDEV_SETUP_STREAM(USART_transmit, NULL, _FDEV_SETUP_WRITE);
    FILE uart_input = FDEV_SETUP_STREAM(NULL, USART_receive, _FDEV_SETUP_READ);
    stdout = &uart_output;
    stdin = &uart_input;
    
    USART_init(UBRR);
    
    check_password();
    
    while(1) { 
		//check_password();
		USART_transmit(1);
		_delay_ms(1000);
    }
}

