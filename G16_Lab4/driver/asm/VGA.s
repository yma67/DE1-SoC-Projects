		.text
		.equ CHAR_BASE 0xC9000000
		.equ PIXEL_BASE 0xC8000000
		.global VGA_clear_charbuff_ASM
		.global VGA_clear_pixelbuff_ASM
		.global VGA_write_char_ASM
		.global VGA_write_byte_ASM
		.global VGA_draw_point_ASM

VGA_clear_charbuff_ASM: 
		PUSH {R0, R1, R2, R3, R4, R5}
		LDR R0, =CHAR_BASE
		LDR R5, [R0]
		LDR R1, #59
		MOV R4, #0
MAP_R: 	LDR R2, #79
MAP_C:	ADD R3, R2, R1, LSL #7
		ADD R3, R5, R3
		STRH R4, [R3]
		SUBS R2, R2, #1
		BGE MAP_C
		SUBS R1, R1, #1
		BGE MAP_R
		POP {R0, R1, R2, R3, R4, R5}
		BX LR

VGA_clear_pixelbuff_ASM: 
		PUSH {R0, R1, R2, R3, R4, R5}
		LDR R0, =PIXEL_BASE
		LDR R5, [R0]
		LDR R1, #239
		MOV R4, #0
MAP_R: 	LDR R2, #319
MAP_C:	ADD R3, R2, R1, LSL #8
		ADD R3, R5, R3, LSL #1
		STRH R4, [R3]
		SUBS R2, R2, #1
		BGE MAP_C
		SUBS R1, R1, #1
		BGE MAP_R
		POP {R0, R1, R2, R3, R4, R5}
		BX LR

VGA_write_char_ASM: 
		PUSH {R3, R4, R5}
		CMP R0, #0
		BLT FWC
		CMP R1, #0
		BLT FWC
		CMP R0, #79
		BGT FWC
		CMP R1, #59
		BGT FWC
		LDR R4, =CHAR_BASE
		LDR R5, [R4]
		ADD R3, R0, R1, LSL #7
		ADD R3, R3, R5
		STRB R2, [R3]
		POP {R3, R4, R5}
FWC: 	BX LR

VGA_write_byte_ASM: 
		PUSH {R3, R4, R5, R6, R7, R8}
		CMP R0, #0
		BLT FWB
		CMP R1, #0
		BLT FWB
		CMP R0, #78
		BGT FWB
		CMP R1, #59
		BGT FWB
		LDR R4, =CHAR_BASE
		LDR R5, [R4]
		AND R6, R2, #0xF
		AND R7, R2, #0xF0
		LSR R7, R7, #4
		LDR R8, =LOOKUP
		LDR R6, [R8, R6]
		LDR R7, [R8, R7]
		ADD R3, R0, R1, LSL #7
		ADD R3, R3, R5
		STRB R6, [R3], #1
		STRB R7, [R3], #1
		POP {R3, R4, R5, R6, R7, R8}
FWB: 	BX LR

VGA_draw_point_ASM: 
		PUSH {R3, R4, R5}
		CMP R0, #0
		BLT FWP
		CMP R1, #0
		BLT FWP
		CMP R0, #319
		BGT FWP
		CMP R1, #239
		BGT FWP
		LDR R4, =PIXEL_BASE
		LDR R5, [R4]
		ADD R3, R0, R1, LSL #8
		ADD R3, R5, R3, LSL #1
		STRH R2, [R3]
		POP {R3, R4, R5}
FWP: 	BX LR

LOOKUP: .byte 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 65, 66, 67, 68, 69, 70

		.end