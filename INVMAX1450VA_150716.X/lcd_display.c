
#include "lcd_mc.h"
#include "interrupts.h"
unsigned int voltage=250,current=250;
extern  int16_t Vdc,Vbat;
extern int16_t batteryVolt;
extern int BatUnderVoltage,state;
int16_t batTen=0,batTen1=0,batOne=0,batOne1=0,batPoint=0,batPoint1=0,batTwoPoint=0,batTwoPoint1=0;

void Display1(void)
{
    char dispBuff[20];
    command_lcd(LCD_CMD_SET_CUR_POS(0x00)); // first line addr
    //sprintf(dispBuff, "INVMAX  850VA   ");
    //sprintf(dispBuff, "V : %1.1f I : %1.2f", 1.0,2.00);
    sprintf(dispBuff, "DC Voltage:  %3d", Vdc);
    data_string_lcd((unsigned char *)dispBuff);
   
    batTen=__builtin_divsd(Vbat,10240);
    batOne1=Vbat - __builtin_mulss(batTen,10240);
    batOne=__builtin_divsd(batOne1,1024);
    batPoint1=batOne1-__builtin_mulss(batOne,1024);
    batPoint=__builtin_divsd(batPoint1,102);
    batTwoPoint1=batPoint1-__builtin_mulss(batPoint,102);
    batTwoPoint= __builtin_divsd(batTwoPoint1,10);       

    command_lcd(LCD_CMD_SET_CUR_POS(0x40)); // second line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "BattryVolt:%d%d.%d%d ", batTen,batOne,batPoint,batTwoPoint);
   // sprintf(dispBuff, "INNERVE POWERSOL");
    data_string_lcd((unsigned char *)dispBuff);       
}
void DCDCTempFault(void)
{
    char dispBuff[20];
    command_lcd(LCD_CMD_SET_CUR_POS(0x00)); // first line addr
    memset(dispBuff, 0, 20);
    //sprintf(dispBuff, "INVMAX  850VA   ");
    //sprintf(dispBuff, "V : %1.1f I : %1.2f", 1.0,2.00);
    sprintf(dispBuff, "OVER TEMPERATURE");
    data_string_lcd((unsigned char *)dispBuff);

    command_lcd(LCD_CMD_SET_CUR_POS(0x40)); // second line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "    SHUT DOWN   ");
    data_string_lcd((unsigned char *)dispBuff);       

}
void OutputOLShutDown(void)
{
    char dispBuff[20];
    command_lcd(LCD_CMD_SET_CUR_POS(0x00)); // first line addr
    memset(dispBuff, 0, 20);
    //sprintf(dispBuff, "INVMAX  850VA   ");
    //sprintf(dispBuff, "V : %1.1f I : %1.2f", 1.0,2.00);
    sprintf(dispBuff, "    OVER LOAD   ");
    data_string_lcd((unsigned char *)dispBuff);

    command_lcd(LCD_CMD_SET_CUR_POS(0x40)); // second line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "    SHUT DOWN   ");
    data_string_lcd((unsigned char *)dispBuff);       

}

void OutputOverLoad(void)
{
    char dispBuff[20];
    command_lcd(LCD_CMD_SET_CUR_POS(0x00)); // first line addr
    memset(dispBuff, 0, 20);
    //sprintf(dispBuff, "INVMAX  850VA   ");
    //sprintf(dispBuff, "V : %1.1f I : %1.2f", 1.0,2.00);
    sprintf(dispBuff, "    OVER LOAD   ");
    data_string_lcd((unsigned char *)dispBuff);

    command_lcd(LCD_CMD_SET_CUR_POS(0x40)); // second line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "       ON       ");
    data_string_lcd((unsigned char *)dispBuff);       
    
}

