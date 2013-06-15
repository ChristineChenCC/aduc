//system.c
#include "system.h"
#include <ioaduc7020.h>

// Init Frequency
void InitFreq(void) {
  POWKEY1 = 0x01;
  POWCON = 0x02;         //11.272MHz
  POWKEY2 = 0xF4;
}

