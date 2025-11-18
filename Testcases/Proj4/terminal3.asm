# Test: Print digits 0-9
addi $sp, $0, -4096      # Initialize stack pointer
addi $t0, $0, 48         # ASCII '0' = 48
addi $t1, $0, 58         # ASCII '9' = 57 (stop at 58)

loop:
    sw $t0, -256($0)     # Print current digit
    addi $t0, $t0, 1     # Next digit
    bne $t0, $t1, loop   # Continue if not done

addi $t0, $0, 10         # newline
sw $t0, -256($0)

done:
    j done