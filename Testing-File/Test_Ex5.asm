@ RISC-V assembly code to perform 25<<2+10
.main:
addi x5, x0, 25
slli x5, x5, 2
addi x6, x0, 10
add x6, x5, x6
    .print x6
end
