;*******************************************************************
;    Filename:     MERG_LDR_TOTI_V1_683.asm
;    Date:         12 May 2022 27 May

;Simple LDR TOTI using ambient light cut-off
;Two states: untripped, tripped; tripstate stored in EEPROM
;Loco LDR resistance increase, voltage up to VH
;Loco gone, light increases, LDR resistance decreases, V down to VL
;VTHL and VTHH are incremented at 25ms per bit
;VTHL = VL + 75 (1.5V)
;VTHH = VH - 60 (1.2V)
;Programme loops 800us
;Untrip delay 1 second (to avoid wagon gaps)
; Counter 3 holds the delay value in 25ms bits
; 40 = 1 second
;ADC input AN3 (GP4)
 
     LIST      P=12F683              ; list directive to define processor
     #INCLUDE <P12F683.INC>          ; processor specific variable definitions

;------------------------------------------------------------------------------------
    __CONFIG   _FCMEN_ON & _IESO_OFF & _CP_OFF & _CPD_ON & _BOD_OFF & _MCLRE_OFF & _WDT_OFF & _PWRTE_ON & _INTRC_OSC_NOCLKOUT 
;8MHz clock
;------------------------------------------------------------------------------
; EEPROM INITIALIZATION
; The 12F683 has 256 bytes of non-volatile EEPROM, starting at address 0x2100
;------------------------------------------------------------------------------

       ERRORLEVEL -302    ; Suppress bank notification
       
;--------------------------------------------------------------------------
RESET_VECTOR  CODE    0x0000  ; processor reset vector

		goto	start
MAIN_PROG     CODE

Flag	EQU		0x21
VL		EQU		0x22 		;ADC voltage for no loco	
VH	 	EQU		0x23		;ADC voltage for loco
VTHL	EQU		0x24		;Lower threshold to go to Tripped state
VTHH	EQU		0x25		;Upper threshold to got to Untripped state
CounterL EQU	0x26		;Trip confirm counters
CounterH EQU	0x27
Temp	EQU		0x28
Delay1	EQU		0x29
Delay2	EQU		0x2A
Counter	EQU		0x2B
Counter2 EQU	0x2C        ;25ms timer
VTHLtemp EQU	0x2D
VTHHtemp EQU	0x2E
Counter3 EQU    0x2F        ;1 second untrip timer
;*********************************************************************	
	#define	Output	    GPIO,5 
	#define	Tripstate	Flag,1	    ;1 = tripped
	#define	LED		    GPIO,2	
    #define UTblockflag Flag,2
;**********************************************************************
;subroutines
init	bsf	    STATUS,RP0 	; set file register bank to 1 

		clrf	GPIO		;as per data sheet

		movlw	b'011011'	;GP4 ADC i/p, GP5 Output, GP2 LED
		movwf	TRISIO		;

        movlw   b'10100000' ;GIE bit 7, TOIE bit 5
		movwf	INTCON		;
		
 		movlw	b'01110111' ;8MHz,int osc
		movwf	OSCCON
 
 		movlw	b'10000000'
		movwf	OPTION_REG
		clrf	PIE1
		
 		clrf	IOC
 		clrf	VRCON
		
		movlw	b'00110000'	;PWM off
		movwf	CCP1CON
		
		movlw	b'00000000'	;PUs off	
		movwf	WPU

		movlw	b'01011000'	;f/16 ADC clock, ADC input AN3/GP4
		movwf	ANSEL
  
        BCF     STATUS,RP0  ; set file register bank to 0
	
		clrf	CMCON0
		clrf	T1CON

		movlw	b'00001101'	;Left justify, VDD ref, AN3/GP4 input, ADC on
		movwf	ADCON0

		return
;====================================================		
;SUBROUTINES
;====================================================	
;10ms timer
Timer	clrf	Delay1		
		movlw	D'26'
		movwf	Delay2	

Loop4	decfsz	Delay1,f	;382us
		goto	Loop4
		decfsz	Delay2,f	;26 X 382µS = 10mS
		goto 	Loop4
		return
