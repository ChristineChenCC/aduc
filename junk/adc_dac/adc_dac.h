//adc_dac.h

// init ADC and DAC
void InitADC(void);
// convert ADC chanel
unsigned long ADC_convert(unsigned char chanel);
// set DAC value
void Set_DAC(char chanel, unsigned long value);


