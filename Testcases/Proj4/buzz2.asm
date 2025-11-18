# Test: Play a simple scale
addi $sp, $0, -4096      # Initialize stack pointer

# Set volume first
addi $t0, $0, 80
sw $t0, -124($0)         # Volume = 80

# Turn sound ON
sw $0, -120($0)

# C note (262 Hz)
addi $t0, $0, 262
sw $t0, -128($0)
addi $t1, $0, 100
delay_c:
    addi $t1, $t1, -1
    bne $t1, $0, delay_c

# D note (294 Hz)
addi $t0, $0, 294
sw $t0, -128($0)
addi $t1, $0, 100
delay_d:
    addi $t1, $t1, -1
    bne $t1, $0, delay_d

# E note (330 Hz)
addi $t0, $0, 330
sw $t0, -128($0)
addi $t1, $0, 100
delay_e:
    addi $t1, $t1, -1
    bne $t1, $0, delay_e

# F note (349 Hz)
addi $t0, $0, 349
sw $t0, -128($0)
addi $t1, $0, 100
delay_f:
    addi $t1, $t1, -1
    bne $t1, $0, delay_f

# G note (392 Hz)
addi $t0, $0, 392
sw $t0, -128($0)
addi $t1, $0, 100
delay_g:
    addi $t1, $t1, -1
    bne $t1, $0, delay_g

# A note (440 Hz)
addi $t0, $0, 440
sw $t0, -128($0)
addi $t1, $0, 100
delay_a:
    addi $t1, $t1, -1
    bne $t1, $0, delay_a

# B note (494 Hz)
addi $t0, $0, 494
sw $t0, -128($0)
addi $t1, $0, 100
delay_b:
    addi $t1, $t1, -1
    bne $t1, $0, delay_b

# High C note (523 Hz)
addi $t0, $0, 523
sw $t0, -128($0)
addi $t1, $0, 100
delay_hc:
    addi $t1, $t1, -1
    bne $t1, $0, delay_hc

# Turn sound OFF
sw $0, -120($0)

done:
    j done