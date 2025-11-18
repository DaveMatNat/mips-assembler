# Test: Draw a 20x20 blue square at (40, 40)
addi $sp, $0, -4096      # Initialize stack pointer

addi $t2, $0, 255
sw $t2, -216($0)

addi $t1, $0, 40         # Start Y
addi $s1, $0, 60         # End Y

y_loop:
    sw $t1, -220($0)     # Set Y coordinate
    
    # Inner loop: X from 40 to 59
    addi $t0, $0, 40     # Start X
    addi $s0, $0, 60     # End X
    
    x_loop:
        sw $t0, -224($0) # Set X coordinate
        sw $0, -212($0)  # Draw pixel
        
        addi $t0, $t0, 1 # Increment X
        bne $t0, $s0, x_loop
    
    addi $t1, $t1, 1     # Increment Y
    bne $t1, $s1, y_loop

done:
    j done