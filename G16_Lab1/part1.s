			.text
			.global _start
_start:
			LDR R4, =RESULT
			LDR R2, [R4, #4] // loop counter 
			ADD R3, R4, #8 // array pointer
			LDR R0, [R3] // current max
			
LOOP: 		SUBS R2, R2, #1
			BEQ DONE
			ADD R3, R3, #4
			LDR R1, [R3]
			CMP R0, R1
			BGE LOOP
			MOV R0, R1
			B LOOP

DONE: 		STR R0, [R4]

END: 		B END

RESULT: 	.word 0
N: 			.word 7
NUMBERS: 	.word 4, 5, 3, 6
			.word 1, 8, 2