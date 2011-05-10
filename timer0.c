//      timer0.c
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

#include "timer0.h"

void (*_t0_func)();
volatile uint16_t _t0_loops;
volatile uint16_t _t0_iter;

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
