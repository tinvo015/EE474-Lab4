
// EE 474, Lab - 4, Section B

// Section B

#include <tm4c123gh6pm.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "C:\Users\taojin\Desktop\EE 474\Lab\EE474-Lab4\TaskB\lab4_starter\LCD\myHeader.h"
#include "C:\Users\taojin\Desktop\EE 474\Lab\EE474-Lab4\TaskB\lab4_starter\LCD\SSD2119.h"

void Timer_Init_0A(void);
void Timer_Init_1A(void);
void PortF_Init(void);
void ADC1_Init(void);
void ADC1_Handler(void);
void SYS_Init(void);
void timer(void);
unsigned int tempTable(double temperature);
void Timer_Handler_1A(void);
void LCD_DrawCube(unsigned short startX, unsigned short startY, unsigned short sildeLen, unsigned short Color);

volatile bool blink = 0;

void main(void)
{
	SYS_Init();
	
	while (1)
	{
		
	}
}

void SYS_Init(void)
{
	PortF_Init();
	Timer_Init_0A();
	Timer_Init_1A();
	ADC1_Init();
	LCD_Init();
	Touch_Init();
}

/** Max countdown value can be adjusted
 *	based on the current clock frequency
 */
void Timer_Init_0A(void)
{
  RCGCTIMER |= 0x01;               // enable clock for Timer 0
  GPTMCFG_0A = 0x00000000;         // select 32-bit timer config
  GPTMCTL_0A = 0x00;               // disable Timer 0
  GPTMCTL_0A |= 0x00000020;				 // enable ADC trigger
  GPTMTAMR_0A |= 0x00000002;       // enable periodic timer mode
  GPTMTAMR_0A &= ~0x000000010000;  // enable countdown mode
  
  // set appropriate second based on clock frequency
  GPTMTAILR_0A = 0xF42400;

  GPTMICR_0A = 0x01;               // clear flag
  GPTMCTL_0A |= 0x01;							 // enable the Timer_0A
}

void Timer_Init_1A(void)
{
	RCGCTIMER |= 0x02;							// enable clock for Timer 1
	GPTMCFG_1A = 0x00000000;				// select 32-bit timer config
	GPTMCTL_1A = 0x00;							// disable Timer 1
	GPTMTAMR_1A |= 0x00000002;			// enable periodic timer mode
	GPTMTAMR_1A &= ~0x000000010000; // enable countdown mode

	GPTMTAILR_1A = 0x4C4B40; 				// load the start value (0.5 sec)

	// interrupt service config
	GPTMIMR_1A |= 0x01; 						// enable GPTM interrupt
	EN0 |= (1 << 21);								// enable Timer 1A intrrupt (interrupt #21)
	GPTMICR_1A = 0x01;							// clear flag
	GPTMCTL_1A |= 0x01;							// enable the Timer_1A
}

/** Initialize GPIO Port F Pins to
 *	enable onboard switches and LEDs
 */
void PortF_Init(void)
{
  volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x20;         		// activate clock for Port F
  delay = SYSCTL_RCGC2_R;             // allow time for clock to start
  GPIODIR_PORTF |= 0x0E;          		// direction PF [1:3] to input
  GPIODEN_PORTF |= 0x1F;           		// enable PF [0:4] digital port
}

/** Configures the ADC module, triggered by
 *  timer and interrupts
 */
void ADC1_Init(void)
{
	RCGCADC |= 0x2;							// enable ADC Module 0
	timer();										// add delay for allowing time to configure RCGCADC
	ADCACTSS_1 &= ~0xF;					// disable the sample sequencer
	ADCISC_1 |= 0xF;						// clear the trigger event
	ADCEMUX_1 |= 0x5000;				// select software trigger for SS3- Timer
	ADCSSCTL3_1 |= 0xE;					// sample the temperature sensor

	// interrupt service config
	ADCIM_1 |= 0x8;							// mask interrupt for SS3
	EN1 |= (1 << 19);						// enable ADC1 SS3 interrupt (interrupt # 51)
	PRI12 |= (3 << 29);         // set interrupt priority to 3

	ADCISC_1 |= 0x8;						// clear trigger status
	ADCACTSS_1 |= 0x8;					// enable SS3
}

