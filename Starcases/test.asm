.data
.text

li $t0, 12345
# move $t2, $t0
addi $t0, $0, 5
addi $t1, $0, 5
and $t2, $t0, $t1
or $t2, $t0, $t1
nor $t2, $t0, $t1
xor $t2, $t0, $t1
andi $t2, $t0, 3
ori $t2, $t0, 3
xori $t2, $t0, 3
lui $t2, 3

addi $v0, $0, 10
syscall