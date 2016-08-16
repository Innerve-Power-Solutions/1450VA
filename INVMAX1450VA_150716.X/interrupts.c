#include "interrupts.h"
  
unsigned int theta=0,sinu=0,cosinu=0,state=0;
int16_t mod_ind=0,count,modulationIndex=0,an0result=0,an1result=0,an2result=0,an3result=0;
int16_t DCVoltage=0,batteryVoltage=0,batVoltage=0,batV=0,VBatcounter=0;
MC_SINCOS_T lsincos;
int16_t Vdc=0,Vdcmin=0;
int16_t Vbat=0;  
int16_t batteryVolt=0;
//int16_t Vbat=0;
int16_t softStartCounter=0,stopCounter=0,softStartFlag=0,softStartSteps=0,clearCountersFlag=0,overLoadCounterFlag=0;
int16_t DClinkCounter=0,BatteryCounter=0,DCOverCounter=0,batOverCounter=0;
int16_t DCvoltInRange=0,BatVoltInRange=0,reversePolarity=0,shortCircuitFlt=0,outputOverLoad=0,DCOverTempCounter=0,DCOvertempFlag=0,DCShort=0;
int16_t DCOverVoltage=0,batOverVoltage=0,outputCurrent=0,Iload=0,IOverCounter=0,OverLoad=0;
int16_t shortCktCounter=0,outputShort=0, BatUVcounter=0,BatUnderVoltage=0,faultStatus=0;
int16_t reversePolarityFlag=0,reversePolCounter=0,DCUnderCounter=0,DCUnderVoltage=0,localFaultLatch=0,OPShortCkt=0,InvOff=0;
int16_t avgVdcCounter=0,an0reslt=0,an1reslt=0,an3reslt=0,avgBatCounter=0,ICounter=0,overLoadLimit=0;
int16_t resetFlag=0,InvResetCount=0,restartTime=0,checkOLCycles=0;
int16_t BatteryDeepDischarge=0,BatDDcounter=0,BatUVResetCount=0,UVresetFlag=0,UVrestartTime=0,BatteryUndervoltageLCD=0;
int16_t LCDrefreshcounter=0;
void __attribute__((interrupt, no_auto_psv)) _MPWM1Interrupt(void)
{
  
    //LATBbits.LATB12 =1;  
 //   LATBbits.LATB2 =1;
   if(modulationIndex==0)
   {
       P1DC1=0;
       P1DC2=0;
       theta=0;
   }
   else
   {
   P1DC1=(__builtin_mulss(sinu,PDC_COUNT))>>15;
   P1DC2=(__builtin_mulss(cosinu,PDC_COUNT))>>15;
   theta=(theta+STEP);//step=164 for 50 Hz sine, 20k pwm freq
   }
    
    MC_CalculateSineCosine_InlineC_Ram(theta,&lsincos);
    
 mod_ind = (__builtin_mulss(modulationIndex,lsincos.sin))>>15;
  
 //  mod_ind = (__builtin_mulss(26620,lsincos.sin))>>15;
   
   sinu=(32767-(uint16_t)mod_ind)>>1;
   cosinu=(32767+(uint16_t)mod_ind)>>1;  
//    cosin1=(32768-cosin)>>1;//cosin)>>1;
//    
//    test1=(__builtin_mulss(test1,800))>>14;
//    cosin1=(__builtin_mulss(cosin1,800))>>14;
//    
   
    IFS3bits.PWM1IF = 0;
   // LATBbits.LATB2 = 0;
   // LATBbits.LATB12 =0;
}

void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
{
   
    an0result=ADC1BUF0;
    an1result=ADC1BUF1;
    an2result=ADC1BUF2;
    an3result=ADC1BUF3;
    
    an0reslt = an0reslt + an0result; 
    avgVdcCounter++;
    if(avgVdcCounter>31)
    {
        DCVoltage=(an0reslt>>5);
        avgVdcCounter=0;
        an0reslt=0;
    }
    
    
    an1reslt = an1reslt + an1result;
    avgBatCounter++;
    if(avgBatCounter>31)
    {
        batteryVoltage=(an1reslt>>5);
        avgBatCounter=0;
        an1reslt=0;
    }
    
   an3reslt = an3reslt + an3result;
   ICounter++;
    if(ICounter>49)
    {
        outputCurrent=(an3reslt/50);
     //   outputCurrent=0;
        ICounter=0;
        an3reslt=0;
    }
    
//    
//    avgVbatCounter++;
//    if(avgVbatCounter>8)
//    {
//        batteryVoltage=an1result;
//        avgVbatCounter=0;
//    }
//    
    
   
    //outputCurrent=an3result;

    Vdc=(__builtin_mulss(DCVoltage,INV_VDC_GAIN_INT))>>15;
    Vdcmin = Vdc;
 //   Vdc = INV_VDC_GAIN;//AC_REF*32767/Vdc
    ///modulationIndex = Vdc_gain;
    
//    if(Vdcmin<=355)
//    {
//        Vdcmin=355;
//    }
//    
    if(Vdcmin<=328)
    {
        Vdcmin=328;
    }
    
    Vbat = (batteryVoltage<<5); 

   
    Iload = (outputCurrent<<5);       //Iload is peak current not rms
   
    IFS0bits.AD1IF = 0;

}


