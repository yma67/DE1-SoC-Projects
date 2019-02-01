			.text
			.global _start
_start:
		LDR	R4, =N
		MOV R0, #0

WHILE: 	CMP R0, #0
		BNE FINISH
		MOV R0, #1
		LDR R2, [R4]
		ADD R3, R4, #4
		LDR R6, [R3]

FOR: 	MOV R5, R6
		ADD R3, R3, #4
		SUBS R2, R2, #1
		BEQ CNT
		LDR R6, [R3]
		CMP R6, R5
		BGE FOR
		STR R5, [R3]
		STR R6, [R3, #-4]
		MOV R7, R5
		MOV R5, R6
		MOV R6, R7
		MOV R0, #0
		B FOR

CNT: 	B WHILE

FINISH: B FINISH
N: 		.word 5
NUM: 	.word 5, 4, 3, 2, 1