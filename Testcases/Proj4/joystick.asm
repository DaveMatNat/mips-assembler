# joystick_x_test.asm
# Only simple commands

        .text
        .globl main

main:
        addi $sp, $zero, -4096

        # X address = 0x3FFFF50
        addi $t1, $0, -176

        # Y address = 0x3FFFF54
        addi $t2, $0, -172

        # Terminal
        addi $t3, $0, -256

loop:
        # ------------------------
        # Check X direction
        # ------------------------
        lw    $t0, 0($t1)          # read X
        addi $t5, $0, 8
        beq   $t0, $t5, check_y  # if X == 0 → skip print

        # print 'X' = ASCII 88
        addi $t4, $zero, 88
        sw    $t4, 0($t3)

check_y:
        # ------------------------
        # Check Y direction
        # ------------------------
        lw    $t0, 0($t2)          # read Y
        addi $t5, $0, 8
        beq   $t0, $t5, loop     # if Y == 0 → restart loop

        # print 'Y' = ASCII 89
        addi $t4, $zero, 89
        sw    $t4, 0($t3)

        j     loop

