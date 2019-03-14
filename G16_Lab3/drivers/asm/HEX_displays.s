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
        PUSH {R1, R2, LR}
        CMP R1, #0
        MOVEQ R2, #0x3F
        CMP R1, #1
        MOVEQ R2, #0x06
        CMP R1, #2
        MOVEQ R2, #0x5B
        CMP R1, #3
        MOVEQ R2, #0x4F
        CMP R1, #4
        MOVEQ R2, #0x66
        CMP R1, #5
        MOVEQ R2, #0x6D
        CMP R1, #6
        MOVEQ R2, #0x7D
        CMP R1, #7
        MOVEQ R2, #0x07
        CMP R1, #8
        MOVEQ R2, #0x7F
        CMP R1, #9
        MOVEQ R2, #0x6F
        CMP R1, #10
        MOVEQ R2, #0x77
        CMP R1, #11
        MOVEQ R2, #0x7C
        CMP R1, #12
        MOVEQ R2, #0x39
        CMP R1, #13
        MOVEQ R2, #0x5E
        CMP R1, #14
        MOVEQ R2, #0x79
        CMP R1, #15
        MOVEQ R2, #0x71
        MOV R1, R2
        BL LOAD_MULTIPLE_VAR
        POP {R1, R2, LR}
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
        .end
