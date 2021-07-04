@ Assembly code to perform 300/100
.main:
	addi x20, x0, 300
	addi x21, x0, 100
    div x22, x20, x21
    .print x22
end