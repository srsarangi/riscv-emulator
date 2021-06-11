.main:
    mv x0, 8
    mv x20, 10
	ori x18, x0, 16
    addi x20, x18, 0
    .print x20
    .if:
		  addi x3,x3,1
    beq x20,x18 .if
    add x20, x20, x20
    .print x20
end