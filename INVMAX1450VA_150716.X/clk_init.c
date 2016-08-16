#include "clk_init.h"

void Init_Clk(void)
{
// Configure Oscillator to operate the device at 16 MHz
 // Set FRC to approximately 8 MHz
    OSCTUN = 0x001F;
   __builtin_write_OSCCONH(0x01);     // New Oscillator selection FRC w/ PLL
   __builtin_write_OSCCONL(0x01);     // Enable Switch

   while(OSCCONbits.COSC != 0b001); //0x011   // Wait for Osc. to switch to FRC w/ PLL
   while(OSCCONbits.LOCK != 1);        // Wait for PLL to Lock
//  __delay_us(50);
//

}