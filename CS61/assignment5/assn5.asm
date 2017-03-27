;=================================================
; Name: Annie Pham
; Email: apham024@ucr.edu
; 
; Assignment name: Assignment 5
; Lab section: 021
; 
; I hereby certify that I have not received assistance on this assignment,
; or used code, from ANY outside source other than the instruction team.
;
;=================================================

.orig x3000			; Program begins here
;-------------
;Instructions
;-------------
;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------
RESTART_MAIN
	LD R0, SUB_MENU
	JSRR R0
	ADD R1, R1, #-1
	BRz ALL_BUSY
	ADD R1, R1, #-1
	BRz ALL_FREE
	ADD R1, R1, #-1
	BRz NUM_BUSY_MACHINES
	ADD R1, R1, #-1
	BRz NUM_FREE_MACHINES
	ADD R1, R1, #-1
	BRz MACHINE_STATUS
	ADD R1, R1, #-1
	BRz FIRST_FREE
	ADD R1, R1, #-1
	BRz QUIT_PROGRAM
	BR RESTART_MAIN

ALL_BUSY
	LD R0, OPTION_1
	JSRR R0
	BR RESTART_MAIN

ALL_FREE
	LD R0, OPTION_2
	JSRR R0
	BR RESTART_MAIN

NUM_BUSY_MACHINES
	LD R0, OPTION_3
	JSRR R0
	BR RESTART_MAIN

NUM_FREE_MACHINES
	LD R0, OPTION_4
	JSRR R0
	BR RESTART_MAIN

MACHINE_STATUS
	LD R0, OPTION_5
	JSRR R0
	BR RESTART_MAIN

FIRST_FREE
	LD R0, OPTION_6
	JSRR R0
	BR RESTART_MAIN

QUIT_PROGRAM
	LD R0, OPTION_7
	JSRR R0

	LEA R0, Goodbye
	PUTS
	
	BR END_MAIN

END_MAIN


HALT
;---------------	
;Data
;---------------
Goodbye .Stringz "\nGoodbye!\n"
SUB_MENU .FILL x3200
OPTION_1 .FILL x3400
OPTION_2 .FILL x3600
OPTION_3 .FILL x3800
OPTION_4 .FILL x4000
OPTION_5 .FILL x4200
OPTION_6 .FILL x4400
OPTION_7 .FILL x5200

;**********************
;* The Busyness Server *
;**********************
;1. Check to see whether all machines are busy
;2. Check to see whether all machines are free
;3. Report the number of busy machines
;4. Report the number of free machines
;5. Report the status of machine n
;6. Report the number of the first available machine
;7. Quit





;-----------------------------------------------------------------------------------------------------------------
; Subroutine: MENU
; Inputs: None
; Postcondition: The subroutine has printed out a menu with numerical options, allowed the
;                          user to select an option, and returned the selected option.
; Return Value (R1): The option selected:  #1, #2, #3, #4, #5, #6 or #7
; no other return value is possible
;-----------------------------------------------------------------------------------------------------------------
.orig x3200
;-------------------------------
;INSERT CODE For Subroutine MENU
;--------------------------------


ST R0, R0_BACKUP_3200
ST R7, R7_BACKUP_3200

BR SKIP

ERROR
	LEA R0, Error_message_1
	PUTS
	
SKIP
LD R1, Menu_string_addr

LOOP_3200
	LDR R0, R1, #0 ; takes value from pointer and loads it
	ADD R0, R0, #0 ; to avoid null character before user input
	BRz FINISH_3200 
	OUT ; outputs each character 
	ADD R1, R1, #1
	ADD R0, R0, #0
	BRnp LOOP_3200 ; if 0, which means end of menu, end this loop

FINISH_3200
	
	GETC
	OUT

	LD R2, UPPER_CHAR_1 ; if anything entered above 7
	ADD R3, R0, R2
	BRzp ERROR
              
	AND R2, R2, #0
	AND R3, R3, #0

	LD R2, LOWER_CHAR_1 ; if anything entered before 1
	ADD R3, R0, R2
	BRnz ERROR

	; end it when it hits newline 
	; when it hits newline it goes back up to LOOP_3200 one more time 
	; then puts 0 into R0, which you DON'T WANT


	ADD R1, R0, #0
	LD R0, CONV_TO_DEC_3200
	;returns number picked in R1
	ADD R1, R1, R0


