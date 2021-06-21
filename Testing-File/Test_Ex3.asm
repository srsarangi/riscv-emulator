@ RISC-V assembly code to find 12^3 +1
.main:
addi x5, x0, 12
mul x6, x5, x5
mul x6, x6, x5
addi x6, x6, 1 
    .print x6
end
