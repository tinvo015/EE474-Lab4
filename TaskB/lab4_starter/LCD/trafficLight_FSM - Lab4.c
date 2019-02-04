

#include <tm4c123gh6pm.h>
#include <stdint.h>
#include <stdbool.h>
#include "C:\Users\taojin\Desktop\EE 474\Lab\EE474-Lab4\TaskB\lab4_starter\LCD\myHeader.h"

// FSM state definition
const int OFF = 0;
const int GO = 1;
const int STOP = 2;
const int WARN = 3;

volatile int state = 0;
volatile int next_state = 0;
volatile bool on_Off = 0;
volatile bool pedestrian = 0;
volatile bool LED_Timeout = 0;

void sys_Init(void);
void LED_Init(void);
void Switch_Init(void);
void timer_Init_0A(void);
void timer_Init_1A(void);
void timer_Init_2A(void);
bool Switch_On_Off(void);
bool Switch_Pedestrian(void);
void readEvent(int state);
void FSM(void);
void read_On_Off(void);
void read_Pedestrian(void);
void read_LED_Timer(void);
void read_Input(void);
void Timer_Handler_0A(void);
void Timer_Handler_1A(void);
void Timer_Handler_2A(void);

int main(void)
{
  sys_Init();           // initialize LED and Switches
  
  while (1) 
  {
    read_Input();
    readEvent(state);   // FSM output is assigned here
  }
  
  return 0;
}

void sys_Init(void)
{
  LED_Init();
  Switch_Init();
  timer_Init_0A();
  timer_Init_1A();
  timer_Init_2A();
}

// initialize the configuration for LED
void LED_Init(void)
{
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x01;               // activate clock for Port A
  delay = SYSCTL_RCGC2_R;               // allow time for clock to start
  GPIO_PORTA_PCTL_R &= ~0x00000F00;
  GPIO_PORTA_AMSEL_R &= ~0xFF;          // disable analog function for Port A
  GPIO_PORTA_DIR_R |= 0xE0;             // set LED Pin direction to output
  GPIO_PORTA_AFSEL_R &= ~0xFF;          // regular port function
  GPIO_PORTA_DEN_R |= 0xFF;             // enable digital Port A
}

// initialize the configuration for switch
void Switch_Init(void)
{
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000001;         // activate clock for Port A
  delay = SYSCTL_RCGC2_R;               // allow time for clock to start
  GPIO_PORTA_AMSEL_R &= ~0x0C;          // disable analog on PA 2&3 
  GPIO_PORTA_PCTL_R &= ~0x0000FF00;     // PCTL GPIO on PA 2&3
  GPIO_PORTA_DIR_R &= ~0x0C;            // direction PA 2&3 to input
  GPIO_PORTA_AFSEL_R &= ~0x0C;          // PA 2&3 regular function
  GPIO_PORTA_DEN_R |= 0x0C;             // enable PA 2&3 digital port
}

void timer_Init_0A(void)
{
  RCGCTIMER |= 0x01;               // enable clock for Timer 0
  GPTMCFG_0A = 0x00000000;         // select 32-bit timer config
  GPTMCTL_0A = 0x00;               // disable Timer 0
  GPTMTAMR_0A |= 0x00000002;       // enable periodic timer mode
  GPTMTAMR_0A &= ~0x000000010000;  // enable countdown mode
  
  GPTMTAILR_0A = 0x4C4B400;        // load the start value to 5 sec
  
  // interrupt service config
  GPTMIMR_0A |= 0x01;              // enable GPTM interrupt
  EN0 |= 0x00080000;               // enable Timer 0A intrrupt (interrupt #19)
  GPTMICR_0A = 0x01;               // clear flag
}

void timer_Init_1A(void)
{
  RCGCTIMER |= 0x02;               // enable clock for Timer 1
  GPTMCFG_1A = 0x00000000;         // select 32-bit timer config
  GPTMCTL_1A = 0x00;               // disable Timer 1
  GPTMTAMR_1A |= 0x00000002;       // enable periodic timer mode
  GPTMTAMR_1A &= ~0x000000010000;  // enable countdown mode

  GPTMTAILR_1A = 0x1E84800;        // load the start value (2 sec)

  // interrupt service config
  GPTMIMR_1A |= 0x01;              // enable GPTM interrupt
  EN0 |= 0x00200000;               // enable Timer 1A intrrupt (interrupt #19)
  GPTMICR_1A = 0x01;               // clear flag
}

