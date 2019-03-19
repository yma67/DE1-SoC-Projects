        .text
        .equ PB_DATA, 0xFF200050
        .equ PB_INTR_MSK, 0xFF200058
        .equ PB_EDGE_CAP, 0xFF20005C
        .global read_PB_data_ASM
        .global PB_data_is_pressed_ASM
        .global read_PB_edgecap_ASM
        .global PB_edgecap_is_pressed_ASM
        .global PB_clear_edgecp_ASM
        .global enable_PB_INT_ASM
        .global disable_PB_INT_ASM

read_PB_data_ASM:
        PUSH {R1, LR}
        LDR R1, =PB_DATA
		LDR R0, [R1]
        POP {R1, LR}
        BX LR

PB_data_is_pressed_ASM: 
        PUSH {R1, R2}
        LDR R1, =PB_DATA
        LDR R2, [R1]
		TST R2, R0
		MOVEQ R0, #0
		MOVNE R0, #1
        POP {R1, R2}
        BX LR

read_PB_edgecap_ASM: 
        PUSH {R1, LR}
        LDR R1, =PB_EDGE_CAP
        LDR R0, [R1]
        POP {R1, LR}
        BX LR

PB_edgecap_is_pressed_ASM: 
        PUSH {R1, R2}
        LDR R1, =PB_EDGE_CAP
        LDR R2, [R1]
		TST R2, R0
		MOVEQ R0, #0
		MOVNE R0, #1
        POP {R1, R2}
        BX LR

PB_clear_edgecp_ASM: 
        PUSH {R1}
        LDR R1, =PB_EDGE_CAP
        STR R0, [R1]
        POP {R1}
        BX LR

enable_PB_INT_ASM: 
        PUSH {R1, R2}
        LDR R1, =PB_INTR_MSK
        LDR R2, [R1]
        ORR R2, R2, R0
        STR R2, [R1]
        POP {R1, R2}
        BX LR

disable_PB_INT_ASM:
        PUSH {R1, R2}
        LDR R1, =PB_INTR_MSK
        LDR R2, [R1]
        BIC R2, R2, R0
        STR R2, [R1]
        POP {R1, R2}
        BX LR

        .end
