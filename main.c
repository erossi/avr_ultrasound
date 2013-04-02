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

	sonar_init();
	rtc_setup();

	/* Start the serial port. */
	string = malloc(20);
	uart_init(0);
	uart_printstr(0, "Hello World!\n");
	rtc_start();

	while (1) {
		sonar_trigger();
		sonar_clear();

		while (rtc_us < 6000)
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
		sonar_print(string);

		if (rtc_us > 10000)
			uart_printstr(0, "Warning! Time overrun.\n");

		while (rtc_us < 10000);

		rtc_clear();
	}

	return(0);
}