;--------------------------------------------------------		
;200ms timer
Timer1	clrf	Delay1		
		clrf	Delay2	

Loop5	nop
		nop
		nop
		decfsz	Delay1,f	;768us
		goto	Loop5
		decfsz	Delay2,f	;256 X 768µS = 200mS
		goto 	Loop5
		return				
;--------------------------------------------------------	
;Timer 2 programme loop time 765us (800us in total)
Timer2	clrf	Delay1
		movlw	d'2'
		movwf	Delay2

Loop6	decfsz	Delay1,f	;1.5us loop x 255 = 382us
		goto	Loop6
		
		decfsz	Delay2,f	;2 x 382us = 765us
		goto 	Loop6
		return		
;----------------------------------------------------------
;ADC measurement
MeasureV
		bsf		ADCON0,1	;Start ADC
Loop	btfsc	ADCON0,1	;Finished?
		goto	Loop
		movfw	ADRESH
		movwf	Temp
		return				;Result in Temp
;------------------------------------------------------
Storeflag
		movfw	Flag	    ;load Flag to w reg
		bsf		STATUS,RP0	;bank 1
		movwf	EEDATA		;into EEDATA
;load write address 1
		clrf	EEADR		;Address 0
;write to EEPROM after 'safe combination'
		bsf		EECON1,2	;write enable
		movlw	55h
		movwf	EECON2
		movlw	0xAA
		movwf	EECON2
		bsf		EECON1,1	;start write operation
;check for completion
EELoop2	btfsc	EECON1,1	;write finished?
		goto	EELoop2		;no, so loop
		bcf		STATUS,RP0	;back to bank 0	
		return		
;**********************************************************
;START OF PROGRAMME
start	call	init
		bcf		Output		;Output off at start
		bsf		LED
		call 	Timer1      ;200ms settling delay
		bcf		LED
;		movlw	d'4'		;Load Counters for repeat trips needed
		movlw	d'25'		;TEST
		movwf	CounterL
		movwf	CounterH
        movlw   d'32'
        movwf   Counter2    ;Threshold update timer
        movlw   d'40'
        movwf   Counter3    ;1 second delay counter
;...........................................			
;start by reading the eeprom
;address 0 = Flag
		bsf		STATUS,RP0	;select bank 1
		clrf	EEADR		;select address 0
		bsf		EECON1,0	;start read
		movfw	EEDATA		;read data		
		bcf		STATUS,RP0	;back to bank 0	
		movwf	Flag		;Restore State flag	
;-------------------------------------------------------------
;Route to trip or untrip depending on flag
		btfss	Tripstate	;1 = tripped
		goto	Untriploop
		goto	Triploop
;------------------------------------------------------------
;Quiescent loop
Untriploop
		call	MeasureV	;Result in Temp
		movfw	Temp
		movwf	VL
			
;Create VTHL = VL +75	
		movlw	d'75'							
		addwf	VL,w
		movwf	VTHL
;.......................................................
Untriploop1	
		call	MeasureV	;Result in Temp 
		movfw	Temp
		movwf	VL	
				
		movlw	d'75'		;Add 75 to VL create VTHLtemp
		addwf	VL,w
		movwf	VTHLtemp	;New VTHL as VTHLtemp
		
;Check if VH > VTHL, which would indicate a loco
UT		movfw	VTHL		;VTHL in w register
		subwf	VL,w		;subtract VTHL from VL
		btfss	STATUS,C	;C = 1 if VL > VTHH (ie a trip)
				
		goto	UTN
		goto	UTY			;Tripped
;...............................................................
UTN		Call	Timer2		;765us delay - 800us total
  
;Increment VTHL if VTHLtemp > VTHL every 32 loops x 765us = 25ms
							;1 volt - 100 steps, takes 2.5 sec
;UTblock counts 40 x 25ms = 1s

		decfsz	Counter2,f
		goto	Untriploop1	;Not yet

        movlw   d'32'       ;Reload Counter 2
        movwf   Counter2
        
