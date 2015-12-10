#include "stm8s_conf.h"
#include "config.h"
#include "timers.h"
#include "inputs.h"
#include "outputs.h"

enum {INPUT1=0,INPUT2,INPUT3,INPUT4,INPUT5,INPUT6,INPUT7,INPUT8};
enum {OUTPUT1=0,OUTPUT2,OUTPUT3,OUTPUT4,OUTPUT5};
enum {TIMER1=0,TIMER2,TIMER3,TIMER4,TIMER5,TIMER6,TIMER7,TIMER8};

void doTest();
void doLogic();

void sysInit()
{
    //sysinit
    // cброс настроек
    CLK_DeInit();
    // внутренний источник, 16 Њѓц
    CLK_HSICmd(ENABLE);
    // предделитель может варьироватьсЯ от 1 до 8.
    // 1 = 16 Њѓц
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    __enable_interrupt();
}

int main( void )
{
    sysInit();
    initTimers();
    initInputs();
    initOutputs();
#ifdef TEST_ONLY
    //тесты тут
    //закоментировать чтобы работала логика
    doTest();
#else
    //put your logic here
    doLogic();
#endif
}

void doLogic()
{
while(1)
    {
      if(readInput(INPUT1))//если включен вход1
        {
            //запустить таймер1 на 10сек
            //таймер запускается только если до этого был выключен
            timerSet_1s(TIMER1,10);
        }
        else
        {
            //выключить таймеры
            timerReset(TIMER1);
            timerReset(TIMER2);
        }

      if(timerGet(TIMER1))//если таймер досчитал 10сек
        {
            timerSet_1s(TIMER2,5);//запустить таймер2 на 5 сек
            //включить выходы 1 и 2
            writeOutput(OUTPUT1,SET);
            writeOutput(OUTPUT2,SET);
        }
        else //если таймер выключен или еще не досчитал
        {
          //выключить выходы 1 и 2
            writeOutput(OUTPUT1,RESET);
            writeOutput(OUTPUT2,RESET);
        }
      if(timerGet(TIMER2))//если таймер2 досчитал до 5сек
        {
          //выключить выходы 1 и 2
            writeOutput(OUTPUT1,SET);
            writeOutput(OUTPUT2,SET);
        }
        if(readInput(INPUT3))//если включен вход3
        {
          //включить выходы 3 и 4
            writeOutput(OUTPUT3,SET);
            writeOutput(OUTPUT4,SET);
        }
        else //если выключен вход3
        {
          //выключить выходы 3 и 4
            writeOutput(OUTPUT3,RESET);
            writeOutput(OUTPUT4,RESET);
        }
        if(readInput(INPUT2))//если включен вход2
        {
          //запустить таймер3 на 10*100 мс = 1с
            timerSet_100ms(TIMER3,10);
        }
        else
        {
            //выключить таймер3
            timerReset(TIMER3);
        }
      //если включен вход2 и таймер3 еще не досчитал(или выключен)
        if(readInput(INPUT2) && !timerGet(TIMER3))
        {
            writeOutput(OUTPUT5,SET);
        }
        else//если вход2 включен и таймер3 досчитал до 1сек
        {
            writeOutput(OUTPUT5,RESET);
        }

        //update outputs & inputs!!
        //обновить выходы и входы контроллера
        loopInputs();
        loopOutputs();
    }
}

void doTest()
{
      while(1)
    {
      if(readInput(INPUT1))
        writeOutput(OUTPUT1,SET);
      else
        writeOutput(OUTPUT1,RESET);
      
      if(readInput(INPUT2))
        writeOutput(OUTPUT2,SET);
      else
        writeOutput(OUTPUT2,RESET);
      
      if(readInput(INPUT3))
        writeOutput(OUTPUT3,SET);
      else
        writeOutput(OUTPUT3,RESET);
      
      if(readInput(INPUT4))
        writeOutput(OUTPUT4,SET);
      else
        writeOutput(OUTPUT4,RESET);
      
      if(timerInline_1s(TIMER1,1))
      {
        timerSet_1s(TIMER2,1);
        writeOutput(OUTPUT5,SET);
      }
      if(timerGet(TIMER2))
      {
        timerReset(TIMER1);
        timerReset(TIMER2);
        writeOutput(OUTPUT5,RESET);
      }
      
      loopInputs();
      loopOutputs();
    }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif
