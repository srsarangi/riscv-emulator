#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
extern long long xd, x1, x2, imm; // distination , sources and immediate value.
extern int isImm; // check for the persence of immediate
extern int hexImm[5]; 
extern int k;
void invalidInst(void)
{
	printf("The instruction in line number %d is INVALID.\n", k);
	exit(0);	// EXIT the interpreter
}
int dec(char ch) // This Function is used for hexa-decimal to decimal Conversion.
{
	switch(ch)
	{
		case '0': return 0;
				   break;
		case '1': return 1;
				   break;
		case '2': return 2;
				   break;
		case '3': return 3;
				   break;
		case '4': return 4;
				   break;
		case '5': return 5;
				   break;
		case '6': return 6;
				   break;
		case '7': return 7;
				   break;
		case '8': return 8;
				   break;
		case '9': return 9;
				   break;
		case 'a':
		case 'A': return 10;
				   break;
		case 'b':
		case 'B': return 11;
				   break;
		case 'c':
		case 'C': return 12;
				   break;
		case 'd':
		case 'D': return 13;
				   break;
		case 'e':
		case 'E': return 14;
				   break;
		case 'f':
		case 'F': return 15;
				   break;
	}
	invalidInst();
}
void getReg3Add(char* inst, int i) // To Extract the Two source Register and One Destination Register
{
	//Code to extract register number of rd
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
	if(inst[i] == 's' && inst[i+1] == 'p')
	{
		xd = 2;
		i += 2;
	}
	
	else
	{
		if(inst[i] != 'x')
			invalidInst();
			
		++i;
		if(isdigit(inst[i]))
		{
			xd = inst[i] - '0';
			++i;
			if(isdigit(inst[i]))
			{
				xd = xd*10 + (inst[i] - '0');
				++i;
			}
		}
		else
			invalidInst();
	}
	if(xd < 0 || xd > 31)
		invalidInst();

	//Code to extract register number of rs1
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
	if(inst[i] != ',')
		invalidInst();
	++i;
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
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

	//Code to extract register number of rs2/imm
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
		isImm = 0;
	}
	else if(inst[i] == 'x')	// if we have rs2
	{
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
			isImm = 0;	//since the instruction does not have an immediate
		}
		else
			invalidInst();
		if(x2 < 0 || x2 > 31)
			invalidInst();
	}

	else if(inst[i] == '0' && inst[i+1] == 'x')	// if we have a hexadecimal immediate
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
		if(hexIndex == 3)
		{
			if(hexImm[0] >= 8)
				imm -= 4096;
		}
		isImm = 1;
	}

	else if(isdigit(inst[i]))	// if we have a positive decimal immediate
	{ 
		imm = 0;
		while(isdigit(inst[i]))
		{
			imm = imm*10 + (inst[i] - '0');
			i++;
		}
		if(imm > 2047)
		invalidInst();	//The largest positive number in 12 bit signed numbers is 0x7FF = 2047
		isImm = 1;
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
		if(imm < -2048)
			invalidInst();	// Since the smallest negative number in 12 bit signed numbers is 0x8000 = -2048
		isImm = 1;
	}

	else
		invalidInst();
}

void getLdSt(char* inst, int i)		// instruction is of the form rd, imm[rs1]
{
	//Code to extract register number of rd
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
	if(inst[i] == 's' && inst[i+1] == 'p')
	{
		xd = 2;
		i += 2;
	}
	else
	{
		if(inst[i] != 'x')
			invalidInst();
		++i;
		if(isdigit(inst[i]))
		{
			xd = inst[i] - '0';
			++i;
			if(isdigit(inst[i]))
			{
				xd = xd*10 + (inst[i] - '0');
				++i;
			}
		}
		else
			invalidInst();
	}
	if(xd < 0 || xd > 31)
		invalidInst();


	//Code to extract register number of imm
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
	if(inst[i] != ',')
		invalidInst();
	++i;
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;

	if(inst[i] == '(')		 // if we are using just register indirect mode of addressing
		imm = 0;

	else if(inst[i] == '0' && inst[i+1] == 'x')	// if we have a hexadecimal immediate
	{
		i = i + 2;
		while(inst[i] == ' ' || inst[i] == '\t')
			++i;
		if(inst[i] == '(' || inst[i] == '\0')
			invalidInst();
		int hexIndex = 0;
		while(inst[i] != '(' && hexIndex < 4)
		{
			hexImm[hexIndex++] = dec(inst[i++]);
			while(inst[i] == ' ' || inst[i] == '\t')
				++i;
		}
		if(inst[i] != '(')
			invalidInst();
		imm = 0;
		int q = 0;
		while(q < hexIndex)
			imm = 16*imm + hexImm[q++];
		if(hexIndex == 4)
		{
			if(hexImm[0] >= 8)
				imm -= 65536;
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
		if(imm > 32767)
			invalidInst();		//The largest positive number in 16 bit signed numbers is 0x7FFF = 32767
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
		if(imm < -32768)
			invalidInst();	// Since the smallest negative number in 16 bit signed numbers is 0x8000 = -32768
	}

	else
		invalidInst();


	//Code to extract register number of rs1
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
	if(inst[i] != '(')
		invalidInst();
	++i;
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
	if(inst[i] == 's' && inst[i+1] == 'p')
	{
		x1 = 2;
		i += 2;
		isImm = 0;
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
	while(inst[i] == ' ' || inst[i] == '\t')
		i++;
	if(inst[i] != ')')
		invalidInst();
}
