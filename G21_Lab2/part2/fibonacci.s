				.text
				.global _start
				.global main
_start:			
				LDR R0, =N				//load N into the R0
				LDR R0, [R0]
				MOV R4, #0				//clear R4 to store result
				SUB R1, SP, #4			//store the top of the stack
				B main

main:			PUSH {LR}				//store the original LR
				BL FIB					//go to fibonacci

RETURN:		POP {R7}				//pop the top of the number				
				CMP R1, SP				//if the stack is empty, terminate the algorithm
				BEQ FINISH
				POP {R0}				//pop the second number, make it -1, and store as the new n				
				SUB R0, R0, #1
				BX LR					//this lr goes back to FIB

FIB:			PUSH {R0}				//push the number into the stack
				CMP R0, #2				//if the number is less than 2, result+1 and start return
				ADDLT R4, R4, #1
				BLLT RETURN
				SUB R0, R0, #1			
				B FIB					//call the fib subroutine again

FINISH:		POP {LR}
				B END				//restore LR 
END:			B END
				

N:				.word 5
