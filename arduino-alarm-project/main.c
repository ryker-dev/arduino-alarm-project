/*
 * arduino-alarm-project.c
 *
 * Created: 27/03/2023 23:47:31
 * Author : Ryker
 */ 

#include "uart.h"
#include <avr/io.h>
#include <stdio.h>
#include "password.h"
    
    
int main(void) {
    /*char input;
    FILE uart_output = FDEV_SETUP_STREAM(USART_transmit, NULL, _FDEV_SETUP_WRITE);
    FILE uart_input = FDEV_SETUP_STREAM(NULL, USART_receive, _FDEV_SETUP_READ);
    stdout = &uart_output;
    stdin = &uart_input;
    
    USART_init(UBRR);*/
    
    check_password();
    
    while(1) {  
    }
}

