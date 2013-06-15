/********************************************************************

 Author        : ADI - Apps            www.analog.com/MicroConverter

 Date          : Sept. 2005

 File          : GPIO.c

 Hardware      : Applicable to ADuC702x rev H or I silicon
                 Currently targetting ADuC7026.

 Description   : This code produces a pulse of 12.30us every 67.4us
 				 on P4.2 using Timer1.

********************************************************************/
#include <ADuC7020.h>
											
void My_IRQ_Function(void);					//	IRQ Funtion Prototype 
								
int main (void)  {

	IRQ = My_IRQ_Function;	// 	Specify Interrupt Service Rountine 
	IRQEN = 0x8;		//	Enable Timer1 IRQ

	T1LD = 0x80;		// timer 1 configuration 
	T1CON = 0xC4;		// 
			
	GP4DAT = 0x04000000;	//	Configure P4.2 as output

	while(1) {}
                   
	return 0 ;
}

/********************************************************************/
/*                                                                  */
/*		Interrupt Service Rountine									*/
/*                                                                  */
/********************************************************************/

void My_IRQ_Function()				
{				
	if ((IRQSTA & GP_TIMER_BIT) == 0x8) 			// Timer1 IRQ?
	{
		T1CLRI = 0;
		GP4DAT ^= 0x00040000;				// Complement P4.2
		if ((GP4DAT & 0x04) == 0x04) T1LD = 0x10;	// timer 1 reload ()
		else T1LD = 0x80;				// timer 1 reload ()
	} 				
	return ;
}



