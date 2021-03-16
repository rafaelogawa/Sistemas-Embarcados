#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id;

typedef struct{
  uint8_t led;
  int time;
}structLeds;

void thread1(void *args){
  uint8_t state = 0;
  uint32_t tick;
  
  structLeds *Args = (structLeds*)args;
  uint8_t Led = Args->led;
  int Time = Args->time;
  
  while(1){
    tick = osKernelGetTickCount();
  
    state ^= Led;
    LEDWrite(Led, state);
    
    osDelayUntil(tick + Time);
  } // while
} // thread1

void main(void){
  LEDInit(LED1 | LED2 | LED3 | LED4);

  osKernelInitialize();
  
  structLeds ins1;
  ins1.time=200;
  ins1.led=LED1;
  
  structLeds ins2;
  ins2.time=300;
  ins2.led=LED2;
  
  structLeds ins3;
  ins3.time=500;
  ins3.led=LED3;
  
  structLeds ins4;
  ins4.time=700;
  ins4.led=LED4;
  
  thread1_id = osThreadNew(thread1,&ins1,NULL);
  thread1_id = osThreadNew(thread1,&ins2,NULL);
  thread1_id = osThreadNew(thread1,&ins3,NULL);
  thread1_id = osThreadNew(thread1,&ins4,NULL);
  
  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main