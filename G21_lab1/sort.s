				.text
				.global _start

_start:
				LDR R0, =NUMBERS		//R0 points to the initial address of the array
				LDR R9, =N				//R9 points to number of elements
				LDR R11, [R9]			//R11 holds the value of R9, N
				MOV R10, #0				//set R10 as the flag, 0 is false by default

SORT:			CMP R10, #1				//if the flag is true
				BEQ END					//then terminate the while loop
				LDR R0, =NUMBERS		//R0 points to the initial address of the array
				MOV R10, #1				//set the flag as true
				MOV R8, #1				//initilize the counter
				B LOOP					//go to for loop

LOOP: 			CMP R8, R11				//check if the counter reaches N
				BEQ SORT				//if true then go back to the while loop
				ADD R8, R8, #1			//increment the counter by one
				ADD R6, R0, #4			//take the address of next number and store in R6
				LDR R2, [R0]			//let R2 holds the first number
				LDR R3, [R6]			//let R3 holds the second number		
				CMP R2, R3				//compare the first number and the second number
				BGT METHOD1				//if the first number is greater than the second number, then do method1
				ADD R0, R0, #4			//put the R0 pointer to the next number
				B LOOP

METHOD1:		STR R2, [R6]
				STR R3, [R0]
				MOV R10, #0
				ADD R0, R0, #4			
				B LOOP								

END:			B END


N:				.word	13		
NUMBERS:		.word	1, 44, 0, 9, 5,	3,	2, 2,	7,	4, 32, 12, 1
