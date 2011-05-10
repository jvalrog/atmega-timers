## Avr-Timers

Arduino/Avr compatible libraries to control timers 0, 1 and 2.

### Description

Those libraries work by setting up the timer and executing a user-defined function after
that time, repeating indifenitely.

When the "top" value is reached by the timer, an interrupt will happen. In this interrupt,
the number of loops will increase till "loops" are reached.

When "loops" are reached, the user defined "f" function is called.

The functions look all the same:

		void timer0(uint8_t prescaler, uint8_t top, uint16_t loops, void (*f)())
		void timer1(uint8_t prescaler, uint16_t top, uint16_t loops, void (*f)())
		void timer2(uint8_t prescaler, uint8_t top, uint16_t loops, void (*f)())

Prescaler constants are defined in each header file for easy access.

There is only a difference between timer1 and both timer0 and timer2. It's the resolution.
Timer1 use 16bit registers while timer0 and timer2 are 8bit.

The funcion "f" is something like this:

	void myfunction() {
		...
	}
	
### Usage

Let's run a function every 50 milliseconds using timer0 in arduino (16Mhz atmega168/328):

1. Set a prescaler value that will allow timer to count up to 50 milliseconds
	
	TIMER0_PRESCALER_64
		
2. Divide cpu frequency by prescaler: 16000000 / 64 = 250000 Hz

3. Get the period of the timer: 1 / 250000 = 4 us
	
4. Every 4us, timer0 will increase by 1. Now let's divide 50ms by 4us:
	
	50000us / 4us = 12500 ticks
	
5. As 12500 *timer ticks* are too long for our 8 bit register, let's divide it by 50:
	
	12500 / 50 = 250
		
6. 250 ticks are a valid number to store in an 8 bit register, so our number of loops
will be 50.
	
7. You are done.
	
	50 loops * 250 ticks * 4us = 50ms

### Sample Code
	
	#include "timer0.h"
	
	void myfunction() {
		// do something
	}
	
	void main() {
		timer0(TIMER0_PRESCALER_64, 250, 50, myfunction);
		sei();
		while(1) {
			// main loop
		}
	}

	// REMEMBER TO ACTIVATE GLOBAL INTERRUPTS WITH *sei()*

