
// customized header file

// lab-1 config
#define RCGCGPIO_PORTF      *((volatile unsigned long *)0x400FE108)
#define GPIODEN_PORTF       *((volatile unsigned long *)0x4002551C)
#define GPIODIR_PORTF	      *((volatile unsigned long *)0x40025400)
#define GPIODATA_PORTF      *((volatile unsigned long *)0x400253FC)
#define GPIODATA_PORTA      *((volatile unsigned long *)0x400043FC)
#define GPIOLOCK_PORTF      *((volatile unsigned long *)0x40025520)
#define GPIO_PORTF_PUR      *((volatile unsigned long *)0x40025510)
#define GPIO_PORTF_PDR      *((volatile unsigned long *)0x40025514)
#define GPIOCR 				      *((volatile unsigned long *)0x40025524)

// Lab - 2 Config

// Section A
#define RCGCTIMER 	 	      *((volatile unsigned long *)0x400FE604)
#define GPTMCTL_0A          *((volatile unsigned long *)0x4003000C)
#define GPTMCTL_1A          *((volatile unsigned long *)0x4003100C)
#define GPTMCTL_2A          *((volatile unsigned long *)0x4003200C)
#define GPTMCFG_0A          *((volatile unsigned long *)0x40030000)
#define GPTMCFG_1A          *((volatile unsigned long *)0x40031000)
#define GPTMCFG_2A          *((volatile unsigned long *)0x40032000)
#define GPTMTAMR_0A         *((volatile unsigned long *)0x40030004)
#define GPTMTAMR_1A         *((volatile unsigned long *)0x40031004)
#define GPTMTAMR_2A         *((volatile unsigned long *)0x40032004)
#define GPTMTAILR_0A        *((volatile unsigned long *)0x40030028)
#define GPTMTAILR_1A        *((volatile unsigned long *)0x40031028)
#define GPTMTAILR_2A        *((volatile unsigned long *)0x40032028)
#define GPTMRIS_0A 	        *((volatile unsigned long *)0x4003001C)
#define GPTMRIS_1A          *((volatile unsigned long *)0x4003101C)
#define GPTMRIS_2A          *((volatile unsigned long *)0x4003201C)
#define GPTMICR_0A          *((volatile unsigned long *)0x40030024)
#define GPTMICR_1A   	      *((volatile unsigned long *)0x40031024)
#define GPTMICR_2A	 	      *((volatile unsigned long *)0x40032024)

// Section B
#define EN0 					      *((volatile unsigned long *)0xE000E100)
#define EN1                 *((volatile unsigned long *)0xE000E104)
#define DIS0 					      *((volatile unsigned long *)0xE000E180)
#define PRI7 					      *((volatile unsigned long *)0xE000E41C)

#define GPTMIMR_0A 		      *((volatile unsigned long *)0x40030018)
#define GPTMIMR_1A 		      *((volatile unsigned long *)0x40031018)
#define GPTMIMR_2A 		      *((volatile unsigned long *)0x40032018)
#define GPIOICR_PORTF       *((volatile unsigned long *)0x4002541C)
#define GPIOMIS_PORTF       *((volatile unsigned long *)0x40025418)
#define GPIORIS_PORTF       *((volatile unsigned long *)0x40025414)

// Lab - 3 Config

