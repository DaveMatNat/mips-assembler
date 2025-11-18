# ultra_simple_led_test.asm
# ONLY simple commands

        .text
        .globl main

main:
        addi $sp, $zero, -4096        # safe stack pointer

        # LED address in $t1: 0x3FFFFA0
        addi $t1, $0, -96

        # Turn LED ON (write 1)
        addi $t0, $zero, 1
        sw    $t0, 0($t1)

        # Turn LED OFF (write 0)
        addi $t0, $zero, 0
        sw    $t0, 0($t1)