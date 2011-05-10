#ifndef timer1_h
#define timer1_h

#include <stdint.h>
#include <avr/interrupt.h>

#define TIMER1_PRESCALER_NONE 0
#define TIMER1_PRESCALER_1 1
#define TIMER1_PRESCALER_8 2
#define TIMER1_PRESCALER_64 3
#define TIMER1_PRESCALER_256 4
#define TIMER1_PRESCALER_1024 5

void timer1(uint8_t prescaler, uint16_t top, uint16_t loops, void (*f)());

#endif
