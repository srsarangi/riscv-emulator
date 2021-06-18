.foo:
   addi x5, x0, 2
   jalr x0, 0(x1)
.main:
   addi x6, x0, 3
   jal x1, .foo
 add x7, x5, x6
    .print x7
end