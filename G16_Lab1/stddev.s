		.text
		.global _start
_start:
		LDR R4, =RESULT
		LDR R2, [R4, #4] // load N
		ADD R3, R4, #8	 // load array pointer
		LDR R5, [R3]	 // load current max (as first elem)
		LDR R6, [R3]	 // load current min (as first elem)

LOOP: 		SUBS R2, R2, #1	 // for each element, do comparison and update
		BEQ DONE         // when finished, do final calculation
		ADD R3, R3, #4	 
		LDR R1, [R3]
		CMP R5, R1	 // check max
		BGE MINC	 // if not greater than current max, check min
		MOV R5, R1	 // else update max
MINC: 		CMP R6, R1	 // check min
		BLE LOOP	 // if not smaller than current min, continue
		MOV R6, R1	 // else update min
		B LOOP

DONE: 		SUBS R0, R5, R6  // max - min
		ASR R0, R0, #2	 // divide by 4
		STR R0, [R4]

END: 		B END

RESULT: 	.word 0
N: 		.word 5
NUM: 		.word 10, 8, 6, 4, 2
