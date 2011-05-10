#ifndef timer2_h
#define timer2_h

#include <stdint.h>
#include <avr/interrupt.h>

#define TIMER2_PRESCALER_NONE 0
#define TIMER2_PRESCALER_1 1
#define TIMER2_PRESCALER_8 2
#define TIMER2_PRESCALER_32 3
#define TIMER2_PRESCALER_64 4
#define TIMER2_PRESCALER_128 5
#define TIMER2_PRESCALER_256 6
#define TIMER2_PRESCALER_1024 7

void timer2(uint8_t prescaler, uint8_t top, uint16_t loops, void (*f)());

#endif

