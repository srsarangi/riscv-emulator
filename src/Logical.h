#include<stdio.h>
extern long long xreg[32]; // used to store values of all 32 registers
extern int isImm;  // Check the persence of Immediate
extern long long xd, x1, x2, imm; // Distination,sources and immediate value.
void XOR(char *inst, int i) // XOR 
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]^xreg[x2];
}
void XORI(char *inst, int i) // XORI
{
    getReg3Add(inst, i);
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]^imm;
}
void OR(char *inst, int i) // OR
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]|xreg[x2];
}
void ORI(char *inst, int i) // ORI
{
    getReg3Add(inst, i);
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]|imm;
}
void AND(char *inst, int i) // AND
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]&xreg[x2];
}
void ANDI(char *inst, int i) // ANDI
{
    getReg3Add(inst, i);
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]&imm;
}
