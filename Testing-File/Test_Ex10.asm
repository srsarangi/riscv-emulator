.main:
addi x6, x0, 100
addi x7, x0, 1
add x10, x0, sp
.loop1:
addi x8, x0, 10
sb x8, 0(sp)
addi sp, sp, 1
addi x7, x7, 1
bge x6, x7, .loop1
addi x9, x0, 0
.loop2:
lb x8, 0(x10)
add x9, x9, x8
addi x10, x10, 1
bge sp, x10, .loop2
    .print x9
end