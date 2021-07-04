@ RISC-V assembly code to return 1 if number is perfect square
.main:
addi x7, x0, 16
addi x5, x0, 0
addi x6, x0, 1
.loop:
   mul x4, x6, x6
   beq x7, x4, .square
   addi x6, x6, 1
   blt x7, x4, .exit
   blt x4, x7, .loop
.square:
   addi x5, x0, 1
.exit:
    .print x5
end
