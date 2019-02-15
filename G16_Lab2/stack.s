			.text
			.global _start
_start:	
		LDR R4, =B
		LDMIA R4!, {R0-R2}
		STR R0, [SP, #-4]!
		PUSH {R1-R2}
		LDMIA SP!, {R0-R2}

END: 	B END

B: 		.word 3, 4, 5
