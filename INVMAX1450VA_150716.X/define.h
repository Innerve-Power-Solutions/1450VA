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

//Kashyap: This is going to work on version control platform: "git" 

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DEFINE_HEADER_TEMPLATE_H
#define	DEFINE_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include<stdint.h>


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
#define FCY 14950000UL
#define PWM_FREQ   10000
#define TMR_FREQ   4000           
#define PWM_PERIOD (int16_t)(FCY/PWM_FREQ)/2
#define TMR_PERIOD (int16_t)(FCY/TMR_FREQ)
#define PDC_COUNT (PWM_PERIOD*2+1) 
#define SINE_FREQ 50
#define STEP        (uint16_t) (65535/(PWM_FREQ/SINE_FREQ))
#define NO_OF_CYCLES 1
#define MOD_CONTROL_COUNT    ((TMR_FREQ/SINE_FREQ)*NO_OF_CYCLES)
    
#include "libpic30.h"
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

