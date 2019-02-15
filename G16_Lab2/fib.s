			.text
			.global _start
_start:
			LDR R4, =RESULT
			LDR R0, [R4]
			PUSH {LR}
			BL FIB
			POP {LR}
			STR R0, [R4]
			B END 

FIB: 		PUSH {R4, R5}
			CMP R0, #2
			BGE INDUCTION
			MOV R0, #1
			POP {R4, R5}
			BX LR
INDUCTION: 	SUB R0, R0, #1
			SUB R4, R0, #1
			PUSH {LR}
			BL FIB
			POP {LR}
			MOV R5, R0
			MOV R0, R4
			MOV R4, R5
			PUSH {LR}
			BL FIB
			POP {LR}
			ADD R0, R0, R4
			POP {R4, R5}
			BX LR

END: 		B END

RESULT: 	.word 11
