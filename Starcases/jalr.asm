.data
func: .word double_number
.text

main:
        addi   $t0, $0, 3            # input value
        la     $t2, func    # load address of function into $t2
        jalr   $t2, $s0              # jump to double_number, save return addr in $ra
        sw     $t1, 0($0)            # store the result from $t1

end: 
        j end                        # infinite loop (halt)

# double_number: doubles value in $t0, writes result to $t1
double_number:
        sll    $t1, $t0, 1           # $t1 = $t0 * 2 (shift left by 1)
        jr     $s0                   # return