			.text
			.global _start
			.global main

_start:		
			LDR R12, =DEFAULT
			LDR R5, =N
			LDR R7, [R5]
			MOV R8, #0
			ADD R6, R5, #4
			B main

main:		STR R4, [R12, #4]!		//PUSH A STACK FRAME
			STR LR, [R12, #4]!		//SAVING LR ONTO THE STACK
			SUB R4, R12, #4			//SETTING UP THE BOTTOM OF THE STACK
			BL LOOP					//GO TO THE LOOP SUBROUTINE				
			ADD R12, R4, #4 		
			LDMFA R12!, {LR, R4}
			MOV R0, #0
			MOV R8, #0
			STR R4, [R12, #4]!
			STR LR, [R12, #4]!
			SUB R4, R12, #4
			BL FINDMAX
			ADD R12, R4, #4 		
			LDMFA R12!, {LR, R4}
			B END
			

LOOP:		CMP R8, R7				
			BXEQ LR
			ADD R8, R8, #1
			LDR R0, [R6], #4
			STR R0, [R12, #4]!
			B LOOP

FINDMAX:	CMP R8, R7				
			BXEQ LR
			ADD R8, R8, #1
			LDR R1, [R12, #4]!
			CMP R0,R1
			MOVLT R0,R1
			B FINDMAX
END:		B END

N:  		.word 10
NUMBERS:	.word 1,99,2,3,4,18,22,96,65,31
DEFAULT:	.word 0		
