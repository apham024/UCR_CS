;=================================================
; Name: Annie Pham	
; Email: apham024@ucr.edu
; 
; Assignment name: Assignment 1
; Lab section: 021
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team.
;
;=================================================

;-------------------------------
;PUT TABLE HERE
;--------------------------------
;REG VALUES	R0 R1 R2 R3  R4 R5 R6 R7
;Pre-loop	0  6  12 0   0  0  0  1168
;Iteration 01	0  6  12 12  0  0  0  1168
;Iteration 02	0  5  12 12  0  0  0  1168
;..
;Iteration n	0 n-1 n 12+n 0  0  0  0
;End of program	0  0  12 72  0  0  0  DEC_0
;--------------------------------

.ORIG x3000			; Program begins here
;-------------
;Instructions
;-------------
LD R1, DEC_6
LD R2, DEC_12
LD R3, DEC_0
;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------

DO_WHILE ADD R3, R3, R2
	 ADD R1, R1, #-1
	 BRp DO_WHILE

HALT
;---------------	
;Data
;---------------
DEC_0	.FILL	#0
DEC_6	.FILL	#6
DEC_12	.FILL	#12

;---------------	
;END of PROGRAM
;---------------	
.END


