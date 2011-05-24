# atmega-timers

`atmega-timers` is an Arduino/Avr compatible library to control timers 0, 1 and 2.

## Description

This library contains several functions to use the timers in different ways.

- One way is using the timers to execute a function on a defined period, indefinitely.

		void timer0(uint8_t prescaler, uint8_t ticks, void (*f)())
		void timer1(uint8_t prescaler, uint16_t ticks, void (*f)())
		void timer2(uint8_t prescaler, uint8_t ticks, void (*f)())

		void timer0_stop()
		void timer1_stop()
		void timer2_stop()

	- `prescaler` are predefined constants in the header file. For example:

			TIMER0_PRESCALER_8
			TIMER0_PRESCALER_64
			...

	- `ticks` are the number of steps the timer will count. Current limits are:

			timer0: 0 - 255
			timer1: 0 - 65535
			timer2: 0 - 255
	
	- `f` is the function to execute after all ticks are consumed. Must be declared `void`
	with no parameters:
		
			void sample() {
				...
			}

	- `timerX_stop()` disables that timer by setting prescaler to "none". Energy saving feature.
	
	- You can disable interrupt definition if you want to use that timer for your own
	purposes. Just comment or delete one of those lines inside `atmega-timers.h` file:
	
			#define ENABLE_TIMER0
			#define ENABLE_TIMER1
			#define ENABLE_TIMER2
		
- Other way is implementing the traditional `delay` routine. The function will `block-wait` until
the count is done.

		void wait0(uint8_t prescaler, uint8_t ticks)
		void wait1(uint8_t prescaler, uint16_t ticks)
		void wait2(uint8_t prescaler, uint8_t ticks)

	- `prescaler` are predefined constants in the header file. For example:

			TIMER0_PRESCALER_8
			TIMER0_PRESCALER_64
			...

	- `ticks` are the number of steps the timer will count. Current limits are:

			timer0: 0 - 255
			timer1: 0 - 65535
			timer2: 0 - 255

## Usage

You need to know your CPU clock frequency before setting the timers.

1. Divide CPU clock by selected prescaler:
	
		16000000 / 64 = 250000 Hz

2. Get timer period:
	
		1 / 250000 = 4 us
	
3. Divide your desired period by timer period, for example 20 milliseconds:
	
		20000 us / 4 us = 5000 ticks

4. Use timer1, as timer0 and timer2 can't support more than 256 ticks:
	
		timer1(TIMER1_PRESCALER_64, 5000U, do_something);

5. Enable global interrupts:
	
		sei();
	
## Sample Code

- Using `wait*` functions:

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

- Using `timer*` functions:

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
			timer1(TIMER1_PRESCALER_1024, 7812U, toggle);
			
			// enable global interrupts
			sei();

			while(1) {
				// your code goes here
			}
		}

Both examples have the same result.

## Running it in Arduino

1. Download the source code by using the Download Button on this page
2. Rename and install the library as: `{arduino_path}/libraries/AtmegaTimers`
3. Open Arduino and go to "Import Library" option. Choose AtmegaTimers from menu.

## Atmel Model Support

It should work with a long range of devices, for example:

- atmega48, 88, 168, 328
- atmega164, 324, 644, 1284
- atmega640, 1280, 1281, 2560, 2561
- atmega325, 645
- ...
