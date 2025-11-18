# Test: Draw pixels with changing colors
addi $sp, $0, -4096      # Initialize stack pointer

# Draw diagonal line with changing colors
addi $t0, $0, 0          # X and Y counter
addi $t3, $0, 100        # Stop at 100

addi $t2, $0, 0          # Color counter

rainbow_loop:
    # Set X and Y (diagonal)
    sw $t0, -224($0)
    sw $t0, -220($0)
    
    # Calculate color (shift left by 16 to get different hues)
    sll $t4, $t2, 16
    sw $t4, -216($0)
    
    # Draw pixel
    sw $0, -212($0)
    
    # Increment
    addi $t0, $t0, 1
    addi $t2, $t2, 2555   # Increment color faster
    
    bne $t0, $t3, rainbow_loop

done:
    j done