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

/*! \file rtc.h
 * \brief low level clock.
 *
 * These functions will setup a global clock
 * based on hardware counter. The counter will start counting
 * at some CPU Frequency speed divided by the prescaler.
 * When it reach the CTC_MAX value the interrupt routine is called
 * incrementing the global rtc_us counter.
 *
 * FCPU/prescaler / CTC_MAX
 * 
 * where in the Arduino example we can have:
 *
 * 16000000 hz/8 / 20 = 100000 (10uS)
 *
 * meaning the rtc_us will be incremented every 10uS
 */

#ifndef RTC_H
#define RTC_H

/*! The max value of the internal counter. */
#define CTC_MAX 20

/*!
 * Global counter used in interrupt.
 * see prescaler setup for details.
 */
volatile unsigned long rtc_us;

void rtc_setup(void);
void rtc_start(void);
void rtc_stop(void);
void rtc_clear(void);

#endif
