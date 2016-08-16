#include "pwm_init.h"

void Init_PWM(void)
{
   // LATBbits.LATB5=1;
    //PWMACTIVE = 1;
   // LATBbits.LATB6=1; //PWM will be off if RB6 is 0
 
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB6 = 0;
  
  //  LATBbits.LATB5=1;
    LATBbits.LATB6=1;
  
	TRISBbits.TRISB12 = 0;
	TRISBbits.TRISB13 = 0;
	TRISBbits.TRISB14 = 0;
	TRISBbits.TRISB15 = 0;

    // P1TCON=0x8000;
    P1TMR=0x0000;
    P1TPER=PWM_PERIOD;
    P1SECMP=PWM_PERIOD;//0x00C8; //Special event triger = 200 for ADC trigger
    
    PWM1CON2=0x0002;
    P1DTCON1=0x0010;//0x0000;
    P1DTCON2=0x0000;
    P1FLTACON=0x3F80;
    P1FLTBCON=0x3F80;  
    P1OVDCON=0x3F3F;
    P1DC1=30;//PWM_PERIOD;
    P1DC2=30;//PWM_PERIOD;
    //P1DC3=PWM_PERIOD;
    
IFS3bits.PWM1IF = 0;
IEC3bits.PWM1IE = 1;
}

