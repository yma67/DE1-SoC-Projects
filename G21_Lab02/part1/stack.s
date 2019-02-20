			.text
			.global _start
_start:		LDR R12, =DEFAULT
			LDR R5, =N
			LDR R7, [R5]
			MOV R8, #0
			ADD R6, R5, #4

LOOP:		CMP R8, R7				
			BEQ POPALL
			ADD R8, R8, #1
			LDR R0, [R6]
			STR R0, [R12, #4]!
			ADD R6, R6, #4
			B LOOP

POPALL:		LDMFA R12!, {R2-R6}
			B END
END:		B END

N:  		.word 5
NUMBERS:	.word 1,2,3,4,18
DEFAULT:	.word 0		




