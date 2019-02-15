			.text
			.global _start
_start:
		LDR R4, =RESULT
		LDR R1, [R4, #4]
		LDR R0, =ARRAY
		PUSH {LR}
		BL MAX
		POP {LR}
		STR R0, [R4]
		B END

MAX:    PUSH {R4, R5}
		LDR R4, [R0], #4
LOOP: 	SUBS R1, R1, #1
		BLE DONE
		LDR R5, [R0], #4
		CMP R4, R5
		BGE LOOP
		MOV R4, R5
		B LOOP
DONE: 	MOV R0, R4
		POP {R4, R5}
		BX LR

END: 	B END

RESULT: .word 0
N: 		.word 6
ARRAY: 	.word -3, 4, 5, 6, 7, 11
