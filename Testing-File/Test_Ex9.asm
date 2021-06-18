.main:
addi x5, x0, 31
addi x9, x0, 64
addi x10, x0, 1
addi x6, x0, 1
addi x7, x0, 0
.loop:
andi x8, x5, 1
bne x8, x10, .increment
addi x7, x7, 1
.increment:
srli x5, x5, 1
addi x6, x6, 1
bge x9, x6, .loop
    .print x7
end