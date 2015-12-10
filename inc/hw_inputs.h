#ifndef HW_INPUTS
#define HW_INPUTS

#include "stm8s_conf.h"

#define INPUT_ACTIVE_LEVEL RESET

void initHWInputs();
uint8_t readWHInputs();

#endif // HW_INPUTS

