# Test: Print "HELLO" to terminal
addi $sp, $0, -4096      # Initialize stack pointer

addi $t0, $0, 72         # 'H'
sw $t0, -256($0)

addi $t0, $0, 69         # 'E'
sw $t0, -256($0)

addi $t0, $0, 76         # 'L'
sw $t0, -256($0)

addi $t0, $0, 76         # 'L'
sw $t0, -256($0)

addi $t0, $0, 79         # 'O'
sw $t0, -256($0)

addi $t0, $0, 10         # newline
sw $t0, -256($0)

done:
    j done               # Infinite loop to keep program running