void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    /*fault detection*///DCvoltInRange=0,
    //BatVoltInRange=0,
    //reversePolarity=0,
    //shortCircuitFlt=0,
    //outputOverLoad=0
  //  reversePolarity=LATBbits.LATB3;
//   
    GRID_ON=PORTBbits.RB3;
    OPShortCkt=PORTBbits.RB5; //to be shifted to RB4
    InvOff  =PORTBbits.RB2;

    if((GRID_ON==0)&&(InvOff==0))
  {    
      if((state==0)&&(faultStatus==0)&&(localFaultLatch==DISABLED)&&(UVresetFlag==0)&&(resetFlag==0))     //Local fault latch is to latch when fault occurs while grid is off but it is reset when grid is off and ons
      {      
        DCDCON    =   1;
      }
  }
  else
  {
  DCDCON    =   0;
  /*reset all faults when GRID is ON and then OFF*/
  state=0;
  clearCountersFlag=DISABLED;
  DCvoltInRange=DISABLED;
  DCOverVoltage=DISABLED;
  DCUnderVoltage=DISABLED;
  BatVoltInRange=DISABLED;
  batOverVoltage=DISABLED;
  BatUnderVoltage=DISABLED;
  localFaultLatch=DISABLED;
  DCOvertempFlag=DISABLED;
  /*overload related flags*/
  overLoadLimit=DISABLED;
  OverLoad=DISABLED;
  IOverCounter=0;
  InvResetCount=0;
  overLoadCounterFlag=0;
  resetFlag=0;
  restartTime=0;
  
  /*Battery Under voltage flags*/
  BatteryUndervoltageLCD=0;
  BatUVResetCount=0;
  UVresetFlag=0;
  BatteryDeepDischarge=0;
  UVrestartTime=0;
  }
//  
    if(reversePolarity == 1)
        {
            reversePolCounter++;
            if(reversePolCounter>=100)
            {
            reversePolarityFlag=ENABLED;
            reversePolCounter=0;
            }      
        }
        else
        {
            reversePolCounter=0;
        }
     //   BUZZER = 1;
  
        if((Vdc > MINDC_SOFTSTRT)&&(DCvoltInRange==DISABLED)&&(Vdc<(DC_OVRVOLT-10)))      //Hysteresis in voltage is 10 V
        {
            DClinkCounter++;
            if(DClinkCounter>=100)
            {      
                
            DCvoltInRange=ENABLED;
           // LATBbits.LATB6=DISABLED; //GPIO to avoid switching off DC-DC converter
            DClinkCounter=0;
            DCOverVoltage=DISABLED;
            DCUnderVoltage=DISABLED;
            }      
        }
        else
        {    
            DClinkCounter=0;
        }
        
        if(Vdc>DC_OVRVOLT) 
            {
            DCOverCounter++;
                if(DCOverCounter>=50)
                {
                DCOverVoltage=ENABLED;                
           //     DCDCON = 0;
            //    LATBbits.LATB6 = ENABLED; //GPIO to switch off DC-DC converter
                DCvoltInRange = DISABLED;
                DCOverCounter=0;
                }      
            }
        else
            {DCOverCounter=0;}
    
        if(Vdc < MINDC_OFFPWMS)
        {
          DCUnderCounter++;
                if(DCUnderCounter>=100)
                {
                DCUnderVoltage=ENABLED;                              
                DCvoltInRange = DISABLED;
                DCUnderCounter=0;
                }      
        }
 
        if(Vbat>BAT_OVRVOLT_INT)  //Latched fault, once overvoltage is set system will be off till system reset
                {
                batOverCounter++;
                    if(batOverCounter>=200)
                    {
                    batOverVoltage=ENABLED;
                     //  DCDCON=0;
               //     LATBbits.LATB6=ENABLED;//GPIO to switch off DC-DC converter
                    batOverCounter=0;
                   BatVoltInRange=DISABLED;
                    }      
                }
        else 
            {batOverCounter=0;}
