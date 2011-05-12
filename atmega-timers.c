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
volatile uint32_t _t0_loops;
volatile uint32_t _t0_iter;
volatile uint8_t _t0_offset;

void (*_t1_func)();
volatile uint32_t _t1_loops;
volatile uint32_t _t1_iter;
volatile uint16_t _t1_offset;

void (*_t2_func)();
volatile uint32_t _t2_loops;
volatile uint32_t _t2_iter;
volatile uint8_t _t2_offset;

void timer0(uint8_t prescaler, uint32_t ticks, void (*f)()) {
	TIMSK0 = 0;
	_t0_func = f;
	_t0_loops = ticks / 256U;
	_t0_iter = 0;
	_t0_offset = ticks - (_t0_loops * 256U);
	if (ticks >= 256U)
		OCR0A = 255;
	else
		OCR0A = ticks;
	TCCR0A = 2;
	TCCR0B = prescaler;
	TCNT0 = 0;
	TIMSK0 = 2;
}

ISR(TIMER0_COMPA_vect) {
	TIMSK0 = 0;
	_t0_iter++;
	if (_t0_iter == _t0_loops) {
		if (_t0_offset > 0) {
			TCNT0 = 255 - _t0_offset;
		} else {
			_t0_iter = 0;
			_t0_func();
		}
	} else if (_t0_iter > _t0_loops) {
		_t0_iter = 0;
		_t0_func();
	}
	TIMSK0 = 2;
}

void timer1(uint8_t prescaler, uint32_t ticks, void (*f)()) {
	TIMSK1 = 0;
	_t1_func = f;
	_t1_loops = ticks / 65536UL;
	_t1_iter = 0;
	_t1_offset = ticks - (_t1_loops * 65536UL);
	if (ticks >= 65536UL)
		OCR1A = 65535U;
	else
		OCR1A = ticks;
	TCCR1A = 0;
	TCCR1B = prescaler | (1<<WGM12);
	TCNT1 = 0;
	TIMSK1 = 2;
}

ISR(TIMER1_COMPA_vect) {
	TIMSK1 = 0;
	_t1_iter++;
	if (_t1_iter == _t1_loops) {
		if (_t1_offset > 0) {
			TCNT1 = 65535U - _t1_offset;
		} else {
			_t1_iter = 0;
			_t1_func();
		}
	} else if (_t1_iter > _t1_loops) {
		_t1_iter = 0;
		_t1_func();
	}
	TIMSK1 = 2;
}

void timer2(uint8_t prescaler, uint32_t ticks, void (*f)()) {
	TIMSK2 = 0;
	_t2_func = f;
	_t2_loops = ticks / 256U;
	_t2_iter = 0;
	_t2_offset = ticks - (_t2_loops * 256U);
	if (ticks >= 256U)
		OCR2A = 255;
	else
		OCR2A = ticks;
	ASSR = 0;
	TCCR2A = 2;
	TCCR2B = prescaler;
	TCNT2 = 0;
	TIMSK2 = 2;
}

ISR(TIMER2_COMPA_vect) {
	TIMSK2 = 0;
	_t2_iter++;
	if (_t2_iter == _t2_loops) {
		if (_t2_offset > 0) {
			TCNT2 = 255 - _t2_offset;
		} else {
			_t2_iter = 0;
			_t2_func();
		}
	} else if (_t2_iter > _t2_loops) {
		_t2_iter = 0;
		_t2_func();
	}
	TIMSK2 = 2;
}
