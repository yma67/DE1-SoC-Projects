			.text
			.global _start
_start:	
		LDR R4, =B
		LDMIA R4!, {R0-R3}
		STR R0, [SP, #-4]!
		STMDB SP!, {R1-R3}
		LDMIA SP!, {R0-R3}

END: 	B END

B: 		.word 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
