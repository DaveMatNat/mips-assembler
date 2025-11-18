addi $sp, $0, -4096 

# Set freq to 440 Hz
addi $t0, $0, 440
sw $t0, -128($0)         # Write to freq register (0x3FFFF80)

# Set volume to 64 
addi $t1, $0, 64
sw $t1, -124($0)         # Write to volume register (0x3FFFF84)

# Turn sound ON
sw $0, -120($0)          # Write to toggle register (0x3FFFF88)

# simple delay loop
addi $t2, $0, 50
delay1:
    addi $t2, $t2, -1
    bne $t2, $0, delay1

# turn sound OFF
sw $0, -120($0)         

done:
    j done