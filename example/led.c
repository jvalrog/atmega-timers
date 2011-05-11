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
	
	// toggle PORTB each 500ms (using 16Mhz clock)
	timer0(TIMER0_PRESCALER_64, 125000, toggle);
	
	// enable global interrupts
	sei();

	while(1) {
		// do nothing
	}
}
