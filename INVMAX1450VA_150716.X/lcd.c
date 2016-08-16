
#include <xc.h>
#include "LCD.h"
#include "stdint.h"
#include "string.h"
#define FCY 14950000UL
#include "libpic30.h"
unsigned char check;


void LCD_init(void)
{
   
    command_lcd(0x01);
    __delay_ms(20);    
    command_lcd(0x30);
    __delay_ms(6);
    nybble();
    __delay_ms(1);
    nybble();
    __delay_ms(1);
    nybble();
    __delay_ms(1);
    command_lcd(LCD_CMD_4BIT_1LINE);        //0x20
    nybble();
    command_lcd(LCD_CMD_4BIT_2LINE);        //0x28,
    command_lcd(0x10);
    command_lcd(0x0F);
    command_lcd(0x0C);
    command_lcd(0x06);
    
  
//    command_lcd(LCD_CMD_8BIT_2LINE);     //0x38               38,10,0C,06
//    command_lcd(LCD_CMD_CURSOR_BLINK);    //0x0F
//    command_lcd(LCD_CMD_CURSOR_OFF);      //0x0C
//    command_lcd(LCD_CMD_DISP_CLEAR);      //0x01
//    command_lcd(LCD_CMD_ENTRY_MODE);      //0x06
}


void data_lcd(unsigned char data)
{
  
    //upper 4 bits
   
     check=data;
    LATAbits.LATA3 = (data>>7)&(0x01); //D7
    LATAbits.LATA2 = (data>>6)&(0x01);  //D6
    LATBbits.LATB8 = (data>>5)&(0x01);  //D5
    LATBbits.LATB9 = (data>>4)&(0x01);   //D4   
  
//     LATBbits.LATB11 = (data>>7)&(0x01); //D7
//    LATBbits.LATB10 = (data>>6)&(0x01);  //D6
//    LATBbits.LATB9 = (data>>5)&(0x01);  //D5
//    LATBbits.LATB8 = (data>>4)&(0x01);   //D4   
//   
//    lcd=data>>4;
//    
//    EN=1;
//    __delay_us(500);
//   // __delay_us(120);
//    //DelayMs(300);
//    EN=0;
    nybble(); 
    //LCDPINS = data<<4;
    //lower 4 bits
    
    check = (data<<4);    
    data = (data<<4);
    LATAbits.LATA3 = (data>>7)&(0x01);
    LATAbits.LATA2 = (data>>6)&(0x01);
    LATBbits.LATB8 = (data>>5)&(0x01);
    LATBbits.LATB9 = (data>>4) &(0x01);
//    LATBbits.LATB11 = (data>>7)&(0x01); //D3
//    LATBbits.LATB10 = (data>>6)&(0x01);  //D2
//    LATBbits.LATB9 = (data>>5)&(0x01);  //D1
//    LATBbits.LATB8 = (data>>4)&(0x01);   //D0   
    nybble();
//    
//    EN=1;
//    __delay_us(500);
//    //__delay_us(120);
//    //DelayMs(300);
//   EN=0;
//    
}
void nybble(void)
{
    EN=1;
    __delay_us(300);
    EN=0;
}
void command_lcd(unsigned char cmd)
{
    RS=0;
    data_lcd(cmd);
}

void data_string_lcd(unsigned char *str)
{
    RS=1;
    while(*str)
    {
        check=*str;
        data_lcd(*str);
        str++;
    }
}

