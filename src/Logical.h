#include<stdio.h>
extern long long xreg[32];
extern int isImm;
extern int xd, x1, x2, imm;
void XOR(char *inst, int i)  // function to perform xor operation on content of both source register
{
    Rtype(inst, i);  // calls Rtype() that is defined in Register.h
	xreg[xd] = xreg[x1]^xreg[x2];
}
void XORI(char *inst, int i) // function to perform xor operation on content of rs1 and immediate
{
    Itype(inst, i); // calls Itype() that is defined in Register.h
	xreg[xd] = xreg[x1]^imm;
}
void OR(char *inst, int i) // function to perform or operation on content of both source register
{
    Rtype(inst, i); // calls Rtype() that is defined in Register.h
	xreg[xd] = xreg[x1]|xreg[x2];
}
void ORI(char *inst, int i) // function to perform xor operation on content of rs1 and immediate
{
    Itype(inst, i); // calls Itype() that is defined in Register.h
	xreg[xd] = xreg[x1]|imm;
}
void AND(char *inst, int i) // // function to perform and operation on content of both source register
{
    Rtype(inst, i); // calls Rtype() that is defined in Register.h
	xreg[xd] = xreg[x1]&xreg[x2];
}
void ANDI(char *inst, int i) // function to perform xor operation on content of rs1 and immediate
{
    Itype(inst, i);  // calls Itype() that is defined in Register.h
	xreg[xd] = xreg[x1]&imm;
}