
.main
    addi x1, x0, 1
    addi x2, x0, 102
    .loop:
        mul x1, x1, x2
        subi x2, x2, 1
        bgt x2, 1, .loop
    .print x2
end