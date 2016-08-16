/*
 * File:   issue_codemain.c
 * Author: I16085
 *
 * Created on March 13, 2016, 2:06 PM
 */


#include "xc.h"

// CONFIG2
#pragma config POSCMOD = HS             // Primary Oscillator Select (HS Oscillator mode selected)
#pragma config ALTI2C = OFF             // Alternate I2C pins (I2C mapped to SDA1/SCL1)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config IOL1WAY = ON             // IOLOCK Protection (Allow Only One Re-configuration)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2 pin has clock out function)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = PRIPLL           // Oscillator Mode (Primary Oscillator (MS, HS, EC) w/ PLL)
#pragma config WDTWIN = WDTWIN25        // Watchdog Window Select (Watchdog Window is 25% of WDT period)
#pragma config PWMPIN = ON              // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)
#pragma config PWMLOCK = ON             // PWM Lock Enable (Certain PWM registers may only be written after key sequence)
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// CONFIG1
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config PLLKEN = ON              // PLL Lock Enable (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = ON           // Watchdog Timer Enable (Watchdog timer enabled/disabled by user software)
#pragma config ICS = PGD3               // Comm Channel Select (Communicate on PGEC3/PGED3)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Segment Code Protection (General Segment Code protect is disabled)


int main(void) {
   
TRISBbits.TRISB2=0;
LATBbits.LATB2=1;
while(1)
{}
}
