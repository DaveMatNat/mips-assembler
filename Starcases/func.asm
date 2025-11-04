main:
        addi   $t0, $0, 3            # input value
        jal  double_number     # call function (return addr goes to $ra)
        sw   $t1, 0($0)       # store the result from $t1

end: 
    j end               # no syscalls; stop here (tight loop)

# double_number: doubles value in $t0, writes result to $t1
double_number:
        sll  $t1, $t0, 1       # $t1 = $t0 * 2 (shift left by 1)
        jr   $ra               # return