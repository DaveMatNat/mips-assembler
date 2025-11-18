# Test: Draw one red pixel at (50, 30)
addi $sp, $0, -4096      # Initialize stack pointer

# Set X coordinate
addi $t0, $0, 50
sw $t0, -224($0)         # Write X (0x3FFFF20)

# Set Y coordinate
addi $t1, $0, 30
sw $t1, -220($0)         # Write Y (0x3FFFF24)

# Set color to RED (0xFF0000)
lui $t2, 0x00FF          # Load upper 16 bits
sw $t2, -216($0)         # Write Color (0x3FFFF28)

# Trigger the write
sw $0, -212($0)          # Write anything to trigger (0x3FFFF2C)

done:
    j done