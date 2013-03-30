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

#define TRIGGER_POUT PB0
#define TRIGGER_PORT PORTB
#define TRIGGER_DDR DDRB

#define ECHO_PORT_IN PINC
#define ECHO_PIN0 PINC0
#define ECHO_PIN1 PINC1
#define ECHO_PIN2 PINC2
#define ECHO_PIN3 PINC3
#define ECHO_PIN4 PINC4
#define ECHO_PIN5 PINC5

#define SCALEuS 10

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "rtc.h"

uint16_t sonar[6];
uint8_t sonar_start_flag;

void init_port(void)
{
	/* Set the trigger pin to 0 */
	TRIGGER_PORT &= ~_BV(TRIGGER_POUT);
	/* Pin trigger set to output. */
	TRIGGER_DDR |= _BV(TRIGGER_POUT);
}

void send_trigger(void)
{
	TRIGGER_PORT |= _BV(TRIGGER_POUT);
	_delay_us(10);
	TRIGGER_PORT &= ~_BV(TRIGGER_POUT);
}

void sonar_clear(void)
{
	uint8_t i;

	sonar_start_flag = 0;

	for (i=0; i<6; i++)
		sonar[i] = 0;
}

void sonar_set(void)
{
	if (sonar_start_flag & _BV(0)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN0))
			sonar[0] = rtc_us - sonar[0];
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN0))
			sonar[0] = rtc_us;
	}

	if (sonar_start_flag & _BV(1)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN1))
			sonar[1] = rtc_us - sonar[1];
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN1))
			sonar[1] = rtc_us;
	}

	if (sonar_start_flag & _BV(2)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN2))
			sonar[2] = rtc_us - sonar[2];
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN2))
			sonar[2] = rtc_us;
	}

	if (sonar_start_flag & _BV(3)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN3))
			sonar[3] = rtc_us - sonar[3];
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN3))
			sonar[3] = rtc_us;
	}

	if (sonar_start_flag & _BV(4)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN4))
			sonar[4] = rtc_us - sonar[4];
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN4))
			sonar[4] = rtc_us;
	}

	if (sonar_start_flag & _BV(5)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN5))
			sonar[5] = rtc_us - sonar[5];
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN5))
			sonar[5] = rtc_us;
	}
}

void sonar_print(char *string)
{
	uint8_t i;

	for (i=0; i<6; i++) {
		string = utoa(sonar[i], string, 10);
		uart_printstr(0, string);
		uart_printstr(0, " ");
	}

	uart_printstr(0, "\n");
}

int main(void)
{
	char *string;

	init_port();
	rtc_setup();

	/* Start the serial port. */
	string = malloc(20);
	uart_init(0);
	uart_printstr(0, "Hello World!\n");
	rtc_start();

	while (1) {
		send_trigger();
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
