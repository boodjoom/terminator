#include "hw_inputs.h"

GPIO_Pin_TypeDef hwinputsPins[8]={
    GPIO_PIN_2,
    GPIO_PIN_7,
    GPIO_PIN_6,
    GPIO_PIN_5,
    GPIO_PIN_4,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5
};

GPIO_TypeDef* hwinputsPorts[8]={
    GPIOD,
    GPIOC,
    GPIOC,
    GPIOC,
    GPIOC,
    GPIOC,
    GPIOB,
    GPIOB
};

void initHWInputs()
{
    uint8_t i;
    for(i=0;i<8;i++)
        GPIO_Init(hwinputsPorts[i],hwinputsPins[i],GPIO_MODE_IN_FL_IT);
}


uint8_t readWHInputs()
{
    uint8_t i, result=0;
    for(i=0;i<8;i++)
        if(GPIO_ReadInputPin(hwinputsPorts[i],hwinputsPins[i])==INPUT_ACTIVE_LEVEL)
        {
            result|=(i<<i);
        }
    return result;
}
