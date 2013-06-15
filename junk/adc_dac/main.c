// This program is designed for ADUC_P7020 board
// It shows how to work with ADC and DAC

#include <ioaduc7020.h>
#include "system.h"
#include "adc_dac.h"


//variable
unsigned char ch = 0x0;

int main()
{
  // Init frequency
  InitFreq();
  // Init UART
  InitADC();

  // loop forever
  while(1) {

    // read value from tripot and set to duoled via ADC/DAC
    Set_DAC(0,ADC_convert(0));
    Set_DAC(1,ADC_convert(1));
  }

}
