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
 * IRQ wakes up on the timer oveflow and increment the global
 * micro seconds.
 */
ISR(TIMER0_COMPA_vect)
{
	rtc_us++;
}

/*! Zeroing the global counter.
 */
void rtc_clear(void)
{
	rtc_us=0;
}

/*!
 * Setup timer/counter.
 *
 * We use the CTC (Clear Timer on Compare match) mode in which
 * the counter will be compared to the OCR0A value and if they
 * match an interrupt will be raised. The interrupt routine
 * TIMER0_COMPA_vect will be called and the counter will
 * restart from the BOTTOM.
 *
 * \bug The global interrupt enable should be something
 * done by the main program, other routine my need to
 * initialize IRQ routines before enable the global IRQ.
 */
void rtc_setup(void)
{
	/* CTC counter mode */
	TCCR0A = _BV(WGM01);
	TCCR0B = 0;

	/* Set the CTC MAX value. */
	OCR0A = CTC_MAX;

	/* Enable interrupt on timer compare match */
	TIMSK0 = _BV(OCIE0A);

	/* clear the rtc_us value. */
	rtc_clear();

	/* enable interrupt. */
	sei();
}

/*!
 * Setup prescaler and start counter.
 */
void rtc_start(void)
{
	/* start counter prescaled by 8 */
        TCCR0B = _BV(CS01);
}

/*!
 * Stop the counter.
 *
 * Disable the interrupt and remove the link
 * to the interrupt routine.
 *
 * \bug The interrupt can be required enable by
 * other part of the program.
 * It shouldn't be totally disabled here.
 */
void rtc_stop(void)
{
	cli();
	TCCR0B = 0;
}
