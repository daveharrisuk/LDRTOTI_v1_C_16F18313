/**
 @File
   LDRTOTI_v1_C_16F18313.X/header.h  

 @Author
   Dave Harris  MERG #2740 ?2022

 @Description
  LDRTOTI data and function declarations    (included by main.c)

 @History
  
*/
#ifndef HEADER_H
#define	HEADER_H

#include <stdint.h>
#include <stdbool.h>

volatile uint8_t tickCount_TMR0 = 0; // timer ISR (150ms tick count 0-7)

const uint8_t EEadrFLAG = 0;  // EEPROM address for save flag.byte

typedef union // flag 
{
    struct
    {
        uint8_t trip    : 1;    // flag.bits.trip is boolean
        uint8_t UTblock : 1;    // flag.bits.UTblock is boolean
        uint8_t f2      : 1;
        uint8_t f3      : 1;
        uint8_t ICSPc   : 1;    // flag.bits.ICSPc debug signal on PinICSPc
    } bits;
    uint8_t byte;       // flag.byte
} flag_t;

flag_t flag;            // flag.bits.trip or flag.byte


typedef int16_t analogWord_t;

analogWord_t vLDR;      // ADC value from LDR

analogWord_t vThL;      // Lower threshold to go to Tripped state
analogWord_t vThH;      // Upper threshold to got to unTripped state

uint8_t counterL;       // Trip confirm counters
uint8_t counterH;

uint8_t counter2;       // 25ms timer
uint8_t counter3;       // 1 second untrip timer


/*---------------------- function declarations --------------------*/

void timer0_ISR();
void setup(void);
void debugPulse(bool);
analogWord_t measureV(void);
void unTripLoop(void);
void tripLoop(void);
void main(void);


#endif /*----------------------- HEADER_H ------------------------*/
