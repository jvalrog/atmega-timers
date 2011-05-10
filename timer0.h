#ifndef timer0_h
#define timer0_h

#include <stdint.h>
#include <avr/interrupt.h>

#define TIMER0_PRESCALER_NONE 0
#define TIMER0_PRESCALER_1 1
#define TIMER0_PRESCALER_8 2
#define TIMER0_PRESCALER_64 3
#define TIMER0_PRESCALER_256 4
#define TIMER0_PRESCALER_1024 5

void timer0(uint8_t prescaler, uint8_t top, uint16_t loops, void (*f)());

#endif

