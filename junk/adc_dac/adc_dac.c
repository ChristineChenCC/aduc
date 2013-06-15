//adc_dac.h

#include "adc_dac.h"
#include <ioaduc7020.h>

// simple delay
void Delay (unsigned long a) { while (--a!=0); }

void ADCpoweron(int time) {
    ADCCON = 0x20;	 // power-on the ADC
    while (time >=0)	 // wait for ADC to be fully powered on
    time--;
}

void InitADC(void) {
    ADCpoweron(20000);	// power on ADC			
    ADCOF     =0x200;	// add 3 LSB for ofset		
    DAC0CON   = 0x13;	// AGND-AVDD range
    DAC1CON   = 0x13;	// AGND-AVDD range
    REFCON    = 0x01;	// internal 2.5V reference
}

// convert ADC chanel
unsigned long ADC_convert(unsigned char chanel) {

  ADCCP = chanel;     // select desired chanel
  ADCCON = 0xA3;      // software conv., single-ended, conv. enabled
  while (!ADCSTA);    // wait for end of conversion
  Delay(1000);
  return ADCDAT;      // return ADC value
}


// set DAC value
void Set_DAC(char chanel, unsigned long value) {
  if(chanel == 0)
    DAC0DAT = value;    // set value to DAC
  if(chanel == 1)
    DAC1DAT = value;    // set value to DAC
}

