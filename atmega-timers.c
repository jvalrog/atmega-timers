//      atmega-timers.c
//      
//      Copyright 2011 Javier Valencia <javiervalencia80@gmail.com>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//      
//      

#include "atmega-timers.h"

void (*_t0_func)();
void (*_t1_func)();
void (*_t2_func)();

void timer0(uint8_t prescaler, uint8_t ticks, void (*f)()) {
	TIMSK0 &= ~(_BV(OCIE0A));				// disable interrupt
	_t0_func = f;						// assign user function
	OCR0A = ticks;						// set top value
	TCCR0A = _BV(WGM01);				// set CTC mode
	TCCR0B = prescaler;					// set prescaler
	TCNT0 = 0;							// reset TCNT counter register
	TIMSK0 |= _BV(OCIE0A);				// enable interrupt
}

void timer0_stop() {
	TCCR0B = 0;							// set prescaler to none, disabling timer
}

#ifdef ENABLE_TIMER0
ISR(TIMER0_COMPA_vect) {
	_t0_func();
}
#endif

void timer1(uint8_t prescaler, uint16_t ticks, void (*f)()) {
	TIMSK1 &= ~(_BV(OCIE1A));
	_t1_func = f;
	OCR1A = ticks;
	TCCR1A = 0;
	TCCR1B = prescaler | _BV(WGM12);
	TCNT1 = 0;
	TIMSK1 |= _BV(OCIE1A);
}

void timer1_stop() {
	TCCR1B = 0;
}

#ifdef ENABLE_TIMER1
ISR(TIMER1_COMPA_vect) {
	_t1_func();
}
#endif

void timer2(uint8_t prescaler, uint8_t ticks, void (*f)()) {
	TIMSK2 &= ~(_BV(OCIE2A));
	_t2_func = f;
	OCR2A = ticks;
	ASSR = 0;
	TCCR2A = _BV(WGM21);
	TCCR2B = prescaler;
	TCNT2 = 0;
	TIMSK2 |= _BV(OCIE2A);
}

void timer2_stop() {
	TCCR2B = 0;
}

#ifdef ENABLE_TIMER2
ISR(TIMER2_COMPA_vect) {
	_t2_func();
}
#endif

void wait0(uint8_t prescaler, uint8_t ticks) {
	if (ticks == 0)
		return;						// return if no ticks to count
	TIMSK0 &= ~(_BV(OCIE0A));			// disable compare interrupt
	OCR0A = ticks;					// set top value
	TCCR0A = _BV(WGM01);			// set CTC mode
	TCCR0B = prescaler;				// set prescaler
	TCNT0 = 0;						// reset TCNT counter register
	TIFR0 |= _BV(OCF0A);			// reset compare flag
	while(!(TIFR0 & _BV(OCF0A)));	// wait till compare flag goes up
	TCCR0B = 0;						// stop timer to save energy
}

void wait1(uint8_t prescaler, uint16_t ticks) {
	if (ticks == 0)
		return;
	TIMSK1 &= ~(_BV(OCIE1A));
	OCR1A = ticks;
	TCCR1A = 0;
	TCCR1B = prescaler | _BV(WGM12);
	TCNT1 = 0;
	TIFR1 |= _BV(OCF1A);
	while(!(TIFR1 & _BV(OCF1A)));
	TCCR1B = 0;
}

void wait2(uint8_t prescaler, uint8_t ticks) {
	if (ticks == 0)
		return;
	TIMSK2 &= ~(_BV(OCIE2A));
	ASSR = 0;
	OCR2A = ticks;
	TCCR2A = _BV(WGM21);
	TCCR2B = prescaler;
	TCNT2 = 0;
	TIFR2 |= _BV(OCF2A);
	while(!(TIFR2 & _BV(OCF2A)));
	TCCR2B = 0;
}
