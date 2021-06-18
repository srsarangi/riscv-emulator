.power:
addi x12, x0, 1
addi x5, x0, 1
beq x11, x0, .ret
.loop:
mul x12, x12, x10
addi x5, x5, 1
bge x11, x5, .loop
.main:
addi x10, x0, 5
addi x11, x0, 3
jal x1, .power
.ret:
    .print x12
end