.main:
    addi x20, x0, 5
    addi x21, x0, 5
    sd x21, 6(x20)
    ld x5, 6(x20)
    .print x5
end