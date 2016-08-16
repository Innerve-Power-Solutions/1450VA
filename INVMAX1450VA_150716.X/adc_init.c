
#include "adc_init.h"

void Init_ADC(void)
{
//AD1CHS0bits.CH0SA = 3; // Select AN3 for CH0 +ve input
//AD1CHS0bits.CH0NA = 0; // Select VREF- for CH0 -ve input
//AD1CHS123bits.CH123SA=0; // Select AN0 for CH1 +ve input
//// Select AN1 for CH2+ve input
//// Select AN2 for CH3 +ve input
//AD1CHS123bits.CH123NA=0; // Select VREF- for CH1/CH2/CH3 -ve inputs
//
AD1CON1bits.FORM = 0;//integer
AD1CON1bits.SSRC = 0b011;//Internal Counter (SAMC) ends sampling and starts conversion
AD1CON1bits.ASAM = 1; // ADC Sample Control: Sampling begins immediately after conversion
//AD1CON2bits.CHPS = 3;//// Converts channels CH0/CH1/CH2/CH3
AD1CON3bits.ADRC = 0; // ADC Clock is derived from Systems Clock
AD1CON3bits.SAMC = 0; // Auto Sample Time = 0 * TAD
AD1CON3bits.ADCS = 0; // ADC Conversion Clock TAD = TCY * (ADCS + 1) = (1/15M) * 1 =
//                                // 66 ns (15 MHz)
//                      // ADC Conversion Time for 10-bit Tconv = 12 * TAD = 800 ns (1.25 MHz)
//AD1CON2bits.SMPI = 0; // SMPI must be 0
//
////AD1CHS0/AD1CHS123: Analog-to-Digital Input Select Register
//AD1CHS0bits.CH0SA = 0; // MUXA +ve input selection (AIN0) for CH0
//AD1CHS0bits.CH0NA = 0; // MUXA -ve input selection (VREF-) for CH0
//
//AD1CHS123bits.CH123SA = 0; // MUXA +ve input selection (AIN0) for CH1
//AD1CHS123bits.CH123NA = 0; // MUXA -ve input selection (VREF-) for CH1
//
////AD1PCFGH/AD1PCFGL: Port Configuration Register
AD1PCFGL = 0xFFFF;
AD1PCFGLbits.PCFG0 = 0; // AN0 as Analog Input
AD1PCFGLbits.PCFG1 =0;// 0; // AN1 as Analog Input
AD1PCFGLbits.PCFG2 = 0; // AN2 as Analog Input
AD1PCFGLbits.PCFG3 = 0; // AN3 as Analog Input

IFS0bits.AD1IF = 0; // Clear the Analog-to-Digital interrupt flag bit
IEC0bits.AD1IE = 1; // Do Not Enable Analog-to-Digital interrupt
AD1CON1bits.ADON = 1; // Turn on the ADC
    
    AD1CON2bits.SMPI=3;
    AD1CON2bits.CHPS=0b00;
    AD1CON2bits.BUFM=0;
    AD1CON2bits.ALTS=0;
   
    AD1CON2bits.CSCNA=1;
    AD1CHS0bits.CH0NA=0;
    AD1CSSLbits.CSS0=1;   //AN0 
    AD1CSSLbits.CSS1=1;   //AN1  
    AD1CSSLbits.CSS2=1;   //AN1  
    AD1CSSLbits.CSS3=1;   //AN2
    
    
}