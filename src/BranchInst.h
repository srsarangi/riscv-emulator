#ifndef BRANCHINST_C
#define BRANCHINST_C

extern int getPcForLabel(char* str, int i, int j);
extern void BEQ(char *inst, int i); // function that sets pc to specified label if content of both source register is equal
extern void BGE(char *inst, int i); // function that sets pc to specified label if greater than or equal
extern void BGEU(char *inst, int i); // function that sets pc to specified label if greater than or equal unsigned
extern void BNE(char *inst, int i);// function that sets pc to specified label if content of both register is not equal
extern void BLT(char *inst, int i); // function that sets pc to specified label if less than
extern void BLTU(char *inst, int i); // function that sets pc to specified label if less than unsigned
extern void JAL(char *inst, int i);  // unconditional jump jal
extern void JALR(char *inst, int i); 

# endif
