/* Martin Thomas 1. Dec. 2007:
   
   Attributes should not be used for exception-handlers, they
   cause nothing but trouble. Either use a assembler wrapper
   of "nacked" handler with assembler-macros to store/restore
   registers.
   
   IRQs now handled by assembler wrapper in startup.S. 
   
   FIQ, SWI etc. not modified so far -> TODO */

#define __KEIL__

#include <ADuC7020.h>

void  	(*IRQ)(void);		/* 	Function Pointers for Interupts 	*/
void 	(*SWI)(void);
void 	(*FIQ)(void);
void  	(*UNDEF)(void);
void 	(*PABORT)(void);
void 	(*DABORT)(void);

void	ADI_SWI_Interrupt_Setup(void) __attribute__ ((interrupt ("SWI")));
void	ADI_FIQ_Interrupt_Setup(void) __attribute__ ((interrupt ("FIQ")));
void	ADI_UNDEF_Interrupt_Setup(void) __attribute__ ((interrupt ("UNDEF")));
void	ADI_PABORT_Interrupt_Setup(void) __attribute__ ((interrupt ("PABORT")));
void	ADI_DABORT_Interrupt_Setup(void)  __attribute__ ((interrupt ("DABORT")));


void	ADI_FIQ_Interrupt_Setup(void) 
{
	if ( *FIQ !=0x00)
	{
		FIQ();
	}
}

void	ADI_SWI_Interrupt_Setup(void) 
{
	if ( *SWI !=0x00)
	{
		SWI();
	}
}

void	ADI_UNDEF_Interrupt_Setup(void) 
{
	if ( *UNDEF !=0x00)
	{
		UNDEF();
	}
}

void	ADI_PABORT_Interrupt_Setup(void) 
{
	if ( *PABORT !=0x00)
	{
		PABORT();
	}
}

void	ADI_DABORT_Interrupt_Setup(void) 
{
	if ( *DABORT !=0x00)
	{
		DABORT();
	}
}
