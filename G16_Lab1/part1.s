		.text
		.global _start
_start:
		LDR R4, =RESULT
		LDR R2, [R4, #4] // loop counter 
		ADD R3, R4, #8   // array pointer
		LDR R0, [R3]     // current max, as first element in array
			
LOOP: 		SUBS R2, R2, #1  // counter - 1, loop N - 1 times
		BEQ DONE	 // end loop
		ADD R3, R3, #4   // increment array pointer
		LDR R1, [R3]	 // load current number
		CMP R0, R1	 // compare element
		BGE LOOP
		MOV R0, R1	 // if small, update max
		B LOOP

DONE: 		STR R0, [R4]	 // store output

END: 		B END

RESULT: 	.word 0
N: 		.word 7
NUMBERS: 	.word 4, 5, 3, 6, 1, 8, 2
