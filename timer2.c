#include "timer2.h"

void (*_t2_func)();
volatile uint16_t _t2_loops;
volatile uint16_t _t2_iter;

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
