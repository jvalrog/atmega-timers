# atmega-timers

`atmega-timers` is an Arduino/Avr compatible library to control timers 0, 1 and 2.

## Description

This library works by setting up the timers and executing a user-defined function after
that time, repeating indefinitely.

The functions are:

	void timer0(uint8_t prescaler, uint32_t ticks, void (*f)())
	void timer1(uint8_t prescaler, uint32_t ticks, void (*f)())
	void timer2(uint8_t prescaler, uint32_t ticks, void (*f)())

- `prescaler` are predefined constants in the header file. For example:

		TIMER0_PRESCALER_8
		TIMER0_PRESCALER_64
		...

- `ticks` are the number of steps the timer will count. Current limits are:

		timer0: 0 - 16777215
		timer1: 0 - 4294967295
		timer2: 0 - 16777215
	
- `f` is the function to execute after all ticks are consumed. Must be declared `void`
with no parameters:
	
		void sample() {
			...
		}
	
## Usage

You need to know your CPU clock frequency before setting the timers.

1. Divide CPU clock by selected prescaler:
	
		16000000 / 64 = 250000 Hz

2. Get timer period:
	
		1 / 250000 = 4 us
	
3. Divide your desired period by timer period, for example 20 milliseconds:
	
		20000 us / 4 us = 5000 ticks

4. Call the function:
	
		timer0(TIMER0_PRESCALER_64, 5000UL, toggle_bits);

5. Enable global interrupts:
	
		sei();
	
## Sample Code

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
		timer0(TIMER0_PRESCALER_64, 125000UL, toggle);
		
		// enable global interrupts
		sei();

		while(1) {
			// do nothing
		}
	}

## Running it in Arduino

Just rename `atmega-timers.c` to `atmega-timers.cpp` and install it as a normal library.

## Atmel Model Support

It should work with a long range of devices, for example:

- atmega48, 88, 168, 328
- atmega164, 324, 644, 1284
- atmega640, 1280, 1281, 2560, 2561
- atmega325, 645
- ...
