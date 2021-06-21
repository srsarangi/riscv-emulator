#include<stdio.h> // importing all the necessary libraries
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
extern long long xreg[32];  // This is store the values of all 32 registers
extern int isImm; // Used to check the persence of immediate
extern long long xd, x1, x2, imm; // Distination register,source registers and immediate values
extern int pc; // Program counter to move the commands
extern char* str; 
extern int b; 
int getRegBranch(char *inst, int i)  // This function is used for getting register from the branch command and comparing them.
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
void BEQ(char *inst, int i)  // Branch if Equal
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
void BGE(char *inst, int i)  // Branch Greater than or Equal.
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
void BGEU(char *inst, int i) // Branch Greater than or equal (unsigned).
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
void BNE(char *inst, int i) // Branch Not Equal
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
void BLT(char *inst, int i) // Branch Less Than
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
void BLTU(char *inst, int i)  // Branch Less than Unsigned
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
void JAL(char *inst, int i) // JUMP AND LINK
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
void JALR(char *inst, int i) // JUMP AND LINK REGISTER
{
	getLdSt(inst,i);
	xreg[xd]=pc++;
	if(xd==0)
	xreg[xd]=0;
	pc=(xreg[x1]+imm)/4;
	pc--;
}

