#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
extern long long xreg[32];
extern int isImm;
extern long long xd, x1, x2, imm;
extern int pc;
extern char* str;
extern int b;
int getRegBranch(char *inst, int i)
{
    //code to extract register number of rs1
    if(inst[i] == 's' && inst[i+1] == 'p')
	{
		x1 = 2;
		i += 2;
	}
	else
	{
	    if(inst[i] != 'x')
		invalidInst();
		++i;
		if(isdigit(inst[i]))
		{
		    x1 = inst[i] - '0';
			++i;
			if(isdigit(inst[i]))
			{
				x1 = x1*10 + (inst[i] - '0');
				++i;
			}
		}
		else
		invalidInst();
		}
		if(x1 < 0 || x1 > 31)
		invalidInst();


		//Code to extract register number of rs2
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
	if(inst[i] != ',')
		invalidInst();
	++i;
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
	if(inst[i] == 's' && inst[i+1] == 'p')
	{
		x2 = 2;
		i += 2;
	}
    else 
	{
		if(inst[i] != 'x')
		invalidInst();
		++i;
	    if(isdigit(inst[i]))
	    {
		    x2 = inst[i] - '0';
		    ++i;
		    if(isdigit(inst[i]))
			{
			    x2 = x2*10 + (inst[i] - '0');
				++i;
			}
		}
	else
	invalidInst();
	}
	if(x2 < 0 || x2 > 31)
	invalidInst();
	return i;
}
void BEQ(char *inst, int i)
{
	 i=getRegBranch(inst,i);
    while(inst[i]==' '||inst[i]=='\t')
	++i;
	if(inst[i]!=',')
	invalidInst();
	i++;
	while(inst[i]==' '||inst[i]=='\t')
	++i;
    if(xreg[x1]==xreg[x2])
    {
	if(isdigit(inst[i]))
	{
		int d;
		d=inst[i]-'0';
		i++;
		while(isdigit(inst[i]))
		{
			d=d*10+inst[i]-'0';
			i++;
		}
		pc=pc+d/4;
	}
    else
	{
		int label_init = i;
	    while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
	    ++i;
	    pc = getPcForLabel(str, b+label_init, b+i) - 1; 
    }
	}
}
void BGE(char *inst, int i)
{
    i=getRegBranch(inst,i);
    while(inst[i]==' '||inst[i]=='\t')
	++i;
	if(inst[i]!=',')
	invalidInst();
	i++;
	while(inst[i]==' '||inst[i]=='\t')
	++i;
    if(xreg[x1]>=xreg[x2])
    {
	if(isdigit(inst[i]))
	{
		int d;
		d=inst[i]-'0';
		i++;
		while(isdigit(inst[i]))
		{
			d=d*10+inst[i]-'0';
			i++;
		}
		pc=pc+d/4;
	}
    else
	{
		int label_init = i;
	    while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
	    ++i;
	    pc = getPcForLabel(str, b+label_init, b+i) - 1; 
    }
	}
}
void BGEU(char *inst, int i)
{
    i=getRegBranch(inst,i);
	while(inst[i]==' '||inst[i]=='\t')
	++i;
	if(inst[i]!=',')
	invalidInst();
	i++;
	while(inst[i]==' '||inst[i]=='\t')
	++i;
    if((unsigned)xreg[x1]>=(unsigned)xreg[x2])
    {
	if(isdigit(inst[i]))
	{
		int d;
		d=inst[i]-'0';
		i++;
		while(isdigit(inst[i]))
		{
			d=d*10+inst[i]-'0';
			i++;
		}
		pc=pc+d/4;
	}
    else
	{
		int label_init = i;
	    while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
	    ++i;
	    pc = getPcForLabel(str, b+label_init, b+i) - 1; 
    }
	}
}
void BNE(char *inst, int i)
{
    i=getRegBranch(inst,i);
	while(inst[i]==' '||inst[i]=='\t')
	++i;
	if(inst[i]!=',')
	invalidInst();
	i++;
	while(inst[i]==' '||inst[i]=='\t')
	++i;
    if(xreg[x1]!=xreg[x2])
    {
	if(isdigit(inst[i]))
	{
		int d;
		d=inst[i]-'0';
		i++;
		while(isdigit(inst[i]))
		{
			d=d*10+inst[i]-'0';
			i++;
		}
		pc=pc+d/4;
	}
    else
	{
		int label_init = i;
	    while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
	    ++i;
	    pc = getPcForLabel(str, b+label_init, b+i) - 1; 
    }
	}
}
void BLT(char *inst, int i)
{
    i=getRegBranch(inst,i);
	while(inst[i]==' '||inst[i]=='\t')
	++i;
	if(inst[i]!=',')
	invalidInst();
	i++;
	while(inst[i]==' '||inst[i]=='\t')
	++i;
    if(xreg[x1]<xreg[x2])
    {
	if(isdigit(inst[i]))
	{
		int d;
		d=inst[i]-'0';
		i++;
		while(isdigit(inst[i]))
		{
			d=d*10+inst[i]-'0';
			i++;
		}
		pc=pc+d/4;
	}
    else
	{
		int label_init = i;
	    while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
	    ++i;
	    pc = getPcForLabel(str, b+label_init, b+i) -1;
	}
	}
}
void BLTU(char *inst, int i)
{
    i=getRegBranch(inst,i);
	while(inst[i]==' '||inst[i]=='\t')
	++i;
	if(inst[i]!=',')
	invalidInst();
	i++;
	while(inst[i]==' '||inst[i]=='\t')
	++i;
    if((unsigned)xreg[x1]<(unsigned)xreg[x2])
    {
	if(isdigit(inst[i]))
	{
		int d;
		d=inst[i]-'0';
		i++;
		while(isdigit(inst[i]))
		{
			d=d*10+inst[i]-'0';
			i++;
		}
		pc=pc+d/4;
	}
    else
	{
		int label_init = i;
	    while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
	    ++i;
	    pc = getPcForLabel(str, b+label_init, b+i) - 1; 
    }
	}
}
void JAL(char *inst, int i)
{
	if(inst[i] == 's' && inst[i+1] == 'p')
	{
		x1 = 2;
		i += 2;
	}
	else
	{
	    if(inst[i] != 'x')
		invalidInst();
		++i;
		if(isdigit(inst[i]))
		{
		    x1 = inst[i] - '0';
			++i;
			if(isdigit(inst[i]))
			{
				x1 = x1*10 + (inst[i] - '0');
				++i;
			}
		}
		else
		invalidInst();
		}
		if(x1 < 0 || x1 > 31)
		invalidInst();
		xreg[x1]=(pc+1)*4;
		while(inst[i] == ' ' || inst[i] == '\t')
			++i;
		if(inst[i]!=',')
		invalidInst();
		i++;
		while(inst[i] == ' ' || inst[i] == '\t')
			++i;
		if(isdigit(inst[i]))
	    {
		int d;
		d=inst[i]-'0';
		i++;
		while(isdigit(inst[i]))
		{
			d=d*10+inst[i]-'0';
			i++;
		}
		pc=pc+d/4;
		pc--;
	   }
       else
	   {
		int label_init = i;
	    while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
	    ++i;
	    pc = getPcForLabel(str, b+label_init, b+i) - 1; 
       }	
}
void JALR(char *inst, int i)
{
	getLdSt(inst,i);
	xreg[xd]=pc++;
	if(xd==0)
	xreg[xd]=0;
	pc=(xreg[x1]+imm)/4;
	pc--;
}

