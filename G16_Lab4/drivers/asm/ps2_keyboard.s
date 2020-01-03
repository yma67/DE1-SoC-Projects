    .text
    .equ KB_BASE, 0xFF200100
    .global read_PS2_data_ASM

read_PS2_data_ASM: 
    PUSH {R1, R2, R3}
    LDR R1, =KB_BASE
    LDR R2, [R1]
    AND R1, R2, #0x8000
    LSRS R3, R1, #15
    BEQ FIN
    ANDS R1, R2, #0xFF
    STRB R1, [R0]
FIN:	
    MOV R0, R3
    POP {R1, R2, R3}
    BX LR
    .end
