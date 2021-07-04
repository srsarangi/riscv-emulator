@Assembly program to print sum upto 15 natural numbers
.main:
addi x1, x0, 1
addi x4, x0, 15
loop:
add x3, x3, x1
addi x1, x1, 1
bge x4, x1, loop
.print x3 
end