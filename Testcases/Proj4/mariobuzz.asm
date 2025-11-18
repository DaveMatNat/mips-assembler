# Super Mario Bros Theme Song (4x Speed)
addi $sp, $0, -4096      # Initialize stack pointer

# Set volume
addi $t0, $0, 80
sw $t0, -124($0)         # Volume = 80

# Turn sound ON
sw $0, -120($0)

# ===== MAIN MELODY =====
# Measure 1: E E - E - C E - G
# E (659 Hz) - eighth note
addi $t0, $0, 659
sw $t0, -128($0)
addi $t1, $0, 128
delay1:
    addi $t1, $t1, -1
    bne $t1, $0, delay1

# E (659 Hz) - eighth note
addi $t0, $0, 659
sw $t0, -128($0)
addi $t1, $0, 128
delay2:
    addi $t1, $t1, -1
    bne $t1, $0, delay2

# Rest - eighth note
sw $0, -120($0)          # Sound off
addi $t1, $0, 128
delay3:
    addi $t1, $t1, -1
    bne $t1, $0, delay3
sw $0, -120($0)          # Sound on

# E (659 Hz) - eighth note
addi $t0, $0, 659
sw $t0, -128($0)
addi $t1, $0, 128
delay4:
    addi $t1, $t1, -1
    bne $t1, $0, delay4

# Rest - eighth note
sw $0, -120($0)          # Sound off
addi $t1, $0, 128
delay5:
    addi $t1, $t1, -1
    bne $t1, $0, delay5
sw $0, -120($0)          # Sound on

# C (523 Hz) - eighth note
addi $t0, $0, 523
sw $t0, -128($0)
addi $t1, $0, 128
delay6:
    addi $t1, $t1, -1
    bne $t1, $0, delay6

# E (659 Hz) - quarter note
addi $t0, $0, 659
sw $t0, -128($0)
addi $t1, $0, 256
delay7:
    addi $t1, $t1, -1
    bne $t1, $0, delay7

# G (784 Hz) - quarter note
addi $t0, $0, 784
sw $t0, -128($0)
addi $t1, $0, 256
delay8:
    addi $t1, $t1, -1
    bne $t1, $0, delay8

# Rest - quarter note
sw $0, -120($0)          # Sound off
addi $t1, $0, 256
delay9:
    addi $t1, $t1, -1
    bne $t1, $0, delay9
sw $0, -120($0)          # Sound on

# G (392 Hz) - quarter note (low G)
addi $t0, $0, 392
sw $t0, -128($0)
addi $t1, $0, 256
delay10:
    addi $t1, $t1, -1
    bne $t1, $0, delay10

# Rest - quarter note
sw $0, -120($0)          # Sound off
addi $t1, $0, 256
delay11:
    addi $t1, $t1, -1
    bne $t1, $0, delay11
sw $0, -120($0)          # Sound on

# ===== Measure 2: C - - G - - E =====
# C (523 Hz) - quarter note
addi $t0, $0, 523
sw $t0, -128($0)
addi $t1, $0, 256
delay12:
    addi $t1, $t1, -1
    bne $t1, $0, delay12

# Rest - eighth note
sw $0, -120($0)          # Sound off
addi $t1, $0, 128
delay13:
    addi $t1, $t1, -1
    bne $t1, $0, delay13
sw $0, -120($0)          # Sound on

# G (392 Hz) - quarter note
addi $t0, $0, 392
sw $t0, -128($0)
addi $t1, $0, 256
delay14:
    addi $t1, $t1, -1
    bne $t1, $0, delay14

# Rest - eighth note
sw $0, -120($0)          # Sound off
addi $t1, $0, 128
delay15:
    addi $t1, $t1, -1
    bne $t1, $0, delay15
sw $0, -120($0)          # Sound on

# E (330 Hz) - quarter note
addi $t0, $0, 330
sw $t0, -128($0)
addi $t1, $0, 256
delay16:
    addi $t1, $t1, -1
    bne $t1, $0, delay16

# Rest - eighth note
sw $0, -120($0)          # Sound off
addi $t1, $0, 128
delay17:
    addi $t1, $t1, -1
    bne $t1, $0, delay17
sw $0, -120($0)          # Sound on

# ===== Measure 3: A - B - A# A =====
# A (440 Hz) - quarter note
addi $t0, $0, 440
sw $t0, -128($0)
addi $t1, $0, 256
delay18:
    addi $t1, $t1, -1
    bne $t1, $0, delay18

# B (494 Hz) - quarter note
addi $t0, $0, 494
sw $t0, -128($0)
addi $t1, $0, 256
delay19:
    addi $t1, $t1, -1
    bne $t1, $0, delay19

# A# (466 Hz) - quarter note
addi $t0, $0, 466
sw $t0, -128($0)
addi $t1, $0, 256
delay20:
    addi $t1, $t1, -1
    bne $t1, $0, delay20

# A (440 Hz) - quarter note
addi $t0, $0, 440
sw $t0, -128($0)
addi $t1, $0, 256
delay21:
    addi $t1, $t1, -1
    bne $t1, $0, delay21

# ===== Measure 4: G E G A - F G =====
# G (392 Hz) - dotted eighth note
addi $t0, $0, 392
sw $t0, -128($0)
addi $t1, $0, 192
delay22:
    addi $t1, $t1, -1
    bne $t1, $0, delay22

# E (659 Hz) - dotted eighth note
addi $t0, $0, 659
sw $t0, -128($0)
addi $t1, $0, 192
delay23:
    addi $t1, $t1, -1
    bne $t1, $0, delay23

# G (784 Hz) - dotted eighth note
addi $t0, $0, 784
sw $t0, -128($0)
addi $t1, $0, 192
delay24:
    addi $t1, $t1, -1
    bne $t1, $0, delay24

# A (880 Hz) - quarter note
addi $t0, $0, 880
sw $t0, -128($0)
addi $t1, $0, 256
delay25:
    addi $t1, $t1, -1
    bne $t1, $0, delay25

# F (698 Hz) - eighth note
addi $t0, $0, 698
sw $t0, -128($0)
addi $t1, $0, 128
delay26:
    addi $t1, $t1, -1
    bne $t1, $0, delay26

# G (784 Hz) - quarter note
addi $t0, $0, 784
sw $t0, -128($0)
addi $t1, $0, 256
delay27:
    addi $t1, $t1, -1
    bne $t1, $0, delay27

# Rest - eighth note
sw $0, -120($0)          # Sound off
addi $t1, $0, 128
delay28:
    addi $t1, $t1, -1
    bne $t1, $0, delay28
sw $0, -120($0)          # Sound on

# ===== Measure 5: E - C - D B =====
# E (659 Hz) - quarter note
addi $t0, $0, 659
sw $t0, -128($0)
addi $t1, $0, 256
delay29:
    addi $t1, $t1, -1
    bne $t1, $0, delay29

# C (523 Hz) - dotted eighth note
addi $t0, $0, 523
sw $t0, -128($0)
addi $t1, $0, 192
delay30:
    addi $t1, $t1, -1
    bne $t1, $0, delay30

# D (587 Hz) - eighth note
addi $t0, $0, 587
sw $t0, -128($0)
addi $t1, $0, 128
delay31:
    addi $t1, $t1, -1
    bne $t1, $0, delay31

# B (494 Hz) - dotted quarter note
addi $t0, $0, 494
sw $t0, -128($0)
addi $t1, $0, 384
delay32:
    addi $t1, $t1, -1
    bne $t1, $0, delay32

# Turn sound OFF
sw $0, -120($0)

done:
    j done