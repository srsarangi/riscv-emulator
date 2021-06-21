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
int getRegBranch(char *inst, int i)   // function that extract register number of both source register of Conditional Branch Instructions
{
    //code to extract index of source register rs1
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
		if(isdigit(inst[i])) // if immediate
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


		//Code to extract index of source register rs2
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
	return i;  // retuns index after both source register
}
void BEQ(char *inst, int i) // function that sets pc to specified label if content of both source register is equal
{
	 i=getRegBranch(inst,i);  // to find index of both source register
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
		while(isdigit(inst[i])) // if immediate
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
	    pc = getPcForLabel(str, b+label_init, b+i) - 1;  // calls function getPcForLabel()  that is defined in MAINFILE.C to get pc for specified label (decremets by 1 since whenn it will incremented in main() function it retains correct pc)
    }
	}
}
void BGE(char *inst, int i) // function that sets pc to specified label if greater than or equal
{
    i=getRegBranch(inst,i);  // to find index of both source register
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
		while(isdigit(inst[i])) // if immediate
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
	    pc = getPcForLabel(str, b+label_init, b+i) - 1;  //// calls function getPcForLabel()  that is defined in MAINFILE.C to get pc for specified label (decremets by 1 since whenn it will incremented in main() function it retains correct pc)
    }
	}
}
void BGEU(char *inst, int i) // function that sets pc to specified label if greater than or equal unsigned
{
    i=getRegBranch(inst,i);  // to find index of both source register
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
		while(isdigit(inst[i])) // if immediate
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
	    pc = getPcForLabel(str, b+label_init, b+i) - 1;  //// calls function getPcForLabel()  that is defined in MAINFILE.C to get pc for specified label (decremets by 1 since whenn it will incremented in main() function it retains correct pc)
    }
	}
}
void BNE(char *inst, int i) // function that sets pc to specified label if content of both register is not equal
{
    i=getRegBranch(inst,i);  // to find index of both source register
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
		while(isdigit(inst[i])) // if immediate
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
	    pc = getPcForLabel(str, b+label_init, b+i) - 1; // calls function getPcForLabel()  that is defined in MAINFILE.C to get pc for specified label (decremets by 1 since whenn it will incremented in main() function it retains correct pc)
    }
	}
}
void BLT(char *inst, int i) // function that sets pc to specified label if less than
{
    i=getRegBranch(inst,i);  // to find index of both source register
	while(inst[i]==' '||inst[i]=='\t')
	++i;
	if(inst[i]!=',')
	invalidInst();
	i++;
	while(inst[i]==' '||inst[i]=='\t')
	++i;
    if(xreg[x1]<xreg[x2])
    {
	if(isdigit(inst[i])) // if immediate
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
		pc--; //decremets by 1 since whenn it will incremented in main() function it retains correct pc
	}
    else
	{
		int label_init = i;
	    while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
	    ++i;
	    pc = getPcForLabel(str, b+label_init, b+i) -1; // calls function getPcForLabel()  that is defined in MAINFILE.C to get pc for specified label (decremets by 1 since whenn it will incremented in main() function it retains correct pc)
	}
	}
}
void BLTU(char *inst, int i) // function that sets pc to specified label if less than unsigned
{
    i=getRegBranch(inst,i);  // to find index of both source register
	while(inst[i]==' '||inst[i]=='\t')
	++i;
	if(inst[i]!=',')
	invalidInst();
	i++;
	while(inst[i]==' '||inst[i]=='\t')
	++i;
    if((unsigned)xreg[x1]<(unsigned)xreg[x2])
    {
	if(isdigit(inst[i])) //if immediate
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
		pc--;  //decremets by 1 since whenn it will incremented in main() function it retains correct pc
	}
    else
	{
		int label_init = i;
	    while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
	    ++i;
	    pc = getPcForLabel(str, b+label_init, b+i) - 1; // calls function getPcForLabel()  that is defined in MAINFILE.C to get pc for specified label (decremets by 1 since whenn it will incremented in main() function it retains correct pc)
    }
	}
}
void JAL(char *inst, int i)  // unconditional jump jal
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
		pc--;     //decremets by 1 since whenn it will incremented in main() function it retains correct pc
	   }
       else
	   {
		int label_init = i;
	    while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
	    ++i;
	    pc = getPcForLabel(str, b+label_init, b+i) - 1; // calls function getPcForLabel()  that is defined in MAINFILE.C to get pc for specified label (decremets by 1 since whenn it will incremented in main() function it retains correct pc)
       }
}
void JALR(char *inst, int i) //function for unconditional branch instruction jalr
{
	getLdSt(inst,i); // same instruction format as DataTransfer Instructions
	xreg[xd]=pc++;
	if(xd==0)
	xreg[xd]=0;
	pc=(xreg[x1]+imm)/4;
	pc--; //decremets by 1 since whenn it will incremented in main() function it retains correct pc
}

