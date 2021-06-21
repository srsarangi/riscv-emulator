#include<stdio.h>
extern long long xreg[32];
extern int isImm;
extern long long xd, x1, x2, imm;
void XOR(char *inst, int i)  // Arguments:(instruction, index) | function to perform xor operation on content of both source register
{
    getReg3Add(inst, i);  // calls getReg3Add() that is defined in Register.h
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]^xreg[x2];
}
void XORI(char *inst, int i) // Arguments:(instruction, index) | function to perform xor operation on content of rs1 and immediate
{
    getReg3Add(inst, i); // calls getReg3Add() that is defined in Register.h
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]^imm;
}
void OR(char *inst, int i) // Arguments:(instruction, index) | function to perform or operation on content of both source register
{
    getReg3Add(inst, i); // calls getReg3Add() that is defined in Register.h
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]|xreg[x2];
}
void ORI(char *inst, int i) // Arguments:(instruction, index) | function to perform xor operation on content of rs1 and immediate
{
    getReg3Add(inst, i); // calls getReg3Add() that is defined in Register.h
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]|imm;
}
void AND(char *inst, int i) //Arguments:(instruction, index) | function to perform and operation on content of both source register
{
    getReg3Add(inst, i); // calls getReg3Add() that is defined in Register.h
	if(isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]&xreg[x2];
}
void ANDI(char *inst, int i) // Arguments:(instruction, index) | function to perform xor operation on content of rs1 and immediate
{
    getReg3Add(inst, i);  // calls getReg3Add() that is defined in Register.h
	if(!isImm)
	invalidInst();
	else
	xreg[xd] = xreg[x1]&imm;
}
