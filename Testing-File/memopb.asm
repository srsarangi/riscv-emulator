.main:
    addi x20, x0, 5
    addi x21, x0, 5
    sb x21, 6(x20)
    lb x5, 6(x20)
    .print x5
end