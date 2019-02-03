// DMAtestmain.c
// the software triggerred DMA block transfer.


#include <stdint.h>
#include "PLL.h"
#include "DMASoftware.h"

#include "inc/tm4c123gh6pm.h"

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
#define LEDS      (*((volatile uint32_t *)0x40025038))
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08
const int32_t COLORWHEEL[8] = {RED, RED+GREEN, GREEN, GREEN+BLUE, BLUE, BLUE+RED, RED+GREEN+BLUE, 0};
//const int32_t COLORWHEEL[3] = {RED, RED+GREEN, GREEN};
#define SIZE 1024
uint32_t SrcBuf[SIZE],DestBuf[SIZE];
int main(void){  volatile uint32_t delay; uint32_t i,t;
  PLL_Init();  // now running at 80 MHz
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOF; // enable Port F clock
  delay = SYSCTL_RCGCGPIO_R;              // allow time to finish 
  GPIO_PORTF_DIR_R |= 0x0E;    // make PF3-1 output (PF3-1 built-in LEDs)
  GPIO_PORTF_AFSEL_R &= ~0x0E; // disable alt funct on PF3-1
  GPIO_PORTF_DEN_R |= 0x0E;    // enable digital I/O on PF3-1
                               // configure PF3-1 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFF000F)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;      // disable analog functionality on PF
  LEDS = 0;                    // turn all LEDs off
  DMA_Init();  // initialize DMA channel 30 for software transfer
  t = 0;
  while(1){
    for (int j = 0; j < 9; j++) { //1 sec to execute entire outter for loop 
      for(i=0;i<SIZE;i++){
        SrcBuf[i] = i;
        DestBuf[i] = 0;
      }
      while(DMA_Status()); // wait for idle
      DMA_Transfer(SrcBuf,DestBuf,SIZE);
    
      for(delay = 0; delay < 600000; delay++){}
    }
//    LEDS = COLORWHEEL[t&0x07];
    
    if (t % 3 == 0) {
      LEDS = COLORWHEEL[1];
    } else if (t % 3 == 1) {
      LEDS = COLORWHEEL[2];
    } else {
      LEDS = COLORWHEEL[0];
    }
    
    
    t = t+1;

  }
}
