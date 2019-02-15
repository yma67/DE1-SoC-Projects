		.text
		.global _start
_start:
		LDR	R4, =N	// R4: start of program
		MOV R0, #0	// R0: bool isSorted

WHILE: 		CMP R0, #0	// while if not sorted
		BNE FINISH
		MOV R0, #1	// set sorted
		LDR R2, [R4]	// R2: decrement counter
		ADD R3, R4, #4	// R3: array pointer
		LDR R6, [R3]	// R6: current element

FOR: 		MOV R5, R6	// R5: previous element
		ADD R3, R3, #4
		SUBS R2, R2, #1 // loop N - 1 times
		BEQ CNT
		LDR R6, [R3]
		CMP R6, R5	// if current grater or equal than prev element
		BGE FOR		// then continue
		STR R5, [R3]	// else swap in both memory and register and continue
		STR R6, [R3, #-4]
		MOV R7, R5	// R7: temp in swap
		MOV R5, R6
		MOV R6, R7
		MOV R0, #0
		B FOR

CNT: 		B WHILE

FINISH: 	B FINISH

N: 		.word 5
NUM: 		.word 9, 5, 4, 3, 2, -1, -99, -100
