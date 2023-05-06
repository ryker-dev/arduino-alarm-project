#include <avr/io.h>
#include <util/delay.h>

int check_password(void);
int compare(char *password, char *given_password);
