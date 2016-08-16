/*
 * File:   main.c
 * Author: naresh
 *
 * Created on February 29, 2016, 11:04 PM
 */



// DSPIC33FJ16GP102 Configuration Bit Settings

// 'C' source line config statements
#include "main.h"

//#define FCY     16000000UL
//#include <libpic30.h>
// CONFIG21
// DSPIC33FJ16MC102 Configuration Bit Settings

// 'C' source line config statements

// CONFIG2
#pragma config POSCMOD = NONE          // Primary Oscillator Select (Primary oscillator disabled)
#pragma config ALTI2C = OFF             // Alternate I2C pins (I2C mapped to SDA1/SCL1)
#pragma config LPOL = ON                // Motor Control PWM Low Side Polarity bit (PWM module low side output pins have active-high output polarity)
#pragma config IOL1WAY = OFF            // IOLOCK Protection (Allow Multiple Re-configurations)
#pragma config OSCIOFNC = ON           // Primary Oscillator Output Function (OSC2 pin has clock out function)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is disabled)
#pragma config FNOSC = FRC              // Oscillator Mode (Internal Fast RC (FRC))
#pragma config WDTWIN = WDTWIN25        // Watchdog Window Select (Watchdog Window is 25% of WDT period)
#pragma config PWMPIN = ON             // Motor Control PWM Module Pin Mode bit (PWM module pins controlled by PORT register at device Reset)
#pragma config PWMLOCK = OFF            // PWM Lock Enable (PWM registers may be written without key sequence)
#pragma config IESO = ON                // Internal External Switch Over Mode (Start-up device with FRC, then automatically switch to user-selected oscillator source when ready)

// CONFIG1
#pragma config WDTPOST = PS32768        // Watchdog Timer Postscaler (1:32,768)
#pragma config WDTPRE = PR128           // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config PLLKEN = ON              // PLL Lock Enable (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF             // Watchdog Timer Window (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF //OFF chesa             // Watchdog Timer Enable (Watchdog timer always enabled)
#pragma config ICS = PGD3               // Comm Channel Select (Communicate on PGEC3/PGED3)
#pragma config HPOL = ON                // Motor Control PWM High Side Polarity bit (PWM module high side output pins have active-high output polarity)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Segment Code Protection (General Segment Code protect is disabled)

signed int test=1,test1=0,faultStatusLCD=0;
extern int16_t batOverVoltage,OverLoad,overLoadLimit,outputShort,BatUnderVoltage,batOverVoltage,state,OPShortCkt,InvOff,BatteryUndervoltageLCD,BatteryDeepDischarge,DCOvertempFlag;
extern int16_t LCDrefreshcounter;

int main(void) 
{
   
  //TRISB = 0;
   
  Init_Clk();
//  TRISBbits.TRISB2=0;//debug 
  Init_IO();
//DCDCON    =  1 ;  
  Init_PWM();
  P1TCON=0x8002;//center aligned mode
//__delay_ms(5);
  //__delay_ms(15);  
  PWM1CON1=0x0033;//0x0077;
 
  
  Init_ADC();
  
  LCD_init();     
  
   Init_timer(); 
  
 //  TRISBbits.TRISB10=0;
   FAN=0;
   while(1)
   {  
       
       if(test==1)
       {
       Display();
        __delay_ms(2000);
        test=0;
       }   
       if(LCDrefreshcounter>LCDREFRESHCOUNT)
       {
           LCD_init();
           LCDrefreshcounter=0;
       }   
     faultStatusLCD =((DCOvertempFlag==ENABLED)||(OverLoad==ENABLED)||(overLoadLimit==ENABLED)||(BatteryUndervoltageLCD==ENABLED)||(OPShortCkt==DISABLED)||(BatteryDeepDischarge==ENABLED)||(BatUnderVoltage==ENABLED));
     if(faultStatusLCD==DISABLED)
     { 
          Display1(); 
       __delay_ms(1000);
     if(GRID_ON==ENABLED)
        {
        GridON();
        __delay_ms(1000);
        } 
     else 
        {
        GridOFF();
        __delay_ms(1000);
        }   
     }
     else
     {
       if(DCOvertempFlag==ENABLED)
       {
       DCDCTempFault();
        __delay_ms(1000);
       }      
       if(overLoadLimit==ENABLED)           
       {
       OutputOLShutDown();
        __delay_ms(1000);
       }   
     if(OverLoad==ENABLED)
        {
        OutputOverLoad();
        __delay_ms(1000);
        }
     if(OPShortCkt==DISABLED)
        {
        OutputShortCkt();
        __delay_ms(1000);
        }  
     if(BatteryDeepDischarge==ENABLED)
        {
        BatDeepDischarge();
        __delay_ms(1000);
        }
     if(BatteryUndervoltageLCD==ENABLED)
        {
         BatterUnderVoltage();
         __delay_ms(1000);
        }
     if(batOverVoltage==ENABLED)
        {
        BatOverVoltage();
        __delay_ms(1000);
         }
    }
   }
}



