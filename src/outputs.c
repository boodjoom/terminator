#include "outputs.h"
#include "hw_outputs.h"

volatile uint8_t outputsReg;


uint8_t readOutput(uint8_t index)
{
    return (outputsReg&(1<<index));
}


void writeOutput(uint8_t index, uint8_t value)
{
    if(value==0)
        outputsReg&=~(1<<index);
    else
        outputsReg|=(1<<index);
}


void initOutputs()
{
    initHWOutputs();
}


void loopOutputs()
{
    writeHWOutputs(outputsReg);
}
