.main:
    addi x20, x0, 5
    addi x21, x0, 5
    sw x21, 6(x20)
    lw x5, 6(x20)
    .print x5
end