//  
     
        if((Vbat>BAT_MIN_LIMIT_INT)&&(BatVoltInRange==DISABLED)&&(Vbat<BAT_OVRVOLT_INT))
            {
            BatteryCounter++;
                if(BatteryCounter>=200)
                {
                BatVoltInRange=ENABLED;
                batOverVoltage=DISABLED;
                BatUnderVoltage=DISABLED;
            //    LATBbits.LATB6 = DISABLED;
                BatteryCounter=0;
                }      
            }
        else 
            {
            BatteryCounter=0;
            
            }

        
        if((Vbat<BAT_DEEP_DISCHARGE_INT)&&(BatteryDeepDischarge==DISABLED))
            {
            BatDDcounter++;
                if(BatDDcounter>=2000)
                {
                BatteryDeepDischarge = ENABLED;
             //DCDCON=0;
                BatDDcounter=0;
                BatVoltInRange=DISABLED;
                }      
            }
        else
            {BatDDcounter=0;}
        
        
/* State Machine*/
    if((DCvoltInRange==ENABLED)&&(state==DISABLED))//&&(resetFlag==0))//&&(BatVoltInRange==ENABLED))//&&(reversePolarityFlag==DISABLED))//
        {
        clearCountersFlag = DISABLED; 
        softStartCounter++;
            if(softStartCounter>=100)
            {
            //FAN=1;    
            state = SOFTSTART;
            softStartFlag=ENABLED;
            softStartCounter=0;
            }
        }
    else 
        {softStartCounter=0;}
    
    if(state == SOFTSTART)
    {
    
        modulationIndex=26620;
        state          = STEADYSTATE; 
    }    
        
    if((BatVoltInRange==ENABLED)&&(DCDCON==1)&&(InvOff==DISABLED)&&(GRID_ON==DISABLED)&&(Vdc<30))//short circuit fault(GPIO input) to be included
        {                
            DCOverTempCounter++;
            if(DCOverTempCounter>=200)              //check for 5 msec
            {
            DCOvertempFlag=ENABLED;   
            DCOverTempCounter=0;
           }              
        }
        else
        {
           DCOverTempCounter=0;
        }
    
    if(OPShortCkt==DISABLED)
    {
     DCDCON = 0;
    }
    if(BatteryDeepDischarge==ENABLED)
    {
            DCDCON = 0;  
            localFaultLatch=ENABLED;
    }
    //DCDC off in fault condition
    if(((state!=0)&&((DCDCON==1)&&(DCvoltInRange==DISABLED)))||(overLoadLimit==ENABLED))//||(outputShort==ENABLED)
        {
        DCDCON = 0;        //comment this line to avoid DCDCOFF
        localFaultLatch=ENABLED;
        }     
  // //Inverter off in fault condition
    if((DCvoltInRange==DISABLED))//||(BatteryDeepDischarge==ENABLED))//
        {
        stopCounter++;
            if(stopCounter>=50)                              //TO introduce delay b/w DCDCOFF and INVERTER OFF to avoid DC shootup
            {
            clearCountersFlag=ENABLED;  //comment this line to avoid INVERTER OFF 
            stopCounter=0;
            }   
        }
    else 
        {
        stopCounter=0;
        }
     
    if(count==MOD_CONTROL_COUNT)                                //20msec if condition
    {
        
   LCDrefreshcounter++;
     /*Battery Deep discharge algorithm */
      
        /*check for battery under voltage(<22.5) and ring buzzer*/
   if(((Vbat<=BAT_UV_BUZZER_INT)&&(BatteryDeepDischarge==DISABLED)&&(GRID_ON==DISABLED)&&(InvOff==DISABLED))||(OverLoad==ENABLED))
            {            
                FAN=ENABLED;
              if((Vbat<=BAT_UV_BUZZER_INT)&&(BatteryDeepDischarge==DISABLED))  
              {
                  BatteryUndervoltageLCD=1;
              }   
                //BUZZER =~BUZZER;
            }
        else 
            {
                FAN=DISABLED;            
                BatteryUndervoltageLCD=0;
                //BUZZER = 0;
            }
        /*Monitor Battery UV >21.5,<22 for 5 secs*/
          /*switch off DCDC and if UVreset happens for 6 times, Permanently Switch off DCDC*/
          if((Vbat<=BAT_UNDERVOLT_INT)&&(Vbat>BAT_DEEP_DISCHARGE_INT)&&(DCDCON==1))
            { 
             BatUVcounter++;      
                if(BatUVcounter>=BATUV_SECS)                         //no. of seconds/20msec
                {
                BatUVResetCount++;                 
                DCDCON=0;
                if(BatUVResetCount>NO_OF_UVRESETS)
                {    
                 UVresetFlag=1;
                 BatteryDeepDischarge=ENABLED;
                }                   
                BatUVcounter=0;
                }
            }
        else 
            {
            BatUVcounter=0;
            }
        /* restart after 8 secs  */
        if((BatUVResetCount>0)&&(BatUVResetCount<=NO_OF_UVRESETS)&&(DCDCON==0))
         {
            UVrestartTime++;
             if(UVrestartTime<UVRESET_SECS_COUNTER)
            {     
            UVresetFlag=1;
            }            
            else
            {
            UVrestartTime=0;     
            UVresetFlag=0;
            }    
        }  
        
          
/*Over load and auto reset algorithm in overload software*/          
        if(Iload>IOUT_OVRLOAD_INT)//&&(OverLoad==DISABLED))
            {            
                OverLoad=ENABLED;                            
                //FAN=1;
                //BUZZER =~BUZZER;
            }
        else 
            {
                OverLoad=DISABLED;            
                //FAN=0;
                //BUZZER = 0;
            }
        /*Monitor Overload for 40 secs then switch off inverter*/
         if(OverLoad==ENABLED)
            { 
             
             IOverCounter++;
                if(IOverCounter>=OVERLOADCYCLES)                         //no. of seconds/20msec
                {
                
                InvResetCount++;                
                DCDCON = 0;
                overLoadCounterFlag=ENABLED;
                
                if(InvResetCount>NO_OF_RESETS)
                {                   
                 resetFlag=1;
                 overLoadLimit=ENABLED;
                }                   
                IOverCounter=0;
                }
            }
        else 
            {            
            IOverCounter=0;
            }
        /*Disable all flags and counters if overload is removed in steady state & during auto reset algorithm*/
        if((OverLoad==DISABLED)&&(state==STEADYSTATE))
        {
        checkOLCycles++;
             if(checkOLCycles>5)
            { 
            resetFlag=0;
            InvResetCount=0;
            restartTime=0;
            checkOLCycles=0;
            }   
        }
        else
        {
        checkOLCycles=0;
        }    
        
        /*Wait for 6 secs to restart the inverter*/
        if((InvResetCount>0)&&(InvResetCount<=NO_OF_RESETS)&&(overLoadCounterFlag==ENABLED))
         {
            restartTime++;
             if(restartTime<RESET_SECS_COUNTER)
            {     
            resetFlag=1;
            }            
            else
            {
            restartTime=0;     
            resetFlag=0;
            }    
        }
      
   
        
        
//        if((state!=0)&&(Iload>IOUT_OVRLOAD_INT)&&(OverLoad==DISABLED))
//            {
//             IOverCounter++;
//                if(IOverCounter>=5)                         //5 cycles
//                {
//                OverLoad=ENABLED;                
//                IOverCounter=0;
//                }      
//            }
//        else 
//            {IOverCounter=0;}
//        
//        if((state!=0)&&(Iload>IOUT_SHORTCKT_INT))   //Latched fault, once short ckt is set system will be off till system reset
//            {
//             shortCktCounter++;
//                if(shortCktCounter>=1)                       //1 cycles       
//                {
//                outputShort=ENABLED;                
//                shortCktCounter=0;
//                }      
//            }
//        else 
//            {shortCktCounter=0;}
        
        switch(state)
        {    
           case SOFTSTART:       
               
            modulationIndex = modulationIndex + SOFTSTARTSTEP;
            softStartSteps++;
            if(softStartSteps>=NO_OF_STEPS)
            {
                state= STEADYSTATE;
            }
            
            break;
   
           case STEADYSTATE:
            
            modulationIndex =  __builtin_divsd(((long)AC_OUTREF<< 15),Vdcmin);
            
            break;
                   
        }
        
    }
    
     count++;
     if(count>MOD_CONTROL_COUNT)
     {
          count=0;
     }
    
     if(clearCountersFlag==ENABLED)
     {
     softStartCounter=0;
     softStartFlag=0;
     state=0;
     modulationIndex=0;
     
     softStartSteps=0;
     stopCounter=0;
     reversePolarityFlag=0;
     reversePolCounter=0;
     }
   //    LATBbits.LATB2=1;
IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag
  // LATBbits.LATB2=0;
}

