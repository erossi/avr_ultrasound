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
#include <avr/io.h>
#include <util/delay.h>
#include "sonar.h"

void sonar_init(void)
{
	/* Set the trigger pin to 0 */
	TRIGGER_PORT &= ~_BV(TRIGGER_POUT);
	/* Pin trigger set to output. */
	TRIGGER_DDR |= _BV(TRIGGER_POUT);
}

void sonar_trigger(void)
{
	TRIGGER_PORT |= _BV(TRIGGER_POUT);
	_delay_us(10);
	TRIGGER_PORT &= ~_BV(TRIGGER_POUT);
}

void sonar_clear(void)
{
	uint8_t i;

	sonar_start_flag = 0;

	for (i=0; i<10; i++)
		sonar[i] = 0;
}

void sonar_set(void)
{
	if (sonar_start_flag & _BV(0)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN0)) {
			sonar[0] = rtc_us - sonar[0];
			sonar_start_flag &= ~_BV(0);
		}
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN0)) {
			sonar[0] = rtc_us;
			sonar_start_flag |= _BV(0);
		}
	}

	if (sonar_start_flag & _BV(1)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN1)) {
			sonar[1] = rtc_us - sonar[1];
			sonar_start_flag &= ~_BV(1);
		}
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN1)) {
			sonar[1] = rtc_us;
			sonar_start_flag |= _BV(1);
		}
	}

	if (sonar_start_flag & _BV(2)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN2)) {
			sonar[2] = rtc_us - sonar[2];
			sonar_start_flag &= ~_BV(2);
		}
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN2)) {
			sonar[2] = rtc_us;
			sonar_start_flag |= _BV(2);
		}
	}

	if (sonar_start_flag & _BV(3)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN3)) {
			sonar[3] = rtc_us - sonar[3];
			sonar_start_flag &= ~_BV(3);
		}
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN3)) {
			sonar[3] = rtc_us;
			sonar_start_flag |= _BV(3);
		}
	}

	if (sonar_start_flag & _BV(4)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN4)) {
			sonar[4] = rtc_us - sonar[4];
			sonar_start_flag &= ~_BV(4);
		}
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN4)) {
			sonar[4] = rtc_us;
			sonar_start_flag |= _BV(4);
		}
	}

	if (sonar_start_flag & _BV(5)) {
		if (bit_is_clear(ECHO_PORT_IN, ECHO_PIN5)) {
			sonar[5] = rtc_us - sonar[5];
			sonar_start_flag &= ~_BV(5);
		}
	} else {
		if (bit_is_set(ECHO_PORT_IN, ECHO_PIN5)) {
			sonar[5] = rtc_us;
			sonar_start_flag |= _BV(5);
		}
	}

	/* Second port */
	if (sonar_start_flag & _BV(6)) {
		if (bit_is_clear(ECHO_PORT_IN2, ECHO_PIN6)) {
			sonar[6] = rtc_us - sonar[6];
			sonar_start_flag &= ~_BV(6);
		}
	} else {
		if (bit_is_set(ECHO_PORT_IN2, ECHO_PIN6)) {
			sonar[6] = rtc_us;
			sonar_start_flag |= _BV(6);
		}
	}

	if (sonar_start_flag & _BV(7)) {
		if (bit_is_clear(ECHO_PORT_IN2, ECHO_PIN7)) {
			sonar[7] = rtc_us - sonar[7];
			sonar_start_flag &= ~_BV(7);
		}
	} else {
		if (bit_is_set(ECHO_PORT_IN2, ECHO_PIN7)) {
			sonar[7] = rtc_us;
			sonar_start_flag |= _BV(7);
		}
	}

	if (sonar_start_flag & _BV(8)) {
		if (bit_is_clear(ECHO_PORT_IN2, ECHO_PIN8)) {
			sonar[8] = rtc_us - sonar[8];
			sonar_start_flag &= ~_BV(8);
		}
	} else {
		if (bit_is_set(ECHO_PORT_IN2, ECHO_PIN8)) {
			sonar[8] = rtc_us;
			sonar_start_flag |= _BV(8);
		}
	}

	if (sonar_start_flag & _BV(9)) {
		if (bit_is_clear(ECHO_PORT_IN2, ECHO_PIN9)) {
			sonar[9] = rtc_us - sonar[9];
			sonar_start_flag &= ~_BV(9);
		}
	} else {
		if (bit_is_set(ECHO_PORT_IN2, ECHO_PIN9)) {
			sonar[9] = rtc_us;
			sonar_start_flag |= _BV(9);
		}
	}
}
