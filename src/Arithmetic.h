#include<stdio.h>
#include <string.h>
extern long long xreg[32];
extern int isImm;
extern long long xd, x1, x2, imm;
void ADD(char *inst, int i)
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]+xreg[x2];
}
void ADDI(char *inst, int i)
{
    getReg3Add(inst, i);
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]+imm;
}
void SUB(char *inst, int i)
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]-xreg[x2];
}
void MUL(char *inst, int i)
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]*xreg[x2];
}
void MULI(char *inst, int i)
{
    getReg3Add(inst, i);
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]*imm;
}