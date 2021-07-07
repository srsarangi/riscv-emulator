#include<stdio.h>
#include <string.h>
#include<ctype.h>
#include"Global_Variable.h"
#include"Register.h"
#include"Arithmetic.h"
void ADD(char *inst, int i)  // function that perform addition on content of two register and stores in destinstion register
{
    Rtype(inst, i);  // calls Rtype() function that is present in Register.h header file
	xreg[xd] = xreg[x1]+xreg[x2];
}
void ADDI(char *inst, int i) // function that perform addition on content of first source register and immediate and stores in destinstion register
{
    Itype(inst, i);  // calls Itype() function that is present in Register.h header file
	xreg[xd] = xreg[x1]+imm;
}
void SUB(char *inst, int i) //function that perform substraction on content of two register and stores in destinstion register
{
    Rtype(inst, i); // calls Rtype() function that is present in Register.h header file
	xreg[xd] = xreg[x1]-xreg[x2];
}
void MUL(char *inst, int i)  //function that perform multiplication on content of two source registers and stores in destinstion register
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = xreg[x1]*xreg[x2];
}
void MULH(char *inst, int i)  //function that perform multiplication on content of two source registers and stores upper 64-bits in destinstion register
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd]=(xreg[x1]/4294967296)*(xreg[x2]/4294967296);
}
void MULHU(char *inst, int i)  //function that perform multiplication on unsigned content of two source registers and stores upper 64-bits in destinstion register
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = ((unsigned long long)xreg[x1]/4294967296)*((unsigned long long)xreg[x2]/4294967296);
}
void MULHSU(char *inst, int i)  //function that perform multiplication on content of two source registers and stores upper 64-bit in destinstion register
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = (xreg[x1]/4294967296)*((unsigned long long)xreg[x2]/4294967296);
}
void DIV(char *inst, int i)  //function that perform division on content of two source registers and stores in destinstion register
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = xreg[x1]/xreg[x2];
}
void DIVU(char *inst, int i)  //function that perform division on unsigned content of two source registers and stores in destinstion register
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = (unsigned long long)xreg[x1]/(unsigned long long)xreg[x2];
}
void REM(char *inst, int i)  //function that provide remainder
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = xreg[x1]%xreg[x2];
}
void REMU(char *inst, int i)  //function that provide remainder for unsigned division
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = (unsigned long long)xreg[x1]%(unsigned long long)xreg[x2];
}
void ADDW(char *inst, int i)  // function that perform addition on content of two register and stores in destinstion register : only on lower 32-bits
{
    Rtype(inst, i);  // calls Rtype() function that is present in Register.h header file
	xreg[xd] =(int)(xreg[x1]+xreg[x2]);
}
void ADDIW(char *inst, int i) // function that perform addition on content of first source register and immediate and stores in destinstion register : only on lower 32-bits
{
    Itype(inst, i);  // calls Itype() function that is present in Register.h header file
	xreg[xd] = (int)(xreg[x1]+imm);
}
void SUBW(char *inst, int i) //function that perform substraction on content of two register and stores in destinstion register : only on lower 32-bits
{
    Rtype(inst, i); // calls Rtype() function that is present in Register.h header file
	xreg[xd] = (int)(xreg[x1]-xreg[x2]);
}
void MULW(char *inst, int i)  //function that perform multiplication on content of two source registers and stores in destinstion register : only on lower 32-bits
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = (int)xreg[x1]*(int)xreg[x2];
}
void DIVW(char *inst, int i)  //function that perform division for lower 32-bit
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = (int)xreg[x1]/(int)xreg[x2];
}
void DIVUW(char *inst, int i)  //function that perform division for unsigned lower 32-bit
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = (unsigned int)xreg[x1]/(unsigned int)xreg[x2];
}
void REMW(char *inst, int i)  //function that provide remainder for lower 32-bit
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = (int)xreg[x1]%(int)xreg[x2];
}
void REMUW(char *inst, int i)  //function that provides remainder for unsigned lower 32-bit
{
    Rtype(inst, i);  //calls Rtype() function that is present in Register.h header file
	xreg[xd] = (unsigned int)xreg[x1]%(unsigned int)xreg[x2];
}
void LUI(char *inst, int i)
{
	i=Utype(inst, i);

	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
	if(inst[i] != ',')
		invalidInst();
	++i;
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
    if(inst[i] == '0' && inst[i+1] == 'x')	// if we have a hexadecimal immediate
	{
		i = i + 2;
		while(inst[i] == ' ' || inst[i] == '\t')
			++i;
		if(inst[i] == '\0')
			invalidInst();
		int hexIndex = 0;
		while((inst[i]>='0'&&inst[i]<='9')|| (inst[i] >= 'A' && inst[i] <= 'F')|| (inst[i] >= 'a' && inst[i] <= 'f'))
		{
			hexImm[hexIndex++] = dec(inst[i++]);
			while(inst[i] == ' ' || inst[i] == '\t')
				++i;
		}
		if(inst[i] != '\0')
			invalidInst();
		imm = 0;
		int q = 0;
		while(q < hexIndex)
			imm = 16*imm + hexImm[q++];
		if(hexIndex == 4)
		{
			if(hexImm[0] >= 8)
				imm -= 1048576;
		}
	}

	else if(isdigit(inst[i]))	// if we have a positive decimal immediate
	{ 
		imm = 0;
		while(isdigit(inst[i]))
		{
			imm = imm*10 + (inst[i] - '0');
			i++;
		}
		if(imm > 524287)
		invalidInst();	//The largest positive number in 12 bit signed numbers is 0x7FF = 2047
	}

	else if(inst[i] == '-')		// if we have a negative decimal immediate
	{
		i++;
		while(inst[i] == ' ' || inst[i] == '\t')
			++i;
		imm = 0;
		while(isdigit(inst[i]))
		{
			imm = imm*10 + (inst[i] - '0');
			i++;
		}
		imm = -imm;
		if(imm < -524288)
			invalidInst();	// Since the smallest negative number in 12 bit signed numbers is 0x8000 = -2048
	}
	else
		invalidInst();
	xreg[xd]=imm<<12;
}
