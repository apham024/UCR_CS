;=================================================
; Name: Annie Pham
; Email: apham024@ucr.edu
; 
; Assignment name: Assignment 4
; Lab section: 021
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team.
;
;=================================================

.ORIG x3000

;-------------------------------
;INSERT CODE STARTING FROM HERE 
;--------------------------------
;Example of how to Output Intro Message
LD R0, introMessage  ;Output Intro Message
PUTS

;Example of how to Output Error Message
;LD R0, errorMessage  ;Output Error Message
;PUTS

JSR SUB_OUTPUT_3200

HALT

;---------------	
;Data
;---------------
introMessage .FILL x6000
;errorMessage .FILL x6100

;------------
;Remote data
;------------
.ORIG x6000
intro .STRINGZ	"Input a positive or negative decimal number (max 5 digits), followed by ENTER\n"

;.ORIG x6100	
;error_mes .STRINGZ	"ERROR INVALID INPUT\n"

; ----------------------------------------------------------------------------
; Subroutine: SUB_OUTPUT_3200
; Input (R0): User input
; Postcondition: Converts string of characters into binary to put into a register
; Return Value: R5 where binary conversion of user input is stored
; ----------------------------------------------------------------------------
.ORIG x3200

; (1) Backup R7 and all registers that this subroutine changes except for Return Values
SUB_OUTPUT_3200		ST R0, BACKUP_R7_3200
			ST R7, BACKUP_R7_3200

; (2) Perform whatever algorithm(s) this subroutine is suppose to perform

BR CONTINUE ; to skip RESET branch
               

RESET ; if there's an error, outputs this message       
	LEA R0, errorMessage
        PUTS
	LEA R0, intro_msg  ;Output Intro Message
	PUTS    


CONTINUE  
              
        AND R1, R1, #0 
	AND R2, R2, #0
	AND R3, R3, #0
	AND R4, R4, #0
	AND R5, R5, #0
	AND R6, R6, #0
                
INPUT_LOOP ; gets user input and checks if '-' or '+' is entered    

	GETC                  
        OUT                   	
                             
        LD R3, MINUS_43 ; for positive sign
        ADD R4, R0, R3 ; 43 - 43 = 0 then it would just ignore the rest 
        BRz INPUT_LOOP ; and loop back up

	AND R3, R3, #0
	AND R4, R4, #0
                
        LD R3, MINUS_45; for negative sign         
        ADD R4, R0, R3 ; 45 - 45 = 0 then it would go to IF_NEG loop
        BRz IF_NEG 
        BR SKIP_LOOP ; if a decimal is entered, ignore and continue


IF_NEG ; if the user entered in '-'

	ADD R1, R1, #1 ; stores '1' for later to indicate negative number
        BR INPUT_LOOP

                
SKIP_LOOP ; checks for newline and non-decimal characters

	LD R2, MINUS_10 ; R2 <- #-10 for when user inputs newline             
        ADD R3, R0, R2	
        BRz END_PROGRAM ; exits on new line

        LD R3, UPPER_CHAR ; if anything entered after 9         
        ADD R4, R0, R3 ; R4 <- R0 + #-58
        BRzp RESET ;if >= 0, reset program
                
	AND R3, R3, #0
        AND R4, R4, #0
                
        LD R3, LOWER_CHAR ; if anything entered before 0
        ADD R4, R0, R3 ;R4 <- R0 + #-47
        BRnz RESET ;if <= 0, reset program
        
	AND R3, R3, #0
	AND R4, R4, #0
        
	LD R3, MINUS_48 ; converts to dec
	ADD R0, R0, R3     
	ADD R5, R5, R0 ; adds all the input entered into R5
                
        LD R4, COUNTER ; to loop through to multiply by 10
        ADD R6, R5, #0 ; to keep track of initial user input

                
TIMES_10_LOOP   

	ADD R5, R5, R6 ; R5 is used to multiply by 10 at this point
        ADD R4, R4, #-1
        BRp TIMES_10_LOOP
	; after multiplying by 10, gets next user input
        BR INPUT_LOOP


END_PROGRAM   
     
        ADD R5, R6, #0 ; stores initial user input from R6 into R5
        ADD R1, R1, #0 ; if R1 holds a '1' from earlier then 
        BRp CONV_TO_NEG ; goes to CONV_TO_NEG to take 2's comp
	ADD R5, R5, #0 ; R5 has 0 if user input only '-'
	BRz RESET ; if 0, when '+' is input, output error
        BR NO_CHANGE


CONV_TO_NEG ; takes 2's comp
	
	ADD R5, R5, #0 ; R5 has 0 if user input only '-'
	BRz RESET ; if 0, when '-' is input, output error
	NOT R5, R5
        ADD R5, R5, #1

 
NO_CHANGE ; officially ends program if not negative
	HALT

LD R0, NEWLINE
OUT

; (3) Restore the registers that you backed up
LD R0, BACKUP_R7_3200
LD R7, BACKUP_R7_3200

; (4) Return to where you came from
RET

;---SUBROUTINE DATA-----
BACKUP_R0_3200	.BLKW #1
BACKUP_R7_3200	.BLKW #1

;--------------
;Local Data
;--------------

COUNTER         .FILL #9
MINUS_48        .FILL #-48
MINUS_10        .FILL #-10
MINUS_45        .FILL #-45
MINUS_43        .FILL #-43
UPPER_CHAR      .FILL #-58
LOWER_CHAR      .FILL #-48   
NEWLINE 	.FILL xA

errorMessage .STRINGZ "\nERROR INVALID INPUT\n"
intro_msg .STRINGZ "Input a positive or negative decimal number (max 5 digits), followed by ENTER\n"

;.ORIG x6100	
;error_mes .STRINGZ	"ERROR INVALID INPUT\n"
       

.END 	
