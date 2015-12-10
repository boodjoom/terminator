#ifndef OUTPUTS
#define OUTPUTS

#include "stm8s_conf.h"

void writeOutput(uint8_t index, uint8_t value);
uint8_t readOutput(uint8_t index);
void initOutputs();
void loopOutputs();

#endif // OUTPUTS