LD R0, R0_BACKUP_3200
LD R7, R7_BACKUP_3200

RET

HALT


;Subroutine Data
R0_BACKUP_3200 .BLKW #1
R7_BACKUP_3200 .BLKW #1

;Data

CONV_TO_DEC_3200 .FILL #-48
Error_message_1 .STRINGZ "\nINVALID INPUT\n"
Menu_string_addr .FILL x6000

LOWER_CHAR_1 .FILL #-48 ; for anything entered before 1
UPPER_CHAR_1 .FILL #-56 ; for anything entered after 7

.orig x6000
MENUSTRING .STRINGZ "**********************\n* The Busyness Server *\n**********************\n1. Check to see whether all machines are busy\n2. Check to see whether all machines are free\n3. Report the number of busy machines\n4. Report the number of free machines\n5. Report the status of machine n\n6. Report the number of the first available machine\n7. Quit\n"



;-----------------------------------------------------------------------------------------------------------------
; Subroutine: ALL_MACHINES_BUSY
; Inputs: None
; Postcondition: The subroutine has returned a value indicating whether all machines are busy
; Return value (R2): 1 if all machines are busy,    0 otherwise
;-----------------------------------------------------------------------------------------------------------------
.orig x3400
;-------------------------------
;INSERT CODE For Subroutine ALL_MACHINES_BUSY
;--------------------------------

ST R0, R0_BACKUP_3400
ST R7, R7_BACKUP_3400

	LD R0, BUSYNESS_ADDR_ALL_MACHINES_BUSY
	LDR R0, R0, #0
	BRz BUSY_3400
	LEA R0, ALLNOTBUSY
	PUTS
	AND R2,R2,#0
	BR NOTBUSY_3400

BUSY_3400
  	AND R2, R2, #0
  	ADD R2, R2, #1 
  	LEA R0, ALLBUSY
  	PUTS

NOTBUSY_3400

LD R0,R0_BACKUP_3400
LD R7,R7_BACKUP_3400

RET

;Subroutine Data

R0_BACKUP_3400 .BLKW #1
R7_BACKUP_3400 .BLKW #1

;Local Data

ALLBUSY .Stringz "\nAll machines are busy\n"
ALLNOTBUSY .Stringz "\nNot all machines are busy\n"


;--------------------------------
;Data for subroutine ALL_MACHINES_BUSY
;--------------------------------
BUSYNESS_ADDR_ALL_MACHINES_BUSY .Fill xD000




;-----------------------------------------------------------------------------------------------------------------
; Subroutine: ALL_MACHINES_FREE
; Inputs: None
; Postcondition: The subroutine has returned a value indicating whether all machines are free
; Return value (R2): 1 if all machines are free,    0 otherwise
;-----------------------------------------------------------------------------------------------------------------
.orig x3600
;-------------------------------
;INSERT CODE For Subroutine ALL_MACHINES_FREE
;--------------------------------

ST R0, R0_BACKUP_3600
ST R7, R7_BACKUP_3600

LD R0, BUSYNESS_ADDR_ALL_MACHINES_FREE
LDR R0, R0, #0
ADD R0, R0, #1
BRz FREE_3600

LEA R0, NOTFREE
PUTS

AND R2, R2, #0
BR NOTFREE_3600

FREE_3600
	AND R2, R2, #0
	ADD R2, R2, #1
	LEA R0, FREE
	PUTS

NOTFREE_3600

LD R0, R0_BACKUP_3600
LD R7, R7_BACKUP_3600

RET

HALT

;Subroutine Data

R0_BACKUP_3600 .BLKW #1
R7_BACKUP_3600 .BLKW #1

;Local Data

FREE .STRINGZ "\nAll machines are free\n"
NOTFREE .STRINGZ "\nNot all machines are free\n"

;--------------------------------
;Data for subroutine ALL_MACHINES_FREE
;--------------------------------
BUSYNESS_ADDR_ALL_MACHINES_FREE .Fill xD000




