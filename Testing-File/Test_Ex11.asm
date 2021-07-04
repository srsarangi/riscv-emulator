@ RISC-V assembly code to define a function to calculate exponent
.power:
addi x12, x0, 1
add x5, x0, x11
beq x11, x0, .ret
.loop:
mul x12, x12, x10
addi x5, x5, -1
bne x5, x0, .loop
jalr x0, 0(x1)
.main:
addi x10, x0, 5
addi x11, x0, 3
jal x1, .power
.ret:
    .print x12
end
