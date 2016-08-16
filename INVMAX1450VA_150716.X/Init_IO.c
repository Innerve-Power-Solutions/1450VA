
/*
 * File:   Init_IO.c
 * Author: naresh
 *
 * Created on April 18, 2016, 7:37 PM
 */


#include "Init_IO.h"

void Init_IO(void)
{
    AD1PCFGLbits.PCFG5  = 1;    //GRID_ON pin as digital input
    AD1PCFGLbits.PCFG4  = 1;    //BUzzer pin as digital input
    TRISBbits.TRISB2    = INPUT;//OUTPUT;          //BUZZER
    TRISBbits.TRISB3    = INPUT;          //GRIDON signal
   // TRISBbits.TRISB5 = INPUT;           //Hardware Fault detection
    TRISBbits.TRISB6    = OUTPUT;          //To keep PWMs active it(FLTA pin) should be output and ON
    TRISBbits.TRISB7    = OUTPUT;          //Fault to switch off DC DC

    TRISAbits.TRISA4 = OUTPUT;          //FAN control
    
    TRISBbits.TRISB8 = OUTPUT;          //To keep PWMs active it(FLTA pin) should be output and ON
    TRISBbits.TRISB9 = OUTPUT;          //Fault to switch off DC DC
    TRISBbits.TRISB10 =OUTPUT;          //To keep PWMs active it(FLTA pin) should be output and ON
    TRISBbits.TRISB11 =OUTPUT;          //To keep PWMs active it(FLTA pin) should be output and ON
    TRISAbits.TRISA3 = OUTPUT;          //Fault to switch off DC DC
    TRISAbits.TRISA2 = OUTPUT;          //To keep PWMs active it(FLTA pin) should be output and ON
       
}
