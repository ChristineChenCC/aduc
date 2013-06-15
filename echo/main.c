// This program is designed for ADUC_P7020 board
// It shows how to work with uart interface

#include "system.h"
#include "ADuC7020.h"
#include "uart.h"

void Delay(int);
void InitADC(void);
unsigned long ADC_convert(int);

void hex(int);

void Delay(int time) { while(time--); }

void InitADC() {
    ADCCON = 0x20;	 // power-on the ADC
    Delay(40000);

    ADCOF     =0x200;	// add 3 LSB for offset		
    REFCON    = 0x01;	// internal 2.5V reference
}

// convert ADC chanel
unsigned long ADC_convert(int channel) {

  ADCCP  = channel;     // select desired channel
  ADCCON = 0xA3;        // software conv., single-ended, conv. enabled
  while (!ADCSTA);      // wait for end of conversion
  Delay(2000);
  return ADCDAT;        // return ADC value
}


void hex(int value) {
    int i = 8;

    while ( i-- ) {
	putc("0123456789ABCDEF"[(value >> i*4) & 0x0F]);
    }
}

// (((ADC>>16)/0x0FFF)*2.5-.5)*100

#define FIXED 8

#define FMUL(a,b) (((a)*(b))>>(FIXED))
#define FDIV(a,b) (((a)<<(FIXED))/(b))

#define ITOFIX(a) ((a)<<FIXED)
#define FIXTOI(a) ((a)>>FIXED)

void nl(void);
void nl(void) { putc('\r'); putc('\n'); }

int Tmp(int T);
int Tmp(int T) {
      return FMUL(FDIV(T >> 8, ITOFIX(0x0FFF)), ITOFIX(2500)) - ITOFIX(50);
}

typedef struct Zone {
    int	setp;
    int	setp_nominal;
    int outdoor;
    int  indoor;

    int min_target;
    int max_target;

    int min_outdoor;
    int max_outdoor;
} Zone;

int c2f(T) { return FMUL(FDIV(ITOFIX(9),ITOFIX(5)),ITOFIX(T)) + 32; }

#if 0

  setp_nominal = 70;
  setp         = 65;

  min_outdoor  = 20;
  max_outdoor  = 60;
  min_target   = 65;
  max_target   = 104;

  degperdeg = FDIV(ITOFIX(min_outdoor - max_outdoor) / ITOFIX(min_outdoor - setp_nominal));

  target    = FMUL(degperdeg, ITOFIX(max_outdoor - min(max_outdoor, max(min_outdoor, outdoor))));

  

    if ( setp > min ) {
	target = 
    } else {
	call = 0
    }

#endif


int main(void)
{
    unsigned char ch;
    int T;

  InitFreq();
  InitUart();
  InitADC();

  GP1DAT = 0xF0000000;		// Four outputs

  while( 1 ) {
    ch = getc();

    switch ( ch ) {
     case '0' : putc('@'); hex(T = ADC_convert(0));	nl();
		putc(':'); hex(Tmp(T));			nl();
		putc(':'); puti(T);			nl();
		putc(':'); puti(Tmp(T));
		break;
     case '1' : putc('@'); hex(ADC_convert(1)); break;
     case '2' : putc('@'); hex(ADC_convert(2)); break;
     case '3' : putc('@'); hex(ADC_convert(3)); break;
     case '4' : putc('@'); hex(ADC_convert(4)); break;

     case 'A' : putc('+'); putc('A'); GP1DAT |=  0x00100000;	break;  // pin 1.4
     case 'B' : putc('+'); putc('B'); GP1DAT |=  0x00200000;	break;  // pin 1.5
     case 'C' : putc('+'); putc('C'); GP1DAT |=  0x00400000;	break;  // pin 1.6
     case 'D' : putc('+'); putc('D'); GP1DAT |=  0x00800000;	break;  // pin 1.7

     case 'a' : putc('-'); putc('a'); GP1DAT &= ~0x00100000;	break;  // pin 1.4
     case 'b' : putc('-'); putc('b'); GP1DAT &= ~0x00200000;	break;  // pin 1.5
     case 'c' : putc('-'); putc('c'); GP1DAT &= ~0x00400000;	break;  // pin 1.6
     case 'd' : putc('-'); putc('d'); GP1DAT &= ~0x00800000;	break;  // pin 1.7

     case 'T' : 
	putc('@'); hex(0x12345678);
	break;
     default:
	putc(':'); putc(ch);
	break;
    }

    nl();
  }
}
