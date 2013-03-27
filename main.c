#define TRIGGER PC0
#define ECHO PC1
#define SCALEuS 10

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

int main(void)
{
	uint16_t i, distance;
	char *string;

	PORTC = 0;
	DDRC = _BV(TRIGGER);

	string = malloc(20);
	uart_init(0);
	uart_printstr(0, "Hello World!\n");

	while (1) {
		i = 0;
		PORTC |= _BV(TRIGGER);
		_delay_us(10);
		PORTC = 0;
		loop_until_bit_is_set(PINC, ECHO);
		
		while (bit_is_set(PINC, ECHO)) {
			_delay_us(SCALEuS);
			i++;
		}

		/*
		 * speed = ((i * SCALEuS)/1000000) * 340 / 2
		 * where:
		 * i * SCALEuS is the duration in uS of the signal.
		 * (i * SCALEuS)/1000000 is the same in seconds.
		 * 340 is the speed of the sound and
		 * /2 we need only half of the way.
		 * The simplyfied formula in cm.
		 * 340 mm/msec = 34cm/msec = 0.029 msec/cm = 29 uS/cm
		 * dist (cm) = T (uS) / 29 /2.
		 *
		 */
		distance = i * SCALEuS /58;
		string = utoa(i, string, 10);
		uart_printstr(0, string);
		uart_printstr(0, " ");
		string = utoa(distance, string, 10);
		uart_printstr(0, string);
		uart_printstr(0, "\n\r");
		_delay_ms(100);
	}

	return(0);
}
