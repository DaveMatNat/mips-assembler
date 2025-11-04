.data
.text
main:
    addi $t0, $0, 0
    addi $t1, $t1, 1
    While:
        beq $t0, $t1, Exit
        addi $t0, $t0, 1
        j While
    Exit:
        j main