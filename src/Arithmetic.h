#include<stdio.h>
#include <string.h>
extern long long xreg[32]; // This will store the value of all 32 registers.
extern int isImm; // This is used to check the persence of immediate Values.
extern long long xd, x1, x2, imm; // distination,source1,source2,immediate.
void ADD(char *inst, int i) // Arithematic Add operation.
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]+xreg[x2];
}
void ADDI(char *inst, int i) // Arithematic Add Operation with Immediate
{
    getReg3Add(inst, i);
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]+imm;
}
void SUB(char *inst, int i) // Arithematic Subtract Operation
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]-xreg[x2];
}
void MUL(char *inst, int i) // Arithematic Multiple Operation
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]*xreg[x2];
}
void MULI(char *inst, int i) // Arithematic Multiple Operation with immediate.
{
    getReg3Add(inst, i);
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]*imm;
}
