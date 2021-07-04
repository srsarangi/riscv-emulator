@Assembly code to perform 4|1
.main:
    addi x20, x0, 4
    addi x21, x0, 1
    or x22, x20, x21
    .print x22
end