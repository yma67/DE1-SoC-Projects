		.text
		.equ FIFO_BASE 0xFF203044
		.equ LEFT_BASE 0xFF203048
		.equ RIGHT_BASE 0xFF20303C
		.global write_audio_LR_ASM

write_audio_LR_ASM: 
		PUSH {R1, R2, R3}
		LDR R1, =FIFO_BASE
		LDR R2, [R1]
		LSR R2, R2, #16
		MOV R3, R2
		ANDS R2, R2, #0xF0
		BEQ FIN
		ANDS R3, R3, #0xF
		BEQ FIN
		LDR R1, =LEFT_BASE
		STR R0, [R1]
		LDR R1, =RIGHT_BASE
		STR R0, [R1]
		MOV R0, #1
		POP {R1, R2, R3}
		BX LR
FIN:	MOV R0, #0
		POP {R1, R2, R3}
		BX LR

		.end