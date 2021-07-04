.main:
        lui  x20, 100
	addi x20, x20, 300
        lui x21, 100
	addi x21, x21, 200
    add x22, x20, x21
    .print x22
end