@ Assembly code to perform 40*50
.main:
	addi x20, x0, 40
	addi x21, x0, 50
    mul x22, x20, x21
    .print x22
end