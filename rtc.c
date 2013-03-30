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

/*!
  \file rtc.c
  \brief Counters handler and IRQ routine.
  */

#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "rtc.h"

/*!
  IRQ wakes up on the timer oveflow and increment the global micro seconds.
 */
ISR(TIMER0_COMPA_vect)
{
	rtc_us++;
}

void rtc_clear(void)
{
	rtc_us=0;
}

/*! setup timer/counter. */
void rtc_setup(void)
{
	TCCR0A = _BV(WGM01);
	TCCR0B = 0;
	OCR0A = 20;

	/*! enable interrupt on timer overflow */
	TIMSK0 = _BV(OCIE0A);
	rtc_clear();
	sei();
}

/*! setup prescaler to scale to 1 sec counter and start counter. */
void rtc_start(void)
{
	/*! counter prescaler 1024 */
        TCCR0B = _BV(CS01);
}

/*! stop the counter. */
void rtc_stop(void)
{
	cli();
	TCCR0B = 0;
}
