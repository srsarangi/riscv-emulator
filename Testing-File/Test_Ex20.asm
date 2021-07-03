.main:
addi x1, x0, 7
addi x2, x0, 5
add x3, x0, x1
add x1, x0, x2
add x2, x1, x3
sub x2, x2, x1
.print x1
.print x2 
end