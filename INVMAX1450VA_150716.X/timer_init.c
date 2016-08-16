#include "timer_init.h"


void Init_timer(void)
{
T1CONbits.TON = 0; // Disable Timer
T1CONbits.TCS = 0; // Select internal instruction cycle clock
T1CONbits.TGATE = 0; // Disable Gated Timer mode
T1CONbits.TCKPS = 0b00; // Select 1:1 Prescaler
TMR1 = 0x00; // Clear timer register
PR1 = TMR_PERIOD; // Load the period value and 2738*6.688963211e-8 = 
IPC0bits.T1IP = 0x01; // Set Timer1 Interrupt Priority Level
IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
IEC0bits.T1IE = 1; // Enable Timer1 interrupt
T1CONbits.TON = 1; // Start Timer
}
