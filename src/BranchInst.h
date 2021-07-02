#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
extern long long xreg[32];
extern int isImm;
extern int xd, x1, x2, imm;
extern int pc;
extern char* str;
extern int b;
extern int lab_count;
extern int inst_count;
struct label
{
	int i;  	  // starting index of label
	int j;  	  // ending index of label
	int inst_no;  // inst_no this label points to
};

// An array of label structs of the program
extern struct label *labels;

int getPcForLabel(char* str, int i, int j)
{
	int lab_c = 0;
	int li, lj;
	// Search for that label which has the same name as the label in the instruction
	while(lab_c < lab_count)
	{
		int k;
		li = labels[lab_c].i;
		lj = labels[lab_c].j;
		if((j-i) == (lj-li))
		{
			if(strncmp(&str[i],&str[li],j-i) == 0)
				return labels[lab_c].inst_no;
		}
		lab_c++;
	}
	printf("The label does not exist !!!\n");
	invalidInst();
}
void BEQ(char *inst, int i) // function that sets pc to specified label if content of both source register is equal
{
	i=Btype(inst,i);  // to find index of both source register
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
		if(pc>=inst_count)
		invalidInst();
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
    i=Btype(inst,i);  // to find index of both source register
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
		if(pc>=inst_count)
		invalidInst();
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
    i=Btype(inst,i);  // to find index of both source register
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
		if(pc>=inst_count)
		invalidInst();
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
    i=Btype(inst,i);  // to find index of both source register
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
		if(pc>=inst_count)
		invalidInst();
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
    i=Btype(inst,i);  // to find index of both source register
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
		if(pc>=inst_count)
		invalidInst();
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
    i=Btype(inst,i);  // to find index of both source register
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
		if(pc>=inst_count)
		invalidInst();
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
	   i=Utype(inst, i); // to find index of destination register
		xreg[xd]=(pc+1)*4;
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
		if(pc>=inst_count)
		invalidInst();
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
	ItypeL(inst,i); // to find index of destination and source register
	xreg[xd]=(pc++)*4;
	if(xd==0)
	xreg[xd]=0;
	pc=(xreg[x1]+imm)/4;
	pc--; //decremets by 1 since whenn it will incremented in main() function it retains correct pc
	if(pc>=inst_count)
	invalidInst();
}