					.text
					.global _start
_start:
					LDR R0, =AVG
					LDR R1, =N
					LDR R2, [R1]
					LDR R7, [R1]
					ADD R3, R1, #4
					MOV R8, #1
					LDR R4, [R3]			//r4 STORES THE INITIAL VALUE
					MOV R10, #1

NBITS:				CMP R2, #2				
					BEQ SUM
					ASR R2, #1
					ADD R10, #1
					B NBITS

SUM:				CMP R8, R7		
					BEQ GETAVG
					ADD R8, R8, #1			//INCREMENT BY 1	
					LDR R5, [R3, #4]		//R5 STORES THE NEXT NUMBER
					ADD R4, R4, R5
					ADD R3, R3, #4
					B SUM				

GETAVG:			ASR R4, R4, R10
					STR R4, [R0]
					MOV R8, #0
					LDR R3, =NUMBER
					B CENTERING

CENTERING:			CMP R8, R7		
					BEQ DONE
					ADD R8, R8, #1			//INCREMENT BY 1	
					LDR R5, [R3]
					SUB R5, R5, R4
					STR R5, [R3]
					ADD R3, R3, #4
					B CENTERING

DONE:				B DONE

AVG:				.word 0
N:					.word 8
NUMBER:			.word 2,9,11,5,7,6,8,7
