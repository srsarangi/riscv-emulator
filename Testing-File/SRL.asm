@Assembly code to perform -30>>>2
.main:
    addi x20, x0, -30
    addi x21, x0, 2
    srl x22, x20, x21
    .print x22
end