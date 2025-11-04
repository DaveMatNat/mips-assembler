.data
.text
main:
    addi $t1, $zero, 1
    addi $t2, $zero, 10
initloop:
    addi $t1, $t1, 1
    bne $t1, $t2, initloop

# .data
# .text
# main:
#     addi $t1, $zero, 1
#     addi $t2, $zero, 1
# initloop:
#     addi $t3, $zero, 1
#     beq $t1, $t2, initloop