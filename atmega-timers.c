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
	TIMSK0 = 0;
	_t0_func = f;
	OCR0A = ticks;
	TCCR0A = 2;
	TCCR0B = prescaler;
	TCNT0 = 0;
	TIMSK0 = 2;
}

ISR(TIMER0_COMPA_vect) {
	TIMSK0 = 0;
	_t0_func();
	TIMSK0 = 2;
}

void timer1(uint8_t prescaler, uint16_t ticks, void (*f)()) {
	TIMSK1 = 0;
	_t1_func = f;
	OCR1A = ticks;
	TCCR1A = 0;
	TCCR1B = prescaler | (1<<WGM12);
	TCNT1 = 0;
	TIMSK1 = 2;
}

ISR(TIMER1_COMPA_vect) {
	TIMSK1 = 0;
	_t1_func();
	TIMSK1 = 2;
}

void timer2(uint8_t prescaler, uint8_t ticks, void (*f)()) {
	TIMSK2 = 0;
	_t2_func = f;
	OCR2A = ticks;
	ASSR = 0;
	TCCR2A = 2;
	TCCR2B = prescaler;
	TCNT2 = 0;
	TIMSK2 = 2;
}

ISR(TIMER2_COMPA_vect) {
	TIMSK2 = 0;
	_t2_func();
	TIMSK2 = 2;
}

void wait0(uint8_t prescaler, uint8_t ticks) {
	TIMSK0 = 0;
	OCR0A = ticks;
	TCCR0A = 2;
	TCCR0B = prescaler;
	TCNT0 = 0;
	TIFR0 = 2;
	while(!(TIFR0 & 2));
}

void wait1(uint8_t prescaler, uint16_t ticks) {
	TIMSK1 = 0;
	OCR1A = ticks;
	TCCR1A = 0;
	TCCR1B = prescaler | (1<<WGM12);
	TCNT1 = 0;
	TIFR1 = 2;
	while(!(TIFR1 & 2));
}

void wait2(uint8_t prescaler, uint8_t ticks) {
	TIMSK2 = 0;
	ASSR = 0;
	OCR2A = ticks;
	TCCR2A = 2;
	TCCR2B = prescaler;
	TCNT2 = 0;
	TIFR2 = 2;
	while(!(TIFR2 & 2));
}
