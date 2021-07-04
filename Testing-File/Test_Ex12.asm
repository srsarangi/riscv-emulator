@Assembly code to perform 31*29-50
.main:
     addi x1, x0, 31
     addi x2, x0, 29
     mul x3, x1, x2
     addi x3, x3, -50
	.print x3
end