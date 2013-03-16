#define TRIGGER PC0
#define ECHO PC1

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

struct uartStruct *uartPtr;

int main(void)
{
	uint16_t i;
	char *string;

	PORTC = 0;
	DDRC = _BV(TRIGGER);

	string = malloc(20);
	uartPtr = uart_init();
	uart_printstr("Hello World!\n");

	while (1) {
		i = 0;
		PORTC |= _BV(TRIGGER);
		_delay_us(10);
		PORTC = 0;
		loop_until_bit_is_set(PINC, ECHO);
		
		while (bit_is_set(PINC, ECHO)) {
			_delay_us(100);
			i++;
		}

		string = utoa(i, string, 10);
		uart_printstr(string);
		uart_printstr("\n\r");
		_delay_ms(100);
	}

	return(0);
}
