@Assembly code to set x22 if 2<5
.main:
    addi x20, x0, 2
    addi x21, x0, 5
    slt x22, x20, x21
    .print x22
end