;-----------------------------------------------------------------------------------------------------------------
; Subroutine: NUM_BUSY_MACHINES
; Inputs: None
; Postcondition: The subroutine has returned the number of busy machines.
; Return Value (R2): The number of machines that are busy
;-----------------------------------------------------------------------------------------------------------------
.orig x3800
;-------------------------------
;INSERT CODE For Subroutine NUM_BUSY_MACHINES
;--------------------------------
ST R0, R0_BACKUP_3800
ST R7, R7_BACKUP_3800

AND R5, R5, #0
ADD R5, R5, #1
LD R0, PTR_NUM_FREE_MACHINES
JSRR R0

;fill reg with 16
AND R0, R0, #0
ADD R0, R0, #12
ADD R0, R0, #4

;flip what's currently in R2
NOT R2, R2
ADD R2, R2, #1
;16 - what was in R2 = num busy
ADD R2, R2, R0

ADD R6, R2, #0
LEA R0, BUSYMACHINE1
PUTS

LD R0, PTR_PRINT_NUM_3800
JSRR R0

LEA R0, BUSYMACHINE2
PUTS

LD R0, R0_BACKUP_3800
LD R7, R7_BACKUP_3800

RET

HALT

;Subroutine Data

R0_BACKUP_3800 .BLKW #1
R7_BACKUP_3800 .BLKW #1

;Local Data


PTR_NUM_FREE_MACHINES .FILL x4000
PTR_PRINT_NUM_3800 .FILL x4800
BUSYMACHINE1 .STRINGZ "\nThere are "
BUSYMACHINE2 .STRINGZ " busy machines\n"

;--------------------------------
;Data for subroutine NUM_BUSY_MACHINES
;--------------------------------
BUSYNESS_ADDR_NUM_BUSY_MACHINES .Fill xD000


;-----------------------------------------------------------------------------------------------------------------
; Subroutine: NUM_FREE_MACHINES
; Inputs: None
; Postcondition: The subroutine has returned the number of free machines
; Return Value (R2): The number of machines that are free 
;-----------------------------------------------------------------------------------------------------------------
.orig x4000
;-------------------------------
;INSERT CODE For Subroutine NUM_FREE_MACHINES
;--------------------------------
ST R0, R0_BACKUP_4000
ST R7, R7_BACKUP_4000

LD R0, BUSYNESS_ADDR_NUM_FREE_MACHINES
LDR R0, R0, #0
;bit set to 1 and will iterate through each
AND R1, R1, #0
ADD R1, R1, #1

;bit counter
AND R2, R2, #0

;loop coounter
;adds 16 instead of label cause whatever
AND R3, R3, #0
ADD R3, R3, #12
ADD R3, R3, #4

FOREACH_BIT_4000
  	AND R4, R0, R1
  	BRz NO_COUNT_4000
  	ADD R2, R2, #1
  	NO_COUNT_4000
  	ADD R1, R1, R1
  	ADD R3, R3, #-1
  	BRnp FOREACH_BIT_4000

END_4000
  
  	ADD R6, R2, #0

	ADD R5, R5, #-1
	BRz SKIP_PRINT_4000

LEA R0,FREEMACHINE1
PUTS

LD R0,PTR_PRINT_NUM_4000
JSRR R0

LEA R0,FREEMACHINE2
PUTS

SKIP_PRINT_4000

LD R0, R0_BACKUP_4000
LD R7, R7_BACKUP_4000

RET

HALT

;Subroutine Data

R0_BACKUP_4000 .BLKW #1
R7_BACKUP_4000 .BLKW #1

;Local Data

PTR_PRINT_NUM_4000 .FILL x4800
FREEMACHINE1 .STRINGZ "\nThere are "
FREEMACHINE2 .STRINGZ " free machines\n"

;--------------------------------
;Data for subroutine NUM_FREE_MACHINES
;--------------------------------
BUSYNESS_ADDR_NUM_FREE_MACHINES .Fill xD000





