#include<stdio.h>
extern long long xreg[32];
extern int isImm;
extern long long xd, x1, x2, imm;
void SLL(char *inst, int i)
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
    xreg[xd] = xreg[x1]<<xreg[x2];
}
void SLLI(char *inst, int i)
{
    getReg3Add(inst, i);
	if(!isImm)
	invalidInst();
	else
    xreg[xd] = xreg[x1]<<imm;
}
void SRA(char *inst, int i)
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
    xreg[xd] = xreg[x1]>>xreg[x2];
}
void SRAI(char *inst, int i)
{
    getReg3Add(inst, i);
	if(!isImm)
	invalidInst();
	else
    xreg[xd] = xreg[x1]>>imm;
}
void SRL(char *inst, int i)
{
    getReg3Add(inst, i);
	if(isImm)
	invalidInst();
	else
    {
        unsigned long long b;
		b = (unsigned long long)xreg[x1];
	    xreg[xd] = b >> xreg[x2];
    }
}
void SRLI(char *inst, int i)
{
    getReg3Add(inst, i);
	if(!isImm)
	invalidInst();
	else
    {
		unsigned long long b;
		b = (unsigned long long)xreg[x1];
		xreg[xd] = b >> imm;
    }
}
void SLT(char *inst, int i)
{
     getReg3Add(inst, i);
	if (isImm)
		invalidInst();
	else
	{
	  if (xreg[x1] < xreg[x2])
	   xreg[xd] = 1;
	   else
	   xreg[xd]=0;
   }
}
void SLTI(char *inst, int i)
{
     getReg3Add(inst, i);
	if (!isImm)
		invalidInst();
	else
	{
	  if (xreg[x1] < imm)
	   xreg[xd] = 1;
	   else
	   xreg[xd]=0;
   }
}
void SLTU(char *inst, int i)
{
	getReg3Add(inst, i);
	if (isImm)
		invalidInst();
	else
	{
		   if ((unsigned long long)xreg[x1] < (unsigned long long)xreg[x2])
			   xreg[xd] = 1;
		   else
			   xreg[xd]=0;
	}
}
void SLTIU(char *inst, int i)
{
    getReg3Add(inst, i);
	if (!isImm)
		invalidInst();
	else
	{
		if ((unsigned long long)xreg[x1] < (unsigned long long)imm)
			xreg[xd] = 1;
		else
			xreg[xd]=0;
	}
}