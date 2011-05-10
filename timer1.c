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
