.main:
addi x1, x0, 50
addi x2, x2, 1
loop:
.print x1
subi x1, x1, 1
bne x1, x2, .loop
end