#ifndef _EE474_
#define _EE474_

#define rcgcgpio (volatile unsigned long *)0x400FE608

#define gpio_den_f (volatile unsigned long *)0x4002551C
#define gpio_data_f (volatile unsigned long *)0x400253FC
#define gpio_dir_f (volatile unsigned long *)0x40025400
#define gpio_lock_f (volatile unsigned long *)0x40025520
#define gpio_cr_f (volatile unsigned long *)0x40025524
#define gpio_pur_f (volatile unsigned long *)0x40025510
#define gpio_im_f (volatile unsigned long *)0x40025410
#define gpio_icr_f (volatile unsigned long *)0x40002541C

#define gpio_den_a (volatile unsigned long *)0x4000451C
#define gpio_data_a (volatile unsigned long *)0x400043FC
#define gpio_dir_a (volatile unsigned long *)0x40004400
#define gpio_amsel_a (volatile unsigned long *)0x40004528
#define gpio_pctl_a (volatile unsigned long *)0x4000452C
#define gpio_afsel_a (volatile unsigned long *)0x40004420
#define gpio_im_a (volatile unsigned long *)0x40004410
#define gpio_icr_a (volatile unsigned long *)0x4000441C
#define gpio_mis_a (volatile unsigned long *)0x40004418
#define gpio_ris_a (volatile unsigned long *)0x40004414

#define gpio_afsel_b (volatile unsigned long *)0x40005420
#define gpio_den_b (volatile unsigned long *)0x4000551C
#define gpio_pctl_b (volatile unsigned long *)0x4000552C


#define rcgctimer (volatile unsigned long *)0x400FE604

#define gptmctl_16b_0 (volatile unsigned long *)0x4003000C
#define gptmcfg_16b_0 (volatile unsigned long *)0x40030000
#define gptmtamr_16b_0 (volatile unsigned long *)0x40030004
#define gptmtailr_16b_0 (volatile unsigned long *)0x40030028
#define gptmris_16b_0 (volatile unsigned long *)0x4003001C
#define gptmicr_16b_0 (volatile unsigned long *)0x40030024
#define gptmimr_16b_0 (volatile unsigned long *)0x40030018

#define gptmctl_16b_1 (volatile unsigned long *)0x4003100C
#define gptmcfg_16b_1 (volatile unsigned long *)0x40031000
#define gptmtamr_16b_1 (volatile unsigned long *)0x40031004
#define gptmtailr_16b_1 (volatile unsigned long *)0x40031028
#define gptmris_16b_1 (volatile unsigned long *)0x4003101C
#define gptmicr_16b_1 (volatile unsigned long *)0x40031024
#define gptmimr_16b_1 (volatile unsigned long *)0x40031018

#define interrupt_en0 (volatile unsigned long *)0xE000E100
#define ris (volatile unsigned long *)0x400FE050
#define misc (volatile unsigned long*)0x400FE058

#define PRI7 (volatile unsigned long *)0xE000E41C

#define rcc (volatile unsigned long *)0x400FE060
#define rcc2 (volatile unsigned long *)0x400FE070

#define rcgcadc (volatile unsigned long *)0x400FE638
#define adcactss0 (volatile unsigned long *)0x40038000
#define adcssctl3 (volatile unsigned long *)0x400380A4
#define adcim (volatile unsigned long *)0x40038008
#define adcpssi0 (volatile unsigned long *)0x40038028
#define adcris0 (volatile unsigned long *)0x40038004
#define adcssfifo3 (volatile unsigned long *)0x400380A8
#define adcisc (volatile unsigned long *)0x4003800C
#define adcris (volatile unsigned long *)0x40038004


#define rcgcuart (volatile unsigned long *)0x400FE618

#define uartctl0 (volatile unsigned long *)0x4000C030
#define uartibrd0 (volatile unsigned long *)0x4000C024
#define uartfbrd0 (volatile unsigned long *)0x4000C028
#define uartlcrh0 (volatile unsigned long *)0x4000C02C
#define uartdr0 (volatile unsigned long *)0x4000C000
#define uartcc0 (volatile unsigned long *)0x4000CFC8
#define uartfr0 (volatile unsigned long *)0x4000C018

#define uartctl1 (volatile unsigned long *)0x4000D030
#define uartibrd1 (volatile unsigned long *)0x4000D024
#define uartfbrd1 (volatile unsigned long *)0x4000D028
#define uartlcrh1 (volatile unsigned long *)0x4000D02C
#define uartdr1 (volatile unsigned long *)0x4000D000
#define uartcc1 (volatile unsigned long *)0x4000DFC8
#define uartfr1 (volatile unsigned long *)0x4000D018

#define PIN0 0x1 //0b00000001
#define PIN1 0x2 //0b00000010
#define PIN2 0x4 //0b00000100
#define PIN3 0x8 //0b00001000
#define PIN4 0x10 //0b00010000
#define PIN5 0x20 //0b00100000
#define PIN6 0x40 //0b01000000
#define PIN7 0x80 //0b10000000


#define SW2 0x1         //0b00001
#define RED 0x02        //0b00010
#define BLUE 0x04       //0b00100
#define GREEN 0x08      //0b01000
#define SW1 0x10        //0b10000


#endif