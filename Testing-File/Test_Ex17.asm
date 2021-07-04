@Assembly code to print numbers from 1 to 50
.main:
addi x1, x0, 50
addi x2, x0, 1
.loop:
.print x2
addi x2, x2, 1
bge x1, x2, .loop
end