#include "inputs.h"
#include "hw_inputs.h"

volatile uint8_t inputsReg;

void initInputs()
{
    initHWInputs();
    inputsReg=0;
}


uint8_t readInput(uint8_t index)
{
    return (inputsReg&(1<<index));
}


void loopInputs()
{
    inputsReg=readWHInputs();
}
