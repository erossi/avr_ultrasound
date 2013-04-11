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

#ifndef SONAR_H
#define SONAR_H

#define TRIGGER_POUT PB0
#define TRIGGER_PORT PORTB
#define TRIGGER_DDR DDRB

#define ECHO_PORT_IN PINC
#define ECHO_PORT_IN2 PIND
#define ECHO_PIN0 PINC0
#define ECHO_PIN1 PINC1
#define ECHO_PIN2 PINC2
#define ECHO_PIN3 PINC3
#define ECHO_PIN4 PINC4
#define ECHO_PIN5 PINC5
#define ECHO_PIN6 PIND4
#define ECHO_PIN7 PIND5
#define ECHO_PIN8 PIND6
#define ECHO_PIN9 PIND7

#define SCALEuS 10

#include "uart.h"
#include "rtc.h"

uint16_t sonar[10];
uint16_t sonar_start_flag;

void sonar_init(void);
void sonar_trigger(void);
void sonar_clear(void);
void sonar_set(void);
void sonar_print(char *string);

#endif
