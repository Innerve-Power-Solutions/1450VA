/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef INTERRUPTS_HEADER_TEMPLATE_H
#define	INTERRUPTS_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#include "define.h"   
#include "Init_IO.h"    
#include <stdint.h>    
#include "motor_control.h"
#include "motor_control_inline_dspic.h"
#include "motor_control_mapping.h"

//#define DC_IN_RANGE     
#define DC_SENSE_GAIN (float)(2.155/400) // According to new schematic version 1.0.3
#define BAT_DC_GAIN (float)(3.3/16)//10.8 UVsetting worked at 10.67 V need to tune this gain
    
#define ADC_GAIN (1024/3.3)             // 10-bit ADC  
#define VDC_GAIN    (float)(ADC_GAIN*DC_SENSE_GAIN) 
#define BAT_VDC_GAIN  (float) (ADC_GAIN*BAT_DC_GAIN)
#define INV_VDC_GAIN  (float)(1/VDC_GAIN)    
#define INV_VDC_GAIN_INT (INV_VDC_GAIN*32767)   
#define BAT_INT_RESOLUTION  (float)(32767/32)          //16 V --> 32767    
#define AC_REF      230    
#define AC_OUTREF   (AC_REF*1.4142)          //Use this in setting Vdcmin


#define BAT_OVRVOLT     28
#define BAT_OVRVOLT_INT (BAT_INT_RESOLUTION*BAT_OVRVOLT)        
#define BAT_UV_BUZZER    21.8//10.8//
#define BAT_UV_BUZZER_INT (BAT_INT_RESOLUTION*BAT_UV_BUZZER)    
#define BAT_UNDERVOLT    21.7//10.8//
#define BAT_UNDERVOLT_INT (BAT_INT_RESOLUTION*BAT_UNDERVOLT)    
#define BAT_DEEP_DISCHARGE    21.2//10.8//
#define BAT_DEEP_DISCHARGE_INT    (BAT_INT_RESOLUTION*BAT_DEEP_DISCHARGE)//10.8//


#define BAT_MIN_LIMIT_INT (BAT_INT_RESOLUTION*BAT_DEEP_DISCHARGE)
    
    
    

#define IOUT_SENSE_GAIN         (float) 0.137//0.47//15//0.157//3.3/21 Shunt resistance value (3.3/(IOUTRMS_MAXSENSE*1.4142135))    //---> 3.3/peak current
#define IOUTAVG_MAXSENSE        (float) ((3.3*3.2)/IOUT_SENSE_GAIN)//3.2 is scaling factor//9.92//21 for 0.157//20.625   //3.3/0.157----> 11.313 A rms --->32767 , 3.3 on ADC
//#define IOUT_GAIN               (float) (ADC_GAIN*IOUT_SENSE_GAIN)//145//48.67    
#define IOUT_INT_RESOLUTION     (float)(32767/(IOUTAVG_MAXSENSE))//3303  //1560  
#define IOUT_RMSOVERLOAD        (float)(5*(4.5/1.9))//(1.2*0.88)//1.2A--->1 A (actual)0.88 is scaling factor(0.6)//(4.25)     //FUll load = 3.7, overloadavg = 3.7*1.15 = 4.25 V
//0.67 A for 0.7 A setting , 1.04 A for 1.2 A setting

#define IOUT_OVRLOAD            (float)(IOUT_RMSOVERLOAD/1.11)   //AVG=4.25/1.11=3.82 A
#define IOUT_OVRLOAD_INT        (IOUT_OVRLOAD*IOUT_INT_RESOLUTION)//
#define IOUT_RMSSHORTCKT        (float)(5.55)    
#define IOUT_SHORTCKT           (float)(IOUT_RMSSHORTCKT/1.11)    //AVG SHORT CKT I=5 A
#define IOUT_SHORTCKT_INT       (IOUT_SHORTCKT*IOUT_INT_RESOLUTION) //11022


#define BATERYUVSECS            5
#define BATUV_SECS              (BATERYUVSECS*SINE_FREQ)
#define NO_OF_UVRESETS          6    
#define UVRESET_SECS            8
#define UVRESET_SECS_COUNTER   (UVRESET_SECS*SINE_FREQ)  

//#define IOUTRMS_MAXSENSE         16/1.414213   //----> 11.313 A rms --->32767 , 3.3 on ADC
//#define IOUT_SENSE_GAIN         (float)(3.3/(IOUTRMS_MAXSENSE*1.4142135))    //---> 3.3/peak current
//#define IOUT_GAIN               (float) (ADC_GAIN*IOUT_SENSE_GAIN)    
//#define IOUT_INT_RESOLUTION     (float)(32767/16)  
//#define IOUT_OVRLOAD            (float)(6*1.4142135)    //Peak value
//#define IOUT_OVRLOAD_INT        (IOUT_OVRLOAD*IOUT_INT_RESOLUTION)
//#define IOUT_SHORTCKT           (float)(8*1.4142135)   //Peak value
//#define IOUT_SHORTCKT_INT       (IOUT_OVRLOAD*IOUT_INT_RESOLUTION)
/*Soft start defines*/
#define SOFTSTART       1
#define STEADYSTATE     2 
#define NO_OF_STEPS     1//10    
#define NO_OF_CYCLES_SOFTSTART  (NO_OF_STEPS/NO_OF_CYCLES)    
#define SOFTSTARTSTEP   (26620/NO_OF_CYCLES_SOFTSTART)  //after softstart modulation index = 0.81(26620)

/*over load algorithm*/
#define NO_SECS_OVERLOAD        40        //1300 seconds is the limit for progrmming over load time
#define OVERLOADCYCLES          (NO_SECS_OVERLOAD*SINE_FREQ)    
#define NO_OF_RESETS    6
#define NO_OF_RESET_SECS      10    
#define RESET_SECS_COUNTER   (NO_OF_RESET_SECS*SINE_FREQ)  

#define MINDC_SOFTSTRT  280 // 300
#define MINDC_OFFPWMS 250// 250 
#define DC_OVRVOLT    430
#define ENABLED             1
#define DISABLED            0    
#define LCDREFRESHSECS      3
#define LCDREFRESHCOUNT     (LCDREFRESHSECS*SINE_FREQ)    
#ifdef	__cplusplus
}
#endif /* __cplusplus */  

#endif	/* XC_HEADER_TEMPLATE_H */

