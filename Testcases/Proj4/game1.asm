# Test: Use WASD to move a white pixel around
addi $sp, $0, -4096      # Initialize stack pointer

# Initial position
addi $s0, $0, 64         # X = 64 (center-ish)
addi $s1, $0, 64         # Y = 64 (center-ish)

# Color constants
addi $s2, $0, 16777215          # White color

# Key codes
addi $s3, $0, 119        # 'w' = up
addi $s4, $0, 97         # 'a' = left
addi $s5, $0, 115        # 's' = down
addi $s6, $0, 100        # 'd' = right

main_loop:
    # Draw current pixel
    sw $s0, -224($0)     # Set X
    sw $s1, -220($0)     # Set Y
    sw $s2, -216($0)     # Set color
    sw $0, -212($0)      # Draw
    
    # Check for keyboard input
    lw $t0, -240($0)     # Check keyboard status
    beq $t0, $0, main_loop  # No key, keep drawing
    
    # Get the key
    lw $t1, -236($0)     # Read keyboard data
    
    # Check which key
    beq $t1, $s3, move_up
    beq $t1, $s4, move_left
    beq $t1, $s5, move_down
    beq $t1, $s6, move_right
    j advance_key        # Unknown key, just advance

move_up:
    addi $s1, $s1, -1    # Y--
    j advance_key

move_left:
    addi $s0, $s0, -1    # X--
    j advance_key

move_down:
    addi $s1, $s1, 1     # Y++
    j advance_key

move_right:
    addi $s0, $s0, 1     # X++
    j advance_key

advance_key:
    sw $0, -240($0)      # Advance keyboard
    j main_loop