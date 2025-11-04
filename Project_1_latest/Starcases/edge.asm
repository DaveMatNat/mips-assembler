.text
a:
    addi $v0, $0, 4
    blt $t0, $t1, c
b:
    sub $a0, $a1, $0
c:
    j b