;-----------------------------------------------------------------------------------------------------------------
; Subroutine: MACHINE_STATUS
; Input (R1): Which machine to check
; Postcondition: The subroutine has returned a value indicating whether the machine indicated
;                          by (R1) is busy or not.
; Return Value (R2): 0 if machine (R1) is busy, 1 if it is free
;-----------------------------------------------------------------------------------------------------------------
.orig x4200
;-------------------------------
;INSERT CODE For Subroutine MACHINE_STATUS
;--------------------------------
ST R0, R0_BACKUP_4200
ST R7, R7_BACKUP_4200

;prompt bus input fn

LD R0, PTR_GET_INPUT_4200
JSRR R0

ADD R6, R1, #0

;print beginnings
LEA R0, STATUS1
PUTS

LD R0, PTR_PRINT_NUM_4200
JSRR R0

;fill front bit in register
;left shift n times where n is the bus requested
LD R5, SINGLE_BIT_4200
LEFTSHIFT_4200
    	ADD R1, R1, #0
    	BRnz ENDSHIFT_4200
    	;exec LEFTSHIFT
    	ADD R5, R5, R5

    	ADD R1, R1, #-1
    	BR LEFTSHIFT_4200
ENDSHIFT_4200

;mask the shifted bit over busyvec to see if the bit is busy or not

LD R1, BUSYNESS_ADDR_MACHINE_STATUS
LDR R1, R1, #0
AND R1, R5, R1

;if nonzero the machine is free
;return 1
;else 0
BRnp FREECASE_4200
BR BUSYCASE_4200

FREECASE_4200
    	AND R2, R2,#0
    	ADD R2, R2,#1
    	LEA R0, STATUS3
    	PUTS
    	BR END_4200
BUSYCASE_4200
    	AND R2, R2,#0
    	LEA R0, STATUS2
    	PUTS
    	BR END_4200

END_4200

LD R0, R0_BACKUP_4200
LD R7, R7_BACKUP_4200

RET

HALT

;Subroutine Data

R0_BACKUP_4200 .BLKW #1
R7_BACKUP_4200 .BLKW #1

;Local Data

PTR_GET_INPUT_4200 .FILL x4600
PTR_PRINT_NUM_4200 .FILL x4800
SINGLE_BIT_4200 .FILL x1
STATUS1 .STRINGZ "Machine "
STATUS2  .STRINGZ " is busy\n"
STATUS3 .STRINGZ " is free\n"

;--------------------------------
;Data for subroutine MACHINE_STATUS
;--------------------------------
BUSYNESS_ADDR_MACHINE_STATUS .Fill xD000




;-----------------------------------------------------------------------------------------------------------------
; Subroutine: FIRST_FREE
; Inputs: None
; Postcondition: 
; The subroutine has returned a value indicating the lowest numbered free machine
; Return Value (R2): the number of the free machine
;-----------------------------------------------------------------------------------------------------------------
.orig x4400
;-------------------------------
;INSERT CODE For Subroutine FIRST_FREE
;--------------------------------
ST R0, R0_BACKUP_4400
ST R7, R7_BACKUP_4400

;position counter
AND R2, R2, #0
;16 iterations limitor
AND R1, R1, #0
ADD R1, R1, #12
ADD R1, R1, #4

LD R5, FIRST_BIT_4400
LD R4, BUSYNESS_ADDR_FIRST_FREE
LDR R4, R4, #0

;iterate left shifts till free machine is found
LEFTSHIFT_4400
     	AND R3,R4,R5
     	BRnp FINSHIFT_4400   
     	;LEFTSHIFT
     	ADD R5,R5,R5

     	ADD R2,R2,#1
     	ADD R1,R1,#-1
     	BRz FINSHIFT_4400
     	BR LEFTSHIFT_4400
FINSHIFT_4400

;need a special branch for when none are free
;or it outputs machine 16 is free (as it has iterated 0-15 and stopped)
ADD R1, R1, #0
BRnp NORMAL_PRINT_4400 
LEA R0, FIRSTFREE3
PUTS

;jump past the normal print if we did the nonefree print
BR ENDMSG_4400

NORMAL_PRINT_4400
;print normal
LEA R0, FIRSTFREE
PUTS

ADD R6, R2, #0
LD R0, PTR_PRINT_NUM_4400
JSRR R0

LEA R0, FIRSTFREE2
PUTS

ENDMSG_4400


