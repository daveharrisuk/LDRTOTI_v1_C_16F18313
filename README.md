# LDRTOTI_v1_C_16F18313

A port of Julian Coles LDRTOTI ASM (27-May-2022, MPLAB v8.91, PIC12F683)
Rewrite to C for use on the PIC16F1xxx
   
Firmware for MERG LDRTOTI SMD PCB

   IDE          MPLAB X v5.50 (ubuntu) {device configuration is done in MCC}
   Compiler     XC8 v2.32
   C-Standard   C90
   MCU          PIC16F18313 
   FOSC         16 MHz   HFINTOSC 16 MHz
   Programming  LVP (MCLR pin is MCLR) using PICKIT 4
   PCB          LDRTOTI revA (by Dave McCabe for SOIC8 chip)
   Target pins  SOIC8
    +----------------------_-----------------------+
    1 VDD|power|5.0V                  VSS|power|0V 8
    2 RA5|output|PinOPTO        RA0|input|PinICSPd 7
    3 RA4|analog|PinLDR         RA1|input|PinICSPc 6
    4 RA3|LVP_MCLR|PinMCLR       RA2|output|PinLED 5
    +----------------------------------------------+
