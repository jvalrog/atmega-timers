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
volatile uint16_t _t0_loops;
volatile uint16_t _t0_iter;

void (*_t1_func)();
volatile uint16_t _t1_loops;
volatile uint16_t _t1_iter;

void (*_t2_func)();
volatile uint16_t _t2_loops;
volatile uint16_t _t2_iter;

void timer0(uint8_t prescaler, uint8_t top, uint16_t loops, void (*f)()) {
	TIMSK0 = 0;
	OCR0A = top;
	TCCR0A = 2; // CTC mode
	TCCR0B = prescaler;
	TCNT0 = 0;
	if (f) {
		_t0_func = f;
		_t0_loops = loops;
		_t0_iter = 0;
		TIMSK0 = 2; // enable
	}
}

ISR(TIMER0_COMPA_vect) {
	_t0_iter++;
	if (_t0_iter == _t0_loops) {
		_t0_iter = 0;
		_t0_func();
	}
}

void timer1(uint8_t prescaler, uint16_t top, uint16_t loops, void (*f)()) {
	TIMSK1 = 0;
	OCR1A = top;
	TCCR1A = 0; // CTC mode
	TCCR1B = prescaler | (1<<WGM12);
	TCNT1 = 0;
	if (f) {
		_t1_func = f;
		_t1_loops = loops;
		_t1_iter = 0;
		TIMSK1 = 2; // enable
	}
}

ISR(TIMER1_COMPA_vect) {
	_t1_iter++;
	if (_t1_iter == _t1_loops) {
		_t1_iter = 0;
		_t1_func();
	}
}

void timer2(uint8_t prescaler, uint8_t top, uint16_t loops, void (*f)()) {
	TIMSK2 = 0;
	OCR2A = top;
	ASSR = 0;
	TCCR2A = 2; // CTC mode
	TCCR2B = prescaler;
	TCNT2 = 0;
	if (f) {
		_t2_func = f;
		_t2_loops = loops;
		_t2_iter = 0;
		TIMSK2 = 2; // enable
	}
}

ISR(TIMER2_COMPA_vect) {
	_t2_iter++;
	if (_t2_iter == _t2_loops) {
		_t2_iter = 0;
		_t2_func();
	}
}
