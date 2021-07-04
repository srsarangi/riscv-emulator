@Assembly code to print numbers from 2 to 20
.main:
addi x1, x0, 1
addi x2, x0, 1
addi x4, x0, 20
loop:
add x3, x1, x2
.print x3
addi x2, x2, 1
bne x2, x4, loop
end