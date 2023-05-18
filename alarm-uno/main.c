#include "uart.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "password.h"

#define IDLE 0
#define DISARMED 1
#define ALARM 2
#define TRIGGERED_WRONGPASSWORD 3
#define TRIGGERED_TOOSLOW 4

int main(void) {
    //char input;
	
	/* Hook URT stream to std */
    FILE uart_output = FDEV_SETUP_STREAM(USART_transmit, NULL, _FDEV_SETUP_WRITE);
    FILE uart_input = FDEV_SETUP_STREAM(NULL, USART_receive, _FDEV_SETUP_READ);
    stdout = &uart_output;
    stdin = &uart_input;
    
    USART_init(UBRR);
    
    int valid_password = 0;
    while(1) { 
		printf("\n\rGive password:\n\r");
		valid_password = check_password();
		printf("%d", valid_password);
		if (valid_password == DISARMED) {
			USART_transmit(DISARMED);
		}
		
		_delay_ms(1000);
    }
}

