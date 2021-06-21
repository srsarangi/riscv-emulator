#include<stdio.h>
#include <string.h>
extern long long xreg[32];
extern int isImm;
extern long long xd, x1, x2, imm;
void ADD(char *inst, int i)  //Arguments:(instruction, index) | function that perform addition on content of two register and stores in destinstion register
{
    getReg3Add(inst, i);  // calls getReg3Add() function that is present in Register.h header file
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]+xreg[x2];
}
void ADDI(char *inst, int i) // Arguments:(instruction, index) | function that perform addition on content of first source register and immediate and stores in destinstion register
{
    getReg3Add(inst, i);  // calls getReg3Add() function that is present in Register.h header file
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]+imm;
}
void SUB(char *inst, int i) //Arguments:(instruction, index) | function that perform substraction on content of two register and stores in destinstion register
{
    getReg3Add(inst, i); // calls getReg3Add() function that is present in Register.h header file
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]-xreg[x2];
}
void MUL(char *inst, int i)  // Arguments:(instruction, index) |function that perform multiplication on content of two source registers and stores in destinstion register
{
    getReg3Add(inst, i);  //calls getReg3Add() function that is present in Register.h header file
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]*xreg[x2];
}
void MULI(char *inst, int i) // Arguments:(instruction, index) | function that perform multiplication on content of first source register and immediate and stores in destinstion register
{
    getReg3Add(inst, i); // calls getReg3Add() function that is present in Register.h header file
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]*imm;
}