void timer_Init_2A(void)
{
  RCGCTIMER |= 0x04;               // enable clock for Timer 2
  GPTMCFG_2A = 0x00000000;         // select 32-bit timer config
  GPTMCTL_2A = 0x00;               // disable Timer 2
  GPTMTAMR_2A |= 0x00000002;       // enable periodic timer mode
  GPTMTAMR_2A &= ~0x000000010000;  // enable countdown mode

  GPTMTAILR_2A = 0x1E84800;        // load the start value (2 sec)

  // interrupt service config
  GPTMIMR_2A |= 0x01;              // enable GPTM interrupt
  EN0 |= 0x00800000;               // enable Timer 2A intrrupt (interrupt #19)
  GPTMICR_2A = 0x01;               // clear flag
}

// returns true if switch is pressed, false otherwise
bool Switch_On_Off(void)
{
  return (GPIO_PORTA_DATA_R & (1 << 2)) != 0;
}

// returns true if switch is pressed, false otherwise
bool Switch_Pedestrian(void)
{
  return (GPIO_PORTA_DATA_R & (1 << 3)) != 0;
}

// executes the output of the parameter state
void readEvent(int state)
{
  GPIO_PORTA_DATA_R &= ~0xFF;
  if (state == OFF)
    GPIO_PORTA_DATA_R &= ~0xFF;
  else if (state == GO)
  {
    GPIO_PORTA_DATA_R |= 0x20;
  }
  else if (state == STOP)
  {
    GPIO_PORTA_DATA_R |= 0x80;
  }
  else if (state == WARN)
  {
    GPIO_PORTA_DATA_R |= 0x40;
  }
}

void FSM(void)
{
  if (state == GO)
  {
    if (on_Off)
      next_state = OFF;
    else if (pedestrian)
      next_state = WARN;
    else
      next_state = STOP;
  }
  else if (state == STOP)
  {
    if (on_Off)
      next_state = OFF;
    else
      next_state = GO;
  }
  else if (state == WARN)
  {
    if (on_Off)
      next_state = OFF;
    else
      next_state = STOP;
  }
  else
  {
    if (on_Off)
      next_state = STOP;
  }
  
  state = next_state;         // assign the current state to the next state
}

void read_On_Off(void)
{
  on_Off = 0;
  if (!(GPTMCTL_1A & (1 << 0)) && Switch_On_Off())
    GPTMCTL_1A |= 0x01;
  else if ((GPTMCTL_1A & (1 << 0)) && !Switch_On_Off())
  {
    GPTMCTL_1A = 0x00;
    GPTMICR_1A = 0x01;
  }
}

void Timer_Handler_1A(void)
{
    on_Off = 1;
    GPTMICR_1A = 0x01;   // clear flag
    GPTMCTL_1A = 0x00;
    timer_Init_0A();
    FSM();
}

void read_Pedestrian(void)
{
  pedestrian = 0;
  if (state == GO)
  {
    if (!(GPTMCTL_2A & (1 << 0)) && Switch_Pedestrian())
      GPTMCTL_2A |= 0x01;
    else if ((GPTMCTL_2A & (1 << 0)) && !Switch_Pedestrian())
    {
      GPTMCTL_2A = 0x00;
      GPTMICR_2A = 0x01;
    }
  }
}

void Timer_Handler_2A(void)
{
  pedestrian = 1;
  GPTMICR_2A = 0x01;    // clear flag
  GPTMCTL_2A = 0x00;    // disable the timer
  if (state == GO)
    timer_Init_0A();
  FSM();
}

void read_LED_Timer(void)
{
  LED_Timeout = 0;

  if (!(GPTMCTL_0A & (1 << 0)) && state != OFF)
    GPTMCTL_0A |= 0x01;
  else if ((GPTMCTL_0A & (1 << 0)) && state == OFF)
    GPTMCTL_0A = 0x00;
}

void Timer_Handler_0A(void)
{
  LED_Timeout = 1;
  FSM();
  GPTMICR_0A = 0x01;
}

void read_Input(void)
{
  read_On_Off();
  read_Pedestrian();
  read_LED_Timer();
}