LD R0, R0_BACKUP_4400
LD R7, R7_BACKUP_4400

RET

HALT

;Subroutine Data

R0_BACKUP_4400 .BLKW #1
R7_BACKUP_4400 .BLKW #1

;Local Data

FIRST_BIT_4400 .FILL x1
PTR_PRINT_NUM_4400 .FILL x4800
FIRSTFREE .STRINGZ "\nThe first available machine is number "
FIRSTFREE2 .STRINGZ "\n"
FIRSTFREE3 .STRINGZ "\nNo machines are free\n"

;--------------------------------
;Data for subroutine FIRST_FREE
;--------------------------------
BUSYNESS_ADDR_FIRST_FREE .Fill xD000


;-----------------------------------------------------------------------------------------------------------------
; Subroutine: Get input
; Inputs: None
; Postcondition: 
; The subroutine get up to a 5 digit input from the user within the range [-32768,32767]
; Return Value (R1): The value of the contructed input
; NOTE: This subroutine should be the same as the one that you did in assignment 5
;	to get input from the user, except the prompt is different.
;-----------------------------------------------------------------------------------------------------------------
.orig x4600
;-------------------------------
;INSERT CODE For Subroutine 
;--------------------------------

; (1) Backup R7 and all registers that this subroutine changes except for Return Values
ST R0, BACKUP_R0_3200
ST R7, BACKUP_R7_3200

; (2) Perform whatever algorithm(s) this subroutine is suppose to perform

BR CONTINUE ; to skip RESET branch
               

RESET ; if there's an error, outputs this message       
	LEA R0, Error_message_2
        PUTS


CONTINUE  

	LEA R0, prompt  ;Output Intro Message
	PUTS    
              
        AND R1, R1, #0 
	AND R2, R2, #0
	AND R3, R3, #0
	AND R4, R4, #0
	AND R5, R5, #0
	AND R6, R6, #0

AND R0, R0, #0
                
INPUT_LOOP ; gets user input and checks if '-' or '+' is entered    
	; FIX: check if R0 already has 43 or 45 if user already input +/-
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


; (3) Restore the registers that you backed up
LD R0, BACKUP_R0_3200
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

;--------------------------------
;Data for subroutine Get input
;--------------------------------
prompt .STRINGZ "\nEnter which machine you want the status of (0 - 15), followed by ENTER: "
Error_message_2 .STRINGZ "\nERROR INVALID INPUT"

;-----------------------------------------------------------------------------------------------------------------
; Subroutine: Quit
; Inputs: This subroutine literally does nothing to exit the program
; Postcondition: 
; Return Value : 
;-----------------------------------------------------------------------------------------------------------------
.orig x5200
;-------------------------------
;INSERT CODE For Subroutine 
;--------------------------------

ST R0, BACKUP_R0_5200
ST R7, BACKUP_R7_5200

; do nothing because it's exiting the program 

LD R0, BACKUP_R0_5200
LD R7, BACKUP_R7_5200

RET

;Subroutine Data
BACKUP_R0_5200 .BLKW #1
BACKUP_R7_5200 .BLKW #1
	
;-----------------------------------------------------------------------------------------------------------------
; Subroutine: print number
; Inputs: 
; Postcondition: 
; The subroutine prints the number that is in 
; Return Value : 
; NOTE: This subroutine should print the number to the user WITHOUT 
;		leading 0's and DOES NOT output the '+' for positive numbers.
;-----------------------------------------------------------------------------------------------------------------
.orig x4800
;-------------------------------
;INSERT CODE For Subroutine 
;--------------------------------

ST R0, BACKUP_R0_4800
ST R7, BACKUP_R7_4800

ADD R6, R6, #0
BRz ZERO_CASE_4800
BRn NEG_CASE_4800
BR NORM_CASE_4800

ZERO_CASE_4800
    	LD R4, CONV_TO_CHAR_4800
    	ADD R0,R6,R4
    	OUT
    	BR SKIP_4800_5
NEG_CASE_4800
    	LD R0, MINUS_SIGN_4800
    	OUT
    	NOT R6, R6
    	ADD R6, R6, #1
NORM_CASE_4800

;store in R0, convert to ascii and output front digit
LD R0, DEC_10000_4800
AND R3, R3, #0

