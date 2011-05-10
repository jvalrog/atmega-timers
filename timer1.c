//      timer1.c
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

#include "timer1.h"

void (*_t1_func)();
volatile uint16_t _t1_loops;
volatile uint16_t _t1_iter;

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
