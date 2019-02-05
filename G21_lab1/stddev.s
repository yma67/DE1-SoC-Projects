				.text
				.global _start

_start:
				LDR R4, =RESULT		//R4 points to the result
				LDR R2, [R4, #4]	//R2 points to the number of the elements
				ADD R3, R4, #8		//R3 points to the first number of the list
				LDR R0, [R3]		//R0 holds the first number
				LDR R11, [R3]       //R11 holds for min value

LOOP: 			SUBS R2, R2, #1
				BEQ DONE
				ADD R3, R3, #4
				LDR R1, [R3]
				LDR R10, [R3]
				CMP R11, R10		//compare the min value with next integer
				MOVGT R11, R10		//if the min is greater than new integer, than move value in the R10 to R11
				CMP R0, R1
				BGE LOOP
				MOV R0, R1
				B LOOP

DONE:			SUB R0, R0, R11		//substarct the min value from the max value and store in R0
				ASR R0, R0, #2		//right shift the value 2 bits in R0 to divide value by 4
				STR R0, [R4]		//store the result in the original address
				


END:			B END

RESULT:		.word		0
N:				.word		7
NUMBERS:		.word		4,	5,	3,	6,	1,	8,	91