AND R1,R1,#0

DECR_10000_4800
    	ADD R2,R6,#0
    	ADD R2,R2,R0
    	BRn DONE_10000_4800
    	ADD R3,R3,#1
    	ADD R6,R2,#0
    	BR DECR_10000_4800
DONE_10000_4800
    	LD R4, CONV_TO_CHAR_4800
    	ADD R0,R3,R4
    	LD R5,CONV_TO_DEC_4800
    	ADD R5,R5,R0
    	ADD R5,R5,R1
    	BRz SKIP_4800_1
    	ADD R1,R1,#1
    	OUT
SKIP_4800_1

LD R0,DEC_1000_4800
AND R3,R3,#0
DECR_1000_4800
    	ADD R2,R6,#0
    	ADD R2,R2,R0
    	BRn DONE_1000_4800
    	ADD R3,R3,#1
    	ADD R6,R2,#0
    	BR DECR_1000_4800
DONE_1000_4800
    	LD R4, CONV_TO_CHAR_4800
    	ADD R0,R3,R4
    	LD R5,CONV_TO_DEC_4800
    	ADD R5,R5,R0
    	ADD R5,R5,R1
    	BRz SKIP_4800_2 
    	ADD R1,R1,#1
    	OUT

SKIP_4800_2
LD R0,DEC_100_4800
AND R3,R3,#0
DECR_100_4800
    	ADD R2,R6,#0
    	ADD R2,R2,R0
    	BRn DONE_100_4800
    	ADD R3,R3,#1
    	ADD R6,R2,#0
    	BR DECR_100_4800
DONE_100_4800
    	LD R4, CONV_TO_CHAR_4800
    	ADD R0,R3,R4
    	LD R5,CONV_TO_DEC_4800
    	ADD R5,R5,R0
    	ADD R5,R5,R1
    	BRz SKIP_4800_3
    	ADD R1,R1,#1
    	OUT

SKIP_4800_3
LD R0,DEC_10_4800
AND R3,R3,#0
DECR_10_4800
    	ADD R2,R6,#0
    	ADD R2,R2,R0
    	BRn DONE_10_4800
    	ADD R3,R3,#1
    	ADD R6,R2,#0
    	BR DECR_10_4800
DONE_10_4800
    	LD R4, CONV_TO_CHAR_4800
    	ADD R0,R3,R4
    	LD R5,CONV_TO_DEC_4800
    	ADD R5,R5,R0
    	ADD R5,R5,R1
    	BRz SKIP_4800_4
    	ADD R1,R1,#1
    	OUT

SKIP_4800_4
LD R0,DEC_1_4800
AND R3,R3,#0
DECR_1_4800
    	ADD R2,R6,#0
    	ADD R2,R2,R0
    	BRn DONE_1_4800
    	ADD R3,R3,#1
    	ADD R6,R2,#0
    	BR DECR_1_4800
DONE_1_4800
    	LD R4, CONV_TO_CHAR_4800
    	ADD R0,R3,R4
    	LD R5,CONV_TO_DEC_4800
    	ADD R5,R5,R0
    	ADD R5,R5,R1
    	BRz SKIP_4800_5
    	ADD R1,R1,#1
    	OUT
SKIP_4800_5

;restore
LD R0,BACKUP_R0_4800
LD R7,BACKUP_R7_4800

RET

;Subroutine Data
BACKUP_R0_4800 .BLKW #1
BACKUP_R7_4800 .BLKW #1

;Local Data
CONV_TO_CHAR_4800 .FILL #48
CONV_TO_DEC_4800 .FILL #-48
MINUS_SIGN_4800 .FILL x2D
DEC_10000_4800 .FILL #-10000
DEC_1000_4800 .FILL #-1000
DEC_100_4800 .FILL #-100
DEC_10_4800 .FILL #-10
DEC_1_4800 .FILL #-1



;--------------------------------
;Data for subroutine print number
;--------------------------------

.ORIG xD000			; Remote data
BUSYNESS .FILL x8000		; <----!!!VALUE FOR BUSYNESS VECTOR!!!

;---------------	
;END of PROGRAM
;---------------	
.END


