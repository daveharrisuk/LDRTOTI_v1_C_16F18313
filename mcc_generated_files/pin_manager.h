/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18313
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set PinICSPd aliases
#define PinICSPd_TRIS                 TRISAbits.TRISA0
#define PinICSPd_LAT                  LATAbits.LATA0
#define PinICSPd_PORT                 PORTAbits.RA0
#define PinICSPd_WPU                  WPUAbits.WPUA0
#define PinICSPd_OD                   ODCONAbits.ODCA0
#define PinICSPd_ANS                  ANSELAbits.ANSA0
#define PinICSPd_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define PinICSPd_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define PinICSPd_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define PinICSPd_GetValue()           PORTAbits.RA0
#define PinICSPd_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define PinICSPd_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define PinICSPd_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define PinICSPd_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define PinICSPd_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define PinICSPd_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define PinICSPd_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define PinICSPd_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set PinICSPc aliases
#define PinICSPc_TRIS                 TRISAbits.TRISA1
#define PinICSPc_LAT                  LATAbits.LATA1
#define PinICSPc_PORT                 PORTAbits.RA1
#define PinICSPc_WPU                  WPUAbits.WPUA1
#define PinICSPc_OD                   ODCONAbits.ODCA1
#define PinICSPc_ANS                  ANSELAbits.ANSA1
#define PinICSPc_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define PinICSPc_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define PinICSPc_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define PinICSPc_GetValue()           PORTAbits.RA1
#define PinICSPc_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define PinICSPc_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define PinICSPc_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define PinICSPc_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define PinICSPc_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define PinICSPc_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define PinICSPc_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define PinICSPc_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set PinLED aliases
#define PinLED_TRIS                 TRISAbits.TRISA2
#define PinLED_LAT                  LATAbits.LATA2
#define PinLED_PORT                 PORTAbits.RA2
#define PinLED_WPU                  WPUAbits.WPUA2
#define PinLED_OD                   ODCONAbits.ODCA2
#define PinLED_ANS                  ANSELAbits.ANSA2
#define PinLED_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define PinLED_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define PinLED_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define PinLED_GetValue()           PORTAbits.RA2
#define PinLED_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define PinLED_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define PinLED_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define PinLED_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define PinLED_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define PinLED_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define PinLED_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define PinLED_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set PinLDR aliases
#define PinLDR_TRIS                 TRISAbits.TRISA4
#define PinLDR_LAT                  LATAbits.LATA4
#define PinLDR_PORT                 PORTAbits.RA4
#define PinLDR_WPU                  WPUAbits.WPUA4
#define PinLDR_OD                   ODCONAbits.ODCA4
#define PinLDR_ANS                  ANSELAbits.ANSA4
#define PinLDR_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define PinLDR_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define PinLDR_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define PinLDR_GetValue()           PORTAbits.RA4
#define PinLDR_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define PinLDR_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define PinLDR_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define PinLDR_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define PinLDR_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define PinLDR_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define PinLDR_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define PinLDR_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set PinOPTO aliases
#define PinOPTO_TRIS                 TRISAbits.TRISA5
#define PinOPTO_LAT                  LATAbits.LATA5
#define PinOPTO_PORT                 PORTAbits.RA5
#define PinOPTO_WPU                  WPUAbits.WPUA5
#define PinOPTO_OD                   ODCONAbits.ODCA5
#define PinOPTO_ANS                  ANSELAbits.ANSA5
#define PinOPTO_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define PinOPTO_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define PinOPTO_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define PinOPTO_GetValue()           PORTAbits.RA5
#define PinOPTO_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define PinOPTO_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define PinOPTO_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define PinOPTO_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define PinOPTO_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define PinOPTO_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define PinOPTO_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define PinOPTO_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/