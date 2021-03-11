#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "driverlib/systick.h"
#include "driverleds.h" // Projects/drivers

// MEF com apenas 2 estados e 1 evento temporal que alterna entre eles
// Seleção por evento

typedef enum {G000, G001, G011, G010, G110, G111, G101, G100} state_t;

volatile uint8_t Evento = 0;

void SysTick_Handler(void){
  Evento = 1;
} // SysTick_Handler

void main(void){
  static state_t Estado = G000; // estado inicial da MEF
  
  LEDInit(LED1);
  LEDInit(LED2);
  LEDInit(LED3);
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  while(1){
    if(Evento){
      Evento = 0;
      switch(Estado){
        case G000:
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          Estado = G001;
          break;
          
        case G001:
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOn(LED3);
          Estado = G011;
          break;
          
        case G011:
          LEDOff(LED1);
          LEDOn(LED2);
          LEDOn(LED3);
          Estado = G010;
          break;
          
        case G010:
          LEDOff(LED1);
          LEDOn(LED2);
          LEDOff(LED3);
          Estado = G110;
          break;
          
        case G110:
          LEDOn(LED1);
          LEDOn(LED2);
          LEDOff(LED3);
          Estado = G111;
          break;
          
        case G111:
          LEDOn(LED1);
          LEDOn(LED2);
          LEDOn(LED3);
          Estado = G101;
          break;
          
        case G101:
          LEDOn(LED1);
          LEDOff(LED2);
          LEDOn(LED3);
          Estado = G100;
          break;
          
        case G100:
          LEDOn(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          Estado = G000;
          break;          
      } // switch
    } // if
  } // while
} // main
