@Assembly program to print 10 multiples of 5
.main:
addi x1, x0, 5
addi x2, x0, 1
addi x3, x0, 11
loop:
mul x4, x1, x2
.print x4
addi x2, x2, 1
bne x2, x3, loop
end