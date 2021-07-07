#ifndef DATATRANSFER_H
#define DATATRANSFER_H
extern void STOREB(char *inst, int i); // function to store byte in memory
extern void STOREH(char *inst, int i); // function to store halfword in memory
extern void STOREW(char *inst, int i);// function to store word in memory
extern void STORED(char *inst, int i); // function to store doubleword in memory
extern void LOADB(char *inst, int i);  // function to loab byte from memory to register		
extern void LOADH(char *inst, int i);  // function to loab halfword from memory to register
extern void LOADW(char *inst, int i);  // function to loab word from memory to register
extern void LOADD(char *inst, int i); // function to loab doubleword from memory to register
extern void LOADBU(char *inst, int i); // function to loab unsigned byte from memory to register
extern void LOADHU(char *inst, int i);  // function to loab unsigned halfword from memory to register
extern void LOADWU(char *inst, int i); // function to loab unsigned word from memory to register
# endif
