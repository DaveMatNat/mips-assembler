# Test: Write to memory and read it back
addi $sp, $0, -4096

# Write some values to memory
addi $t0, $0, 42
sw $t0, 0($0)           

addi $t0, $0, 100
sw $t0, 4($0)           

addi $t0, $0, 255
sw $t0, 8($0)            

# Read them back
lw $t1, 0($0)            # Should get 42
lw $t2, 4($0)            # Should get 100
lw $t3, 8($0)            # Should get 255

# Print results to terminal 
addi $t1, $t1, 48        # Convert to ASCII (42 + 48 = 90 = 'Z' )
sw $t1, -256($0)

done:
    j done