#include "hw_outputs.h"

GPIO_Pin_TypeDef hwoutputsPins[5]={
    GPIO_PIN_3,
    GPIO_PIN_2,
    GPIO_PIN_1,
    GPIO_PIN_4,
    GPIO_PIN_3
};

GPIO_TypeDef* hwoutputsPorts[5]={
    GPIOA,
    GPIOA,
    GPIOA,
    GPIOD,
    GPIOD
};

void initHWOutputs()
{
    uint8_t i;
    for(i=0;i<5;i++)
        GPIO_Init(hwoutputsPorts[i],hwoutputsPins[i],GPIO_MODE_OUT_PP_LOW_FAST);
}


void writeHWOutputs(uint8_t mask)
{
    uint8_t i;
    for(i=0;i<5;i++)
    {
        if(mask&(1<<i))
            GPIO_WriteHigh(hwoutputsPorts[i],hwoutputsPins[i]);
        else
            GPIO_WriteLow(hwoutputsPorts[i],hwoutputsPins[i]);
    }
}
