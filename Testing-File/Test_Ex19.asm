.main:
addi x1, x0, 1
addi x2, x0, 11
loop:
mul x3, x1, x1
mul x3, x3, x1
.print x3
addi x1, x1, 1
bne x1, x2, loop
end