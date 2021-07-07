#ifndef COMPARE_H
#define COMPARE_H

extern void SLT(char *inst, int i); // function to set if less than (two source register)
extern void SLTI(char *inst, int i);  // function to set if less than (one source register one immediate)
extern void SLTU(char *inst, int i); // function to set if less than unsigned (two source registers)
extern void SLTIU(char *inst, int i);   // function to set if less than unsigned (one source register and immediate)

# endif
