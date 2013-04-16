/* Copyright (C) 2013 Enrico Rossi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include "uart.h"
#include "rtc.h"
#include "sonar.h"

int main(void)
{
	char *string;
	uint16_t counter;
	uint8_t i;

	sonar_init();
	rtc_setup();

	/* Start the serial port. */
	string = malloc(20);
	counter = 0;
	uart_init(0);
	uart_printstr(0, "\n\nConnected!\n");
	rtc_start();

	while (1) {
		sonar_trigger();
		sonar_clear();

		while (rtc_us < 4000)
			sonar_set();

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

		string = utoa(counter, string, 10);
		uart_printstr(0, string);
		uart_printstr(0, " ");
		counter++;
		sonar_print(string);

		/* test to saturate the serial output line */
		/*
		for (i=0; i<11; i++) {
			string = utoa(12345, string, 10);
			uart_printstr(0, string);
			uart_printstr(0, " ");
		}

		uart_printstr(0, "\n");
		*/

		if (rtc_us > 5000)
			uart_printstr(0, "Warning! Time overrun.\n");

		while (rtc_us < 10000);

		rtc_clear();
	}

	return(0);
}