;Every 25ms:
        btfss   UTblockflag ;1 = block
        goto    Incdec

        decfsz  Counter3,f    ;40 x 25ms = 1s
        goto    Incdec
        
        bcf     Output      ;Output off after 1s delay
        bcf     UTblockflag ;Clear UTblockflag
        
;Inc/dec routine
Incdec	movfw	VTHL		;VTHL in w register
		subwf	VTHLtemp,w	;subtract VTHL from VTHLtemp
		btfss	STATUS,C	;C = 1 if VTHLtemp > VVTHL (ie VL has gone up)
		
		goto	Down
		goto	Up

Down	decf	VTHL,f		;VTHL going down, so decrement VTHL
		goto	Untriploop1
		
Up		incf	VTHL,f 	    ;VTHL going up so increment VTHL	
		goto	Untriploop1
;..............................................................			
UTY							;Tripped
;Check the condition 4x	
		decfsz	CounterL,f
		goto	Untriploop1	;Not yet
		movlw	d'4'   		;Reload CounterL
		movwf	CounterL
;4 trips
		bsf		Tripstate	;Tripped so flag set to '1'
		call	Storeflag
		call	Timer		;10ms delay before next actions	
;================================================================
;Set VTHH = VH - 60
		call	MeasureV	;Result in Temp
		movfw	Temp
		movwf	VH	
		
;Subtract 60 from VH to create VTHH
		movlw	d'60'
		subwf	VH,w		;Subtract 60 from VH
		movwf	VTHH        ;Create VTHH
		goto	Triploop1
;.......................		
Triploop					;From start up
		movlw	d'40'
		movwf	VTHH		;VTHH = 40 at start up

Triploop1
		bsf		Output
		bsf		LED		
		call	Timer		;10ms avoid start up transient
;....................................		
Triploop1a
		call	MeasureV	;Result in Temp
		movfw	Temp
		movwf	VH	

;Subtract 60 from VH to create VTHHtemp
		movlw	d'60'
		subwf	VH,w		
		movwf	VTHHtemp
				
;TT		
;Check if VH < VTHH, which would indicate no loco
CVH		movfw	VTHH		;VTHH into w register
		subwf	VH,w		;subtract 
		btfss	STATUS,C	;C = 1 if Temp > VTHH ie no trip
		
		goto	TY
		goto	TN
;..............................................................		
TN		Call	Timer2		;800us delay
;Increment VTHH if VTHHtemp > VTHH every 32 loops - 25ms
		movfw	Counter2
		decfsz	Counter2,f
		goto	Triploop1a	;Not yet
  
        movlw   d'32'       ;Reload Counter 2
        movwf   Counter2
		
		movfw	VTHH		;VTHH in w register
		subwf	VTHHtemp,w	;subtract VTHH from VTHHtemp
		btfss	STATUS,C	;C = 1 if VTHHtemp > VTHH (ie VH has gone up)
		
		goto	Down2
		goto	Up2

Down2	decf	VTHH,f		;VH going down, so decrement VTHH
		goto	Triploop1a
		
Up2		incf	VTHH,f	    ;VH going up so increment VTHH	
		goto	Triploop1a
;..............................				
TY							;Back to untripped
;Check the condition 4x
		decfsz	CounterH,f
		goto	Triploop1	;Not yet
		movlw	d'4'   		;Reload CounterH
;		movlw	d'25'		;TEST
		movwf	CounterH
;4 trips
		bcf		Tripstate	;Untripped so flag set to '0'
        
;Output delayed 1 second
		bcf		LED         ;LED cleared immediately, output after 1s delay.
		
		call	Storeflag
			
        bsf     UTblockflag
        
        movlw   d'40'       ;Load Untrip block timer: 40 x 25ms =1s
        movwf   Counter3
  
  
		call	Timer		;10ms delay
		goto	Untriploop
;==============================================================
		end
;--------------------------------------------------------------
