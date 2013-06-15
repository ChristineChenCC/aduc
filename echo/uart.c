// uart.c

#include "uart.h"
#include <ADuC7020.h>

#define TEMT  0x40
#define THRE  0x20
#define	DR    0x01

// init uart interface
void InitUart(void) {

  // Setup tx & rx pins on P1.0 and P1.1
  GP1CON = 0x011;

  // Start setting up UART at 9600bps
  COMCON0 = 0x080;				// Setting DLAB
  COMDIV0 = 0x023;				// Setting DIV0 and DIV1 to DL calculated (9600/11.2MHz)
  COMDIV1 = 0x000;
  COMCON0 = 0x003;				// Clearing DLAB
}

// Receive char from uart
//
unsigned char getc(void) {
  while ((COMSTA0 & DR) == 0);
  return COMRX;
}


// Send char via uart
//
void putc(unsigned char ch) {
  while ((COMSTA0 & TEMT) == 0);
  COMTX=ch;	
}

void puts(char *str) {
    while ( *str ) {
	putc(*str);
    }
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
	tmp_value = value;
	value /= base;
	*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
	tmp_char = *ptr;
	*ptr--= *ptr1;
	*ptr1++ = tmp_char;
    }
    return result;
}

void puti(int i) {
    char buffer[32];

    puts(itoa(i, buffer, 32));
}
