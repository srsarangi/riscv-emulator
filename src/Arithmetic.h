#ifndef ARITHMETIC_H
#define ARITHMETIC_H
extern void ADD(char *inst, int i);
extern void ADDI(char *inst, int i); // function that perform addition on content of first source register and immediate and stores in destinstion register
extern void SUB(char *inst, int i); //function that perform substraction on content of two register and stores in destinstination register
extern void MUL(char *inst, int i);  //function that perform multiplication on content of two source registers and stores in destinstion register
extern void MULH(char *inst, int i);  //function that perform multiplication on content of two source registers and stores upper 64-bits in destinstion register
extern void MULHU(char *inst, int i);  //function that perform multiplication on unsigned content of two source registers and stores upper 64-bits in destinstion register
extern void MULHSU(char *inst, int i);  //function that perform multiplication on content of two source registers and stores upper 64-bit in destinstion register
extern void DIV(char *inst, int i);  //function that perform division on content of two source registers and stores in destinstion register
extern void DIVU(char *inst, int i); //function that perform division on unsigned content of two source registers and stores in destinstion register
extern void REM(char *inst, int i);  //function that provide remainder
extern void REMU(char *inst, int i);  //function that provide remainder for unsigned division
extern void ADDW(char *inst, int i);  // function that perform addition on content of two register and stores in destinstion register : only on lower 32-bits
extern void ADDIW(char *inst, int i); // function that perform addition on content of first source register and immediate and stores in destinstion register : only on lower 32-bits
extern void SUBW(char *inst, int i); //function that perform substraction on content of two register and stores in destinstion register : only on lower 32-bits
extern void MULW(char *inst, int i);  //function that perform multiplication on content of two source registers and stores in destinstion register : only on lower 32-bits
extern void DIVW(char *inst, int i);  //function that perform division for lower 32-bit
extern void DIVUW(char *inst, int i);  //function that perform division for unsigned lower 32-bit
extern void REMW(char *inst, int i);  //function that provide remainder for lower 32-bit
extern void REMUW(char *inst, int i);  //function that provides remainder for unsigned lower 32-bit
extern void LUI(char *inst, int i);
#endif
