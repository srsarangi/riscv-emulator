#ifndef EXECUTION_H
#define EXECUTION_H
extern void PRINT(char *inst, int i); // extract index of specified register and  prints value stored in them
extern void executeInstruction(void); // function to execute instruction of specified pc. it takes beginning and ending index of instruction as arguments.
#endif
