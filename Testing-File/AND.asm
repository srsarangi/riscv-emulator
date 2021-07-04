@Assembly code to perform 5&3
.main:
    addi x20, x0, 5
    addi x21, x0, 3
    and x21, x20, x21
    .print x21
end