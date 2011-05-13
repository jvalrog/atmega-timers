#include <avr/io.h>
#include "atmega-timers.h"

// toggle PORTB status
void toggle() {
	static uint8_t output = 0xff;

	PORTB = output;
	output = !output;
}

void main() {
	// set all pins of PORTB as output
	DDRB = 0xff;
	
	// toggle PORTB every 500ms (using 16Mhz clock)
	while(1) {
		toggle();
		wait1(TIMER1_PRESCALER_1024, 7812U);
	}
}
