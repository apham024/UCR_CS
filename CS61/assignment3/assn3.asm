;=================================================
; Name: Annie Pham	
; Email: apham024@ucr.edu
; 
; Assignment name: Assignment 3
; Lab section: 021
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team.
;
;=================================================

.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------
LD R6, Convert_addr		; R6 <-- Address pointer for Convert
LDR R1, R6, #0			; R1 <-- VARIABLE Convert 

;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------
LD R2, DEC_0 
LD R3, DEC_16
AND R6, R6, R2 ; clears R6
ADD R6, R6, #4
LD R2, BINARY_NUM
BRp IF_LOOP


IF_LOOP
	ADD R3, R3, #0
	BRnz END_PROGRAM
	ADD R6, R6, #0
	BRz PRINT_SPACE
	COME_BACK
	AND R4, R1, R2 
	ADD R0, R4, #0
	BRn TRUE_CONDITION ; if(R3 <= 0)

FALSE_CONDITION
	NOT R4, R4
	ADD R4, R4, #1
	LD R5, DEC_48
	ADD R0, R5, #0 ; adds 48 to get 0 as left most bit (00000....)
	OUT
	ADD R6, R6, #-1

BR END_IF_LOOP

TRUE_CONDITION
	NOT R4, R4
	ADD R4, R4, #1
	LD R5, DEC_49
	ADD R0, R5, #0 ; adds 49 to get 1 as left most bit (10000.....)
	OUT
	ADD R6, R6, #-1

END_IF_LOOP

ADD R1, R1, R1 ; shifts
ADD R3, R3, #-1 ; counter

BRnzp IF_LOOP

;------------

PRINT_SPACE
;	ADD R6, R6, #0
;	BRnz END_PRINT_SPACE ;(if R6 <= 0, break out of loop)
	LD R0, SPACE
	OUT	
	ADD R6, R6, #4
	BR COME_BACK
END_PRINT_SPACE

END_PROGRAM

LD R0, NEWLINE
OUT

HALT
;---------------	
;Data
;---------------
Convert_addr .FILL xD000	; The address of where to find the data
BINARY_NUM .FILL x8000
DEC_48 .FILL #48
DEC_0 .FILL #0
DEC_49 .FILL #49
DEC_16 .FILL #16
SPACE .FILL x20
NEWLINE .FILL xA

.ORIG xD000			; Remote data
Convert .FILL xABCD		; <----!!!NUMBER TO BE CONVERTED TO BINARY!!!
;---------------	
;END of PROGRAM
;---------------	
.END
