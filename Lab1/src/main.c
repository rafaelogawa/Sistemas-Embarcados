#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void main(void){
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilita��o
    
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); // LEDs D4 como sa�da
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); // LEDs D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  bool change = 0;
  uint32_t count = 0;
  while(1){
    
    /*
    *   � afetado ao otimizar o c�digo, quanto maior a otimiza��o, mais r�pido
    *   o led pisca
    */
    //while(count != 2400000){
    //  count++;
    //}
    //count = 0;
    
    /*
    *   Frequ�ncia de 24Mhz:
    *   T = 1/24MHz = 41,67ns
    *   41,67 * 3 instru��es = 125 ns
    *   125 ns * 8*10^6 = 1 s 
    *   N�o � afetado ao otimizar o c�digo
    */
    SysCtlDelay(8000000);
    
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, change);
    change = !change;
    
    
  } // while
} // main