void GridON(void)
{
    char dispBuff[20];
    command_lcd(LCD_CMD_SET_CUR_POS(0x00)); // first line addr
    memset(dispBuff, 0, 20);
    //sprintf(dispBuff, "INVMAX  850VA   ");
    //sprintf(dispBuff, "V : %1.1f I : %1.2f", 1.0,2.00);
    sprintf(dispBuff, "   MAINS ON     ");
    data_string_lcd((unsigned char *)dispBuff);

    command_lcd(LCD_CMD_SET_CUR_POS(0x40)); // second line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "   INVERTER OFF ");
    data_string_lcd((unsigned char *)dispBuff);       
    
}
void GridOFF(void)
{
    char dispBuff[20];
    command_lcd(LCD_CMD_SET_CUR_POS(0x00)); // first line addr
    memset(dispBuff, 0, 20);
    //sprintf(dispBuff, "INVMAX  850VA   ");
    //sprintf(dispBuff, "V : %1.1f I : %1.2f", 1.0,2.00);
    sprintf(dispBuff, "   MAINS   OFF  ");
    data_string_lcd((unsigned char *)dispBuff);

    command_lcd(LCD_CMD_SET_CUR_POS(0x40)); // second line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "  INVERTER  ON  ");
    data_string_lcd((unsigned char *)dispBuff);       
    
}
void OutputShortCkt(void)
{
    char dispBuff[20];
    command_lcd(LCD_CMD_SET_CUR_POS(0x00)); // first line addr
    memset(dispBuff, 0, 20);
    //sprintf(dispBuff, "INVMAX  850VA   ");
    //sprintf(dispBuff, "V : %1.1f I : %1.2f", 1.0,2.00);
    sprintf(dispBuff, "  SHORT CIRCUIT   ");
    data_string_lcd((unsigned char *)dispBuff);

    command_lcd(LCD_CMD_SET_CUR_POS(0x40)); // second line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "                ");
    data_string_lcd((unsigned char *)dispBuff);       
    
}
void BatDeepDischarge(void)
{
    char dispBuff[20];
    command_lcd(LCD_CMD_SET_CUR_POS(0x00)); // first line addr
    memset(dispBuff, 0, 20);
    //sprintf(dispBuff, "INVMAX  850VA   ");
    //sprintf(dispBuff, "V : %1.1f I : %1.2f", 1.0,2.00);
    sprintf(dispBuff, "BATTERY VOLTAGE ");
    data_string_lcd((unsigned char *)dispBuff);

    command_lcd(LCD_CMD_SET_CUR_POS(0x40)); // second line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "DEEP DISCHARGE  ");
    data_string_lcd((unsigned char *)dispBuff);       
    
}
void BatterUnderVoltage(void)
{
    char dispBuff[20];
    command_lcd(LCD_CMD_SET_CUR_POS(0x00)); // first line addr
    memset(dispBuff, 0, 20);
    //sprintf(dispBuff, "INVMAX  850VA   ");
    //sprintf(dispBuff, "V : %1.1f I : %1.2f", 1.0,2.00);
    sprintf(dispBuff, "  LOW  BATTERY  ");
    data_string_lcd((unsigned char *)dispBuff);

    command_lcd(LCD_CMD_SET_CUR_POS(0x40)); // second line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "REDUCE THE LOAD ");
    data_string_lcd((unsigned char *)dispBuff);       

}
void BatOverVoltage(void)
{
    char dispBuff[20];
    command_lcd(LCD_CMD_SET_CUR_POS(0x00)); // first line addr
    memset(dispBuff, 0, 20);
    //sprintf(dispBuff, "INVMAX  850VA   ");
    //sprintf(dispBuff, "V : %1.1f I : %1.2f", 1.0,2.00);
    sprintf(dispBuff, "     BATTERY    ");
    data_string_lcd((unsigned char *)dispBuff);

    command_lcd(LCD_CMD_SET_CUR_POS(0x40)); // second line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "  OVER VOLTAGE  ");
    data_string_lcd((unsigned char *)dispBuff);       
    
}
void Display(void)
{
    char dispBuff[20];
    command_lcd(LCD_CMD_SET_CUR_POS(0x00)); // first line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "INVMAX 1450VA   ");
    //sprintf(dispBuff, "V : %1.1f I : %1.2f", 1.0,2.00);
    //sprintf(dispBuff, "V :  %3d I : %3d", voltage, current);
    data_string_lcd((unsigned char *)dispBuff);

    
    command_lcd(LCD_CMD_SET_CUR_POS(0x40)); // second line addr
    memset(dispBuff, 0, 20);
    sprintf(dispBuff, "DYTECH  POWER   ");
    data_string_lcd((unsigned char *)dispBuff);       
}