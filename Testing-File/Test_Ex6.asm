.main:
addi x7, x0, 5
addi x5, x0, 1
addi x6, x0, 1
loop:
mul x5, x6, x5
addi x6, x6, 1
bge x7, x6, loop
    .print x5
end