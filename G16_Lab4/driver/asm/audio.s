		.text
		.equ FIFO_BASE, 0xFF203044
		.equ LEFT_BASE, 0xFF203048
		.equ RIGHT_BASE, 0xFF20303C
		.global write_audio_LR_ASM

write_audio_LR_ASM: 

		PUSH {R1, R2, R3}
		LDR R1, =FIFO_BASE
		LDR R2, [R1]
		LSR R2, R2, #16
		ANDS R3, R2, #0xFF
		BLE FIN
		LSR R2, R2, #8
		ANDS R3, R2, #0xFF
		BLE FIN
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
