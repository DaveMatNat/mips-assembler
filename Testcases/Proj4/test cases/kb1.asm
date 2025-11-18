# Test: Read from keyboard and echo to terminal
addi $sp, $0, -4096      # Initialize stack pointer

loop:
    # Check if key is ready
    lw $t0, -240($0)         # Read keyboard status (0x3FFFF10)
    beq $t0, $0, loop        # If 0, no key pressed, keep waiting
     
    # Key is ready, get it
    lw $t1, -236($0)         # Read keyboard data (0x3FFFF14)
    
    # Echo to terminal
    sw $t1, -256($0)         # Write to terminal (0x3FFFF00)
    
    # Advance to next key
    sw $0, -240($0)          # Write anything to status to advance
    
    j loop                   # Repeat forever

done:
    j done