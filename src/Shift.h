#ifndef SHIFT_H
#define SHIFT_H
extern void SLL(char *inst, int i);  // function to perform left shifting (two source register)
extern void SLLI(char *inst, int i); // function to perform left shifting (one source register one immediate)
extern void SRA(char *inst, int i); // function to perform arithmetic right shifting (two source register)
extern void SRAI(char *inst, int i);  // function to perform arithmetic right shifting (one source register one immediate)
extern void SRL(char *inst, int i);  // function to perform logical right shifting (two source register)
extern void SRLI(char *inst, int i); // function to logical right shifting (one source register one immediate)
extern void SLLW(char *inst, int i);  // function to perform left shifting (two source register) on only 32-bit values
extern void SLLIW(char *inst, int i); // function to perform left shifting (one source register one immediate) on only 32-bit values
extern void SRAW(char *inst, int i); // function to perform arithmetic right shifting (two source register) on only 32-bit values
extern void SRAIW(char *inst, int i);  // function to perform arithmetic right shifting (one source register one immediate) on only 32-bit values
extern void SRLW(char *inst, int i); // function to perform logical right shifting (two source register) on only 32-bit values
extern void SRLIW(char *inst, int i); // function to logical right shifting (one source register one immediate) on only 32-bit valus

#endif
