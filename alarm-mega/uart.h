#define F_CPU 16000000UL
#define FOSC 16000000UL	// Clock speed
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

void USART_init(unsigned int ubrr);
//void USART_transmit(int data);
unsigned char USART_receive(void);



