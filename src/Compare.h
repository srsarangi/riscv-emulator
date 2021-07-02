#include<stdio.h>
extern long long xreg[32];
extern int isImm;
extern int xd, x1, x2, imm;
void SLT(char *inst, int i) // function to set if less than (two source register)
{
      Rtype(inst, i);  // calls Rtype() that is defined in Register.h
	  if (xreg[x1] < xreg[x2])
	   xreg[xd] = 1;
	   else
	   xreg[xd]=0;
}
void SLTI(char *inst, int i)  // function to set if less than (one source register one immediate)
{
      Itype(inst, i);  // calls Itype() that is defined in Register.h
	  if (xreg[x1] < imm)
	   xreg[xd] = 1;
	   else
	   xreg[xd]=0;
}
void SLTU(char *inst, int i) // function to set if less than unsigned (two source register)
{
	Rtype(inst, i);  // calls Rtype() that is defined in Register.h
	if ((unsigned long long)xreg[x1] < (unsigned long long)xreg[x2])
	   xreg[xd] = 1;
	else
		xreg[xd]=0;
}
void SLTIU(char *inst, int i)   // function to set if less than unsigned (one source register and immediate)
{
    Itype(inst, i);  // calls Itype() that is defined in Register.h
	if ((unsigned long long)xreg[x1] < (unsigned long long)imm)
		xreg[xd] = 1;
	else
		xreg[xd]=0;
}