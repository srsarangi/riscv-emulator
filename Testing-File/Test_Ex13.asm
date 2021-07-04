@Assembly code to print factorial of 12
.main:
addi x1, x0, 1
addi x2, x0, 12
addi x3, x0, 1
.loop:
	mul x1, x1, x2
	addi x2, x2, -1
	blt x3, x2, .loop
    .print x1
end