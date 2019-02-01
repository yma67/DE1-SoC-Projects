		.text
		.global _start
_start:
		LDR R4, =RESULT
		LDR R2, [R4, #4]
		CLZ R8, R2
		RSB R8, R8, #31
		ADD R3, R4, #8
		LDR R5, [R3]

LOOP: 		SUBS R2, R2, #1
		BEQ NXT
		ADD R3, R3, #4
		LDR R1, [R3]
		ADD R5, R5, R1
		B LOOP

NXT: 		ASR R5, R5, R8
		STR R5, [R4]
		LDR R2, [R4, #4]
		ADD R3, R4, #8

MAP: 		LDR R0, [R3]
		SUBS R0, R0, R5
		STR R0, [R3], #4
		SUBS R2, R2, #1
		BEQ DONE
		B MAP

DONE:	B DONE

RESULT: .word 0
N: 	.word 8
NUMBER: .word 2, 9, 11, 5, 7, 6, 8, 7
