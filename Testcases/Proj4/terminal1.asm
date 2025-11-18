# Test: Print 'A' to terminal
addi $sp, $0, -4096      # Initialize stack pointer
addi $t0, $0, 65         # ASCII code for 'A'
sw $t0, -256($0)         # Write to terminal (0x3FFFF00)