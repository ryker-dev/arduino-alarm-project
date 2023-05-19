#define F_CPU 16000000UL
#define FOSC 16000000UL	// Clock speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

// Define the timeout when alarm starts if no password has been given
#define TIMEOUT 30

void USART_init(unsigned int ubrr);
void USART_transmit(char data);
char USART_receive(void);



