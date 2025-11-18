# button_print_if_pressed.asm
# Print 'B' only when any button is pressed.
# No 'li' used.

        .text
        .globl main

main:
        # Safe stack pointer
        addi $sp, $zero, -4096

        # BUTTON address in $t1
        addi $t1, $zero, -112

        # TERMINAL address in $t2
        addi $t2, $zero, -256

loop:
        lw    $t0, 0($t1)      # read button bits
        beq   $t0, $zero, loop # if no button pressed, keep polling

        # Put ASCII 'B' (= 66) into $t3 without using li
        addi $t3, $zero, 66   # 66 = 'B'

        sw    $t3, 0($t2)      # print 'B'

        j     loop