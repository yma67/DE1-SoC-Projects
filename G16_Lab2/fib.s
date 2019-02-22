			.text
			.global _start
_start:
			LDR R4, =RESULT
			LDR R0, [R4]
			BL FIB
			STR R0, [R4]
			B END 

FIB: 		PUSH {R4, R5, LR}
			CMP R0, #2
			BGE INDUCTION
			MOV R0, #1
			POP {R4, R5, LR}
			BX LR
INDUCTION: 	SUB R0, R0, #1
			SUB R4, R0, #1
			BL FIB
			MOV R5, R0
			MOV R0, R4
			MOV R4, R5
			BL FIB
			ADD R0, R0, R4
			POP {R4, R5, LR}
			BX LR

END: 		B END

RESULT: 	.word 11