/**	ISR for the ADC0 module
 *
 *	Calculate the temperature
 *	Display the color code with LEDs
 */
void ADC1_Handler(void)
{
	ADCPSSI_1 |= 0x3;						// start a conversion sequence 3
	
	while (!(ADCRIS_1 & 0x8))
	{
		// wait for conversion to complete
	}
	float result = (float) ADCSSFIFO3_1;
	int temperature = (int) (147.5 - ((247.5 * result) / 4096));	// temp conversion
	int color = tempTable(temperature);

	LCD_SetCursor(160, 120);
	LCD_PrintInteger(temperature);
	LCD_SetCursor(160, 150);
	
	if ((GPIODATA_PORTF & 0x0E))
		GPIODATA_PORTF = 0;
	else
		GPIODATA_PORTF = color;

	LCD_DrawCube(200, 150, 60, 0x1234);

	GPTMCTL_0A &= ~0x01;						// disable the Timer_0A
	ADCISC_1 |= 0x8;								// clear the ADC flag
	GPTMICR_0A = 0x01;  						// clear timer flag
	GPTMCTL_0A |= 0x01;							// enable the Timer_0A
}

void timer(void)
{
	int count = 0;
	for (int i = 0; i < 500000; i++)
		count++;
}

unsigned int tempTable(double temp)
{
	unsigned int LED = 0;
	if (temp > 0 && temp <= 17)
		LED = RED;
	else if (temp > 17 && temp <= 19)
		LED = BLUE;
	else if (temp > 19 && temp <= 21)
		LED = VIOLET;
	else if (temp > 21 && temp <= 23)
		LED = GREEN;
	else if (temp > 23 && temp <= 25)
		LED = YELLOW;
	else if (temp > 25 && temp <= 27)
		LED = LIGHT_BLUE;
	else if (temp > 27 && temp <= 40)
		LED = WHITE;
	
	return LED;
}

void Timer_Handler_1A(void)
{
	// // Clear the contents of the display buffer.
	// int count;
	// LCD_WriteCommand(0x22);
	// for (count = 0; count < (320 * 240); count++)
	// {
	// 	LCD_WriteData(0x0000);
	// }

	int x = (int)Touch_ReadX();
	int y = (int)Touch_ReadY();

	LCD_SetCursor(60, 230);
	printf("X Coor is: %d and Y Coor is: %d", x, y);

	GPTMCTL_1A &= ~(0x01);			// disable the Timer_1A
	GPTMICR_1A = 0x01; 					// clear flag
	GPTMCTL_1A |= 0x01;					// enable the Timer_1A
}

void LCD_DrawCube(unsigned short startX, unsigned short startY, unsigned short sideLen, unsigned short Color)
{
	LCD_DrawRect(startX, startY, sideLen, sideLen, Color);

	LCD_DrawLine(startX, startY, (unsigned short)(startX + (sideLen / sqrt(2))), (unsigned short)(startY - (sideLen / sqrt(2))), Color);

	LCD_DrawLine((unsigned short)(startX + (sideLen / sqrt(2))), (unsigned short)(startY - (sideLen / sqrt(2))),
							 (unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2))), Color);

	LCD_DrawLine((unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2))),
							 (unsigned short)(startX + sideLen), startY, Color);

	LCD_DrawLine((unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2))),
							 (unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2)) + sideLen), Color);

	LCD_DrawLine((unsigned short)((startX + (sideLen / sqrt(2))) + sideLen), (unsigned short)(startY - (sideLen / sqrt(2)) + sideLen),
							 (unsigned short)(startX + sideLen), (unsigned short)(startY + sideLen), Color);

	// int i;
	// for (i = y0 - x; i < y0 + x; i++)
	// {
	// 	LCD_DrawPixel(x0 - y, i, color);
	// }

	// LCD_DrawFilledRect(startX, startY, sideLen, sideLen, Color);
}