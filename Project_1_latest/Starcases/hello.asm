.data
my_num: .word 301 1 2
hello: .asciiz "Hello, world!"
zeros: .asciiz "000000000"
.text

addi $v0, $0, 4 # code for print string
la $a0, hello
syscall

# la $t0, my_num
lw $a0, 0($t0)
addi $v0, $0, 1
syscall

lw $a0, 4($t0)
syscall

addi $v0, $0, 10
syscall