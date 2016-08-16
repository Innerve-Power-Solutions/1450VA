/* 
 * File:   LCD.h
 * Author: Girisha
 *
 * Created on 24 October, 2015, 3:11 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<xc.h>
#include<stdio.h>
#include<stdlib.h>
//#include "TimeDelay.h"


// LCD Commands
#define LCD_CMD_8BIT_1LINE              0x30
#define LCD_CMD_8BIT_2LINE              0x38
#define LCD_CMD_4BIT_1LINE              0x20
#define LCD_CMD_4BIT_2LINE              0x28
#define LCD_CMD_ENTRY_MODE              0x06
#define LCD_CMD_CURSOR_OFF_DDR_ON       0x08
#define LCD_CMD_CURSOR_ON               0x0E
#define LCD_CMD_CURSOR_OFF              0x0C
#define LCD_CMD_CURSOR_BLINK            0x0F
#define LCD_CMD_DISP_SHIFT_L            0x18
#define LCD_CMD_DISP_SHIFT_R            0x1C
#define LCD_CMD_MOV_CUR_L               0x10
#define LCD_CMD_MOV_CUR_R               0x14
#define LCD_CMD_DISP_CLEAR              0x01
#define LCD_CMD_SET_CUR_POS(addr)       (0x80 + addr)
#define LCD_CMD_SET_CGRAM_ADDR(addr)    (0x40 + addr)
   

    
#define EN LATBbits.LATB10    //B5           //EN
#define RS LATBbits.LATB11    //B7       //RS
////#define RW LATBbits.LATB6           //RW
//#define EN LATBbits.LATB5   //EN
//#define RS LATBbits.LATB7   //RS
//#define RW LATBbits.LATB6   //RW


void command_lcd(unsigned char );
void data_string_lcd(unsigned char *);
void data_lcd(unsigned char );
void LCD_init(void);
void nybble(void);



#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

