#ifndef TIMERS
#define TIMERS

#include "stm8s_conf.h"

void initTimers();
void timerSet_10ms(uint8_t index, uint32_t value);
void timerSet_100ms(uint8_t index, uint32_t value);
void timerSet_1s(uint8_t index, uint32_t value);
void timerReset(uint8_t index);
uint8_t timerGet(uint8_t index);
uint8_t timerInline_10ms(uint8_t index, uint32_t value);
uint8_t timerInline_100ms(uint8_t index, uint32_t value);
uint8_t timerInline_1s(uint8_t index, uint32_t value);

#endif // TIMERS

