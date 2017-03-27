;=================================================
; Name: Annie Pham
; Email: apham024@ucr.edu
; 
; Assignment name: Assignment 2
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

;----------------------------------------------
;outputs prompt
;----------------------------------------------	
LEA R0, intro			; 
PUTS				; Invokes BIOS routine to output string

;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------

GETC
OUT
ADD R1, R0, #0 ; adds the value from R0 to R1
LD R0, NEWLINE
OUT

GETC
OUT
ADD R2, R0, #0 ; adds the value from R0 to R2
LD R0, NEWLINE
OUT

ADD R0, R1, #0
OUT

LEA R0, SPACE
PUTS

LD R0, MINUS
OUT

LEA R0, SPACE
PUTS

ADD R0, R2, #0
OUT

LEA R0, SPACE
PUTS

LEA R0, EQUAL
PUTS

ADD R1, R1, #-15 ; convert to actual number
ADD R1, R1, #-15 
ADD R1, R1, #-15 
ADD R1, R1, #-3
ADD R2, R2, #-15
ADD R2, R2, #-15
ADD R2, R2, #-15
ADD R2, R2, #-3

ADD R2, R2, #0
BRz IF_ZERO

LD R0, ASCII ; load R0 with #48
BRp FOR_LOOP
HALT

; if R2 = 0, the sum will just be R1 and skips over subtraction loop
; FIX: X - 0 = X and 0 - 0 = 0

FOR_LOOP ; subtract
	ADD R1, R1, #-1
	ADD R2, R2, #-1
	BRp FOR_LOOP

IF_ZERO
	ADD R7, R7, #0
END_IF_ZERO

ADD R1, R1, #0
BRzp IF_POSITIVE

; FIX: X - X = 0, if sum = 0, skips loop that adds '-'

IF_NEGATIVE
	LD R0, MINUS
	OUT
	NOT R1, R1
	ADD R1, R1, #1
END_IF_NEGATIVE

IF_POSITIVE
	ADD R5, R5, #0						
END_IF_POSITIVE

LD R6, ASCII
NUM_TO_CHAR
	ADD R1, R1, #1
	ADD R6, R6, #-1
	BRp NUM_TO_CHAR
END_NUM_TO_CHAR

ADD R0, R1, #0
OUT

LD R0, NEWLINE
OUT

HALT
;------	
;Data
;------
; String to explain what to input 
intro .STRINGZ	"ENTER two numbers (i.e '0'....'9')\n" 
NEWLINE .STRINGZ "\n"	; String that holds the newline character
ASCII	.FILL	#48
MINUS   .FILL   x2D
EQUAL	.FILL	x3D
SPACE	.FILL	x20


;---------------	
;END of PROGRAM
;---------------	
.END

