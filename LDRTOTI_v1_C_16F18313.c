/* File: LDRTOTI_v1_C_16F18313.c
 * ----------------------------------------
 * Author: Dave Harris
 *
 * Port of Julian Coles LDRTOTI ASM (27-May-2022, MPLAB v8.91, PIC12F683)
 * 
 * Rewrite to C for PIC16F18313
 * 
 * Environment...
 *  IDE: MPLAB X v5.50 (ubuntu).  Compiler: XC8 v2.32
 *  MCU: PIC16F18313. HFINTOSC: 16 MHz. FOSC: 8 MHz. VDD: 5.0V
 *  Programming: LVP (MCLR pin is MCLR) using PICKIT 4
 *  PCB: LDRTOTI revA by Dave McCabe (for SOIC8)
 * 
 * PDIP8/SOIC8 pins...
 *  1: Vdd                   8: Vss
 *  2: RA5|output|PinOPTO    7: RA0|input|PinICSPd
 *  3: RA4|analog|PinLDR     6: RA1|input|PinICSPd
 *  4: RA3|MCLR|PinMCLR      5: RA2|output|PinLED
 * 
 * 
 * Created: 1-Jun-20222
 */

#include "LDRTOTI_v1_C_16F18313.h"

#include "mcc_generated_files/mcc.h"


void unTripLoop(void)
{
  bool unTripFlag = false;
  
  do
  {
        
  } while( unTripFlag == false );
  
}

/*-----------------------setup()-----------------------------------*/
void setup(void)
{
    ADC_Initialize();
    ADC_SelectChannel( PinLDR );
    
    
}


/*-----------------------loop()-----------------------------------*/
void loop(void) 
{
    
}


/*-----------------------main()-----------------------------------*/
void main() 
{
    setup(); // configure device and variables
    
    while( 1 ) 
    {
        loop(); // forever
    }
    // no exit
}


//--------------eof LDRTOTI_v1_C_16F18313.c ---------------
