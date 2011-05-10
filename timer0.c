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
