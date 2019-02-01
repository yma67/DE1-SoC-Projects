			.text
			.global _start
_start:
		LDR R4, =RESULT
		LDR R2, [R4, #4]
		ADD R3, R4, #8
		LDR R5, [R3]
		LDR R6, [R3]

LOOP: 	SUBS R2, R2, #1
		BEQ DONE 
		ADD R3, R3, #4
		LDR R1, [R3]
		CMP R5, R1
		BGE MINC
		MOV R5, R1
MINC: 	CMP R6, R1
		BLE LOOP
		MOV R6, R1
		B LOOP

DONE: 	SUBS R0, R5, R6
		ASR R0, R0, #2
		STR R0, [R4]
END: 	B END

RESULT: .word 0
N: 		.word 5
NUM: 	.word 10, 8, 6, 4, 2
