#include "timers.h"

volatile uint32_t sysTime10ms;
volatile uint8_t timersFlags;
volatile uint32_t timersTimes[8];

void initTimers()
{
    ///////////////////////////////////////////////
    //sys timer 10 ms
    TIM2_DeInit();
    //1ñ / (16ÌÃö / 256) * 625 = 0.01c
    TIM2_TimeBaseInit(TIM2_PRESCALER_256, 625);
    //TIM2_PrescalerConfig(TIM2_PRESCALER_256, TIM2_PSCRELOADMODE_UPDATE);
    TIM2_ITConfig(TIM2_IT_UPDATE,ENABLE);
    TIM2_Cmd(ENABLE);
    sysTime10ms=0;
    timersFlags=0;
    uint8_t i;
    for(i=0;i<8;i++)
        timersTimes[i]=0;
}

void timerSet_10ms(uint8_t index, uint32_t value)
{
    if((timersFlags&(1<<index))==0)
    {
        timersTimes[index]=sysTime10ms+value;
        timersFlags=timersFlags|(1<<index);
    }
}


uint8_t timerGet(uint8_t index)
{
    if((timersFlags&(1<<index))==0)
    {
        return 0;
    }
    if(timersTimes[index]<=sysTime10ms)
    {
        return 1;
    }
    return 0;
}


void timerReset(uint8_t index)
{
    timersFlags&=~(1<<index);
}


void timerSet_100ms(uint8_t index, uint32_t value)
{
    timerSet_10ms(index,value*10);
}


void timerSet_1s(uint8_t index, uint32_t value)
{
    timerSet_10ms(index,value*100);
}


uint8_t timerInline_10ms(uint8_t index, uint32_t value)
{
    if((timersFlags&(1<<index))==0)
    {
        timerSet_10ms(index,value);
    }
    return timerGet(index);
}


uint8_t timerInline_100ms(uint8_t index, uint32_t value)
{
    return timerInline_10ms(index,value*10);
}


uint8_t timerInline_1s(uint8_t index, uint32_t value)
{
    return timerInline_10ms(index,value*100);
}
