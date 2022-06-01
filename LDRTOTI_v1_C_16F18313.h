/* File: LDRTOTI_v1_C_16F18313.h  
 *----------------------------------
 * Author: Dave Harris
 * Comments:
 * Revision history: 
 */
 
#ifndef LDRTOTI_v1_C_16F18313_H
#define	LDRTOTI_v1_C_16F18313_H

#include <stdint.h>


const uint8_t Flag = 0x21;
const uint8_t VL	 = 0x22; 	// ADC voltage for no loco	
const uint8_t VH	 = 0x23;		// ADC voltage for loco
const uint8_t VTHL = 0x24;		// Lower threshold to go to Tripped state
const uint8_t VTHH	 = 0x25; //Upper threshold to got to Untripped state
const uint8_t CounterL = 0x26; //Trip confirm counters
const uint8_t CounterH = 0x27;
const uint8_t Temp	 = 0x28;
const uint8_t Delay1	 = 0x29;
const uint8_t Delay2	 = 0x2A;
const uint8_t Counter	 = 0x2B;
const uint8_t Counter2 = 0x2C; //25ms timer
const uint8_t VTHLtemp = 0x2D;
const uint8_t VTHHtemp = 0x2E;
const uint8_t Counter3 = 0x2F; //1 second untrip timer


#endif	/* LDRTOTI_v1_C_16F18313_H */
