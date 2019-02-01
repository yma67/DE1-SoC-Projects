		.text
		.global _start
_start:
		LDR R4, =RESULT	 // R4: start of program
		LDR R2, [R4, #4] // R2: number of element as decrement counter
		CLZ R8, R2	 // R8: number of shifts
		RSB R8, R8, #31	 // calculate number of shift to be done in division
		ADD R3, R4, #8	 // R3: array pointer
		LDR R5, [R3]	 // R5: current sum

LOOP: 		SUBS R2, R2, #1  // N - 1 iterations for sum
		BEQ NXT
		ADD R3, R3, #4
		LDR R1, [R3]
		ADD R5, R5, R1	 // load, add current with previous
		B LOOP

NXT: 		ASR R5, R5, R8	 // divide using shift
		STR R5, [R4]
		LDR R2, [R4, #4] // reset loop counter and array pointer
		ADD R3, R4, #8

MAP: 		LDR R0, [R3]
		SUBS R0, R0, R5	 // R0: subtract element, and store in mem
		STR R0, [R3], #4
		SUBS R2, R2, #1	 // branch for, N iterations
		BEQ DONE
		B MAP

DONE:		B DONE

RESULT: 	.word 0
N: 		.word 8
NUMBER: 	.word 2, 9, 11, 5, 7, 6, 8, 7
