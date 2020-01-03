        .text
        .equ HEX_A, 0xFF200020
        .equ HEX_B, 0xFF200030
        .global HEX_clear_ASM
        .global HEX_flood_ASM
        .global HEX_write_ASM

HEX_clear_ASM:
        PUSH {R1, LR}
        MOV R1, #0x00
        BL LOAD_MULTIPLE_VAR
        POP {R1, LR}
        BX LR

HEX_flood_ASM:
        PUSH {R1, LR}
        MOV R1, #0x7F
        BL LOAD_MULTIPLE_VAR
        POP {R1, LR}
        BX LR

HEX_write_ASM:
        PUSH {R1, R2, R3, LR}
        LDR R2, =LOOKUP
        LDRB R3, [R2, R1]
        MOV R1, R3
        BL LOAD_MULTIPLE_VAR
        POP {R1, R2, R3, LR}
        BX LR

LOAD_MULTIPLE_VAR:
        PUSH {R2, R3, R4, R5, R6, R7}
        LDR R2, =HEX_A
        LDR R3, =HEX_B
	MOV R7, #0xFF
        MOV R4, #-1
	MOV R5, #1
AST:    ADD R4, R4, #1
        CMP R4, #6
        BGE FIN
        TST R0, R5, LSL R4
        BEQ AST
	LDR R6, [R2]
	CMP R4, #0
        BICEQ R6, R6, R7
        ORREQ R6, R6, R1
	CMP R4, #1
        BICEQ R6, R6, R7, ROR #24
        ORREQ R6, R6, R1, ROR #24
	CMP R4, #2
        BICEQ R6, R6, R7, ROR #16
        ORREQ R6, R6, R1, ROR #16
        CMP R4, #3
        BICEQ R6, R6, R7, ROR #8
        ORREQ R6, R6, R1, ROR #8
	STR R6, [R2]
	LDR R6, [R3]
        CMP R4, #4
        BICEQ R6, R6, R7
        ORREQ R6, R6, R1
        CMP R4, #5
        BICEQ R6, R6, R7, ROR #24
        ORREQ R6, R6, R1, ROR #24
	STR R6, [R3]
        B AST
FIN:    POP {R2, R3, R4, R5, R6, R7}
        BX LR

LOOKUP: .byte   0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71

        .end
