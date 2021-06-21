@ RISC V assembly code to find ~(AVB) where A=0 & B=1
.main:
addi x5, x0, 0
ori x1, x5, 1
sub x5, x0, x1
    .print x5
end
