/* Copyright (C) 2013, 2016 Enrico Rossi
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
#include <string.h>
#include <avr/pgmspace.h>
#include "usart.h"
#include "rtc.h"
#include "sonar.h"

void sonar_print(void)
{
	uint8_t i;

	for (i=0; i<10; i++) {
		usart->tx0_buffer = utoa(sonar[i], usart->tx0_buffer, 10);
		usart_printstr(0, NULL);
		usart_printstr(0, " ");
	}

	usart_printstr(0, "\n");
}

int main(void)
{
	uint16_t counter;

	usart_init();
	sonar_init();
	rtc_setup();

	counter = 0;
	usart_resume(0);
	strcpy_P(usart->tx0_buffer, PSTR("\nTsunami Simulator "));
	strcat_P(usart->tx0_buffer, PSTR(GITREL));
	strcat_P(usart->tx0_buffer, PSTR("\n\nConnected!\n"));
	usart_printstr(0, NULL);
	rtc_start();

	while (1) {
		/* send the trigger */
		sonar_trigger();
		/* clear all the data */
		sonar_clear();

		/*
		 * Wait 40mS maximum and collect all the
		 * data during the period.
		 */
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
		 */

		usart->tx0_buffer = utoa(counter, usart->tx0_buffer, 10);
		usart_printstr(0, NULL);
		usart_printstr(0, " ");
		counter++;
		sonar_print();

		/* test to saturate the serial output line
		 *
		 * In order to test if the print takes too long, substitute
		 * the sonar_print() above with:

		for (i=0; i<11; i++) {
			usart->tx0_buffer = utoa(12345, usart->tx0_buffer, 10);
			usart_printstr(0, string);
			usart_printstr(0, " ");
		}

		usart_printstr(0, "\n");
		*/

		/* if the counter has already reach 50mS,
		 * then this cycle takes too long.
		 */
		if (rtc_us > 5000)
			usart_printstr(0, "Warning! Time overrun.\n");

		/* Wait up to 50mS before restart */
		while (rtc_us < 5000);

		/* Restart the counter */
		rtc_clear();
	}

	return(0);
}
