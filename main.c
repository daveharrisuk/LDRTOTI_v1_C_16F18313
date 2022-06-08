/**
@File
   main.c

@Description
   A port of Julian Coles LDRTOTI ASM (27-May-2022, MPLAB v8.91, PIC12F683).
   Rewrite to C for use on the PIC16F1xxx and LDRTOTI revA PCB.

@Repo
   https://github.com/daveharrisuk/LDRTOTI_v1_C_16F18313

@Author
    Dave Harris   MERG #2740    �2022

@License
  under Creative Commons Attribution-NonCommercial-ShareAlike license.
   https://creativecommons.org/licenses/by-nc-sa/3.0/

@Environment
   IDE         MPLAB X v5.50  Use MCC for device code configuration.
   Compiler    XC8 v2.32 (Free license)   C90 
   MCU         PIC16F18313 
   FOSC        16 MHz   HFINTOSC 16 MHz
   Programming LVP (MCLR pin is MCLR) using PICKIT 4
   PCB         LDRTOTI revA (by Dave McCabe for SMD PCB project)
   MCU pins  SOIC8
    +---------------------__----------------------+
    1 VDD|power5|noSymbol     VSS|power0|noSymbol 8
    2 RA5|output|PinOPTO       RA0|input|PinICSPd 7
    3 RA4|analog|PinLDR        RA1|input|PinICSPc 6 (debug sets this output)
    4 RA3|LVP_MCLR|noSymbol     RA2|output|PinLED 5
    +---------------------------------------------+
   Memory
    Program space        used   29Fh (   671) of   800h words   ( 32.8%)
    Data space           used    1Eh (    30) of   100h bytes   ( 11.7%)

@History
   1-Jun-2022 Created
*/

#include "header.h"

#include "mcc_generated_files/mcc.h"
/* files generated by MCC (.c and .h)...
    mcc, device_config, pin_manager, adc, memory & interrupt_manager
*/


/* mask warnings from MCC_generated files */
#pragma warning disable 520  //"function x is never called"
#pragma warning disable 1498 //"pointer(x) has no target"
  // the following warning disable wont disable!  Its an XC8 bug.
#pragma warning disable 1020 //"unknown attribute x in chipinfo"



/*---------------------------- timer0_ISR() ----------------------------
 Interrupt Service Routine called every 125 ms from MCC code, from TMR0
 LED is dual function, heartbeat flash and trip flag indicator
*/
void timer0_ISR()
{
    switch( tickCount_TMR0++ )
    {
        case 0:
            PinLED_SetHigh(); // heart beat flash
            break;

        case 1: // and 2-6
            if( flag.bits.trip == 1 )
                PinLED_SetHigh(); // lit if trip is true
            else
                PinLED_SetLow(); // un lit if trip is false
            break;

        case 7:
            tickCount_TMR0 = 0; // reset count
            PinLED_SetLow();    // flash pause
            break;

        default: // tick count 2-6, do nothing
            break;
    };
}


/*----------------------------- setup() ---------------------------------
   called from main()
*/
void setup()
{
    SYSTEM_Initialize();
    
    ADC_Initialize();
    ADC_SelectChannel(PinLDR);

    TMR0_SetInterruptHandler(timer0_ISR);   //Register the interrupt Handler

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    counterL = 25;
    counterH = 25;
    counter2 = 32;
    counter3 = 40;
}


/*------------------------- measureV() ----------------------------------
  return 8 bit ADC reading from a 10 bit ADC conversion
*/
analogWord_t measureV()
{
   return  ADC_GetConversion(PinLDR) >> 2;
}


const uint8_t ICSPcDEBUG = 1;
/*------------------------ debugPulse() ---------------------------------
 set pin ICSPc high or low as debug signal
*/
void debugPulse(bool level)
{
    if( ICSPcDEBUG == 1 )
    {
        PinICSPc_SetDigitalOutput();
        if( level == 1 )
            PinICSPc_SetHigh();
        else
            PinICSPc_SetLow();
    }
}


/*------------------------- unTripLoop() --------------------------------
  unTrip loops until return statement 
*/
void unTripLoops()
{    
    vThL = measureV() +75;
    
    unTripLoop1:  // loop until return

        vLDR = measureV();
  
            //vThLtemp = vL +75; // not needed
    //UT
        if( vLDR > vThL ) // trip?
        {
            if( --counterL != 0 ) goto unTripLoop1; // not yet
    // UTY
            counterL = 4;
            return;         // exit unTripLoop and go back to main
        }
    //UTN
        debugPulse(1);
            __delay_us(765);
        debugPulse(0);
        
        if( --counter2 > 0 ) goto unTripLoop1; // 25 ms? not yet

        counter2 = 32;  // reset
        
        if( flag.bits.UTblock == 1 )
        {
            if( --counter3 <= 0 )
            {
                counter3 = 40;  // reset
                
                flag.bits.UTblock = 0;
                PinOPTO_SetLow();
            }
        }
        
        debugPulse(1);        
            if( ( vLDR +75 ) > vThL )  // ambient light tracking
                     vThL++;       // up
            else
                     vThL--;       // down
        debugPulse(0);
        
    goto unTripLoop1;   
    
} // end unTripLoop()


/*-------------------------- tripLoop() -----------------------------------
  Trip loops until return statement 
*/
void tripLoops() 
{
 
    tripLoop1:
        debugPulse(1);
            __delay_ms(10);
        debugPulse(0);
     
        PinOPTO_SetHigh();

    tripLoop1a:
    
        vLDR = measureV();
        vThH = vLDR - 60;
        
        if( vLDR < vThH )
        {
        //TY
            if( --counterH != 0 ) goto tripLoop1; // not yet
            counterH = 4;
            
            return;
        }
    //TN
        debugPulse(1); 
        __delay_us(765);
        debugPulse(0);
        
        if( counter2 != 0 ) goto tripLoop1a;
        counter2 = 32;
        
        debugPulse(1);
            if( (vLDR - 60) > vThH ) // ambient light tracking
                vThH++;
            else
                vThH--;
        debugPulse(0);
        
    goto tripLoop1a;
    
} // end tripLoop())


/*---------------------------- main() -----------------------------------
*/
void main() 
{
    setup();
    
    flag.byte = DATAEE_ReadByte(EEadrFLAG);

    if( flag.bits.trip == 1 )
    {
        vThH = 40;
        goto trip;
    }
    
    unTrip:
    
        unTripLoops();
    
        flag.bits.trip = 1;
        
        DATAEE_WriteByte(EEadrFLAG, flag.byte);
        __delay_ms(10);
            
        vLDR = measureV();
        vThH = vLDR - 60;
        
     trip:
    
        tripLoops();
     
        flag.bits.trip = 0;
        
        DATAEE_WriteByte(EEadrFLAG, flag.byte);

        flag.bits.UTblock = 1;
            
        __delay_ms(10);
        
    goto unTrip;
}


/*--------------------- EoF main.c ----------------------------------*/
