# Test: Store and retrieve an array
addi $sp, $0, -4096      # Initialize stack pointer

# Store array values
addi $t0, $0, 10
sw $t0, 100($0)          # array[0] = 10

addi $t0, $0, 20
sw $t0, 104($0)          # array[1] = 20

addi $t0, $0, 30
sw $t0, 108($0)          # array[2] = 30

# Load and sum the array
lw $t1, 100($0)
lw $t2, 104($0)
lw $t3, 108($0)

add $t4, $t1, $t2
add $t4, $t4, $t3        # t4 = 10 + 20 + 30 = 60

done:
    j done