// Section A
#define SYSCTL_RCC 	 	      *((volatile unsigned long *)0x400FE060)
#define SYSCTL_RCC2 	      *((volatile unsigned long *)0x400FE070)
#define SYSCTL_RIS 	 	      *((volatile unsigned long *)0x400FE050)
#define RCGCADC 	 	 	      *((volatile unsigned long *)0x400FE638)
#define PRI4                *((volatile unsigned long *)0xE000E410)
// ADC Module 0
#define ADCACTSS_0 	 	      *((volatile unsigned long *)0x40038000)
#define ADCISC_0 	 	 	      *((volatile unsigned long *)0x4003800C)
#define ADCEMUX_0 	 	      *((volatile unsigned long *)0x40038014)
#define ADCSSCTL3_0 	      *((volatile unsigned long *)0x400380A4)
#define ADCIM_0 	 		      *((volatile unsigned long *)0x40038008)
#define ADCSSFIFO3_0        *((volatile unsigned long *)0x400380A8)
#define ADCPSSI_0 	 	      *((volatile unsigned long *)0x40038028)
#define ADCRIS_0 	 	 	      *((volatile unsigned long *)0x40038004)
// ADC Module 1
#define ADCACTSS_1          *((volatile unsigned long *)0x40039000)
#define ADCISC_1            *((volatile unsigned long *)0x4003900C)
#define ADCEMUX_1           *((volatile unsigned long *)0x40039014)
#define ADCSSCTL3_1         *((volatile unsigned long *)0x400390A4)
#define ADCIM_1             *((volatile unsigned long *)0x40039008)
#define ADCSSFIFO3_1        *((volatile unsigned long *)0x400390A8)
#define ADCPSSI_1           *((volatile unsigned long *)0x40039028)
#define ADCRIS_1            *((volatile unsigned long *)0x40039004)

// Section B
#define GPIOPCTL_PORTA      *((volatile unsigned long *)0x4000452C)
#define GPIOAFSEL_PORTA     *((volatile unsigned long *)0x40004420)
#define GPIOPCTL_PORTB      *((volatile unsigned long *)0x4000552C)
#define GPIOAFSEL_PORTB     *((volatile unsigned long *)0x40005420)
#define RCGCUART 			      *((volatile unsigned long *)0x400FE618)
#define UARTCTL_0 		      *((volatile unsigned long *)0x4000C030)
#define UARTLCRH_0 		      *((volatile unsigned long *)0x4000C02C)
#define UARTIBRD_0 		      *((volatile unsigned long *)0x4000C024)
#define UARTFBRD_0 		      *((volatile unsigned long *)0x4000C028)
#define UARTCTL_1 		      *((volatile unsigned long *)0x4000D030)
#define UARTLCRH_1 		      *((volatile unsigned long *)0x4000D02C)
#define UARTIBRD_1 		      *((volatile unsigned long *)0x4000D024)
#define UARTFBRD_1 		      *((volatile unsigned long *)0x4000D028)
#define GPIODEN_PORTA       *((volatile unsigned long *)0x4000451C)
#define GPIOAMSEL_PORTA     *((volatile unsigned long *)0x40004528)
#define GPIODEN_PORTB       *((volatile unsigned long *)0x4000551C)
#define GPIOAMSEL_PORTB     *((volatile unsigned long *)0x40005528)
#define UARTFR_0 		 	      *((volatile unsigned long *)0x4000C018)
#define UARTDR_0 		 	      *((volatile unsigned long *)0x4000C000)
#define UARTCC_0 		 	      *((volatile unsigned long *)0x4000CFC8)
#define UARTFR_1 		 	      *((volatile unsigned long *)0x4000D018)
#define UARTDR_1 		 	      *((volatile unsigned long *)0x4000D000)
#define UARTCC_1 		 	      *((volatile unsigned long *)0x4000DFC8)

// Lab - 4 Config
#define RCGCGPIO_PORTS      *((volatile unsigned long *)0x400FE108)
#define RCGCGPIO            *((volatile unsigned long *)0x400FE608)
#define GPIODIR_PORTA       *((volatile unsigned long *)0x40004400)
#define GPIODIR_PORTB       *((volatile unsigned long *)0x40005400)
#define PRI12               *((volatile unsigned long *)0xE000E430)

#define GPIOCR_UNLOCK       0x4C4F434B
#define RED 						    0x02
#define BLUE 						    0x04
#define VIOLET 					    0x06
#define GREEN 					    0x08
#define YELLOW 					    0x0A
#define LIGHT_BLUE          0x0C
#define WHITE 					    0x0E

// USB Serial Baud Rate
#define USBI80					    int 520
#define USBF80					    int 54
#define USBI4						    int 26
#define USBF4						    int 3
#define USBI16					    int 104
#define USBF16				    	int 11

// Bluetooth Serial Baud Rate
#define BTI80			    			int 43
#define BTF80					    	int 26
#define BTI4			    			int 2
#define BTF4				    		int 11
#define BTI16				    		int 8
#define BTF16				    		int 44