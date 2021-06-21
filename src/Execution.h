#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include"Register.h"
#include"Arithmetic.h"
#include"DataTransfer.h"
#include"Logical.h"
#include"Shift.h"
#include"BrancInst.h"
extern long long xreg[32];
int b;
extern char *str;
extern int pc;
void PRINT(char *inst, int i) // Print Command to print Value of register 
{
	while(1)
	{
	// Here rd will be used to denote the register to be printed
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
		printf("x%-2d: %lld\n",xd, xreg[xd]);
		while(inst[i] == ' ' || inst[i] == '\t')
			i++;
		if(inst[i] != ',')
			break;
		++i;
	}
}
void executeInstruction(int a, int c) // Program to Execute Instructons.
{
	b = a;		// b is the beginning of the instruction
	int f = c;		// f is the end of the instruction
	while(str[b] == ' ' || str[b] == '\t')
		b++;
	int u = b;
	while(u < f)
	{
		if(str[u] == '@')	// Everything after @ will be a single line comment
		{
			f = u;
			break;
		}
		u++;
	}
	if(b == f)	// If this line is just a blank line or a comment and does not contain any instruction
		return;
	int l = f-b+1;
	char inst[l];
	memcpy(inst, &str[b], l-1);		// Copy the instructions into the string inst
	inst[l-1] = '\0';
	int i = 0;
	switch(inst[i])
	{
		case 'x': if(inst[i+1]=='o'&&inst[i+2] == 'r')
				{
					i = i + 3;
					if(inst[i] == ' ' || inst[i] == '\t')  //XOR
					XOR(inst,i);
					else if(inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t')) //XORI
					{
						i++;
					XORI(inst,i);
					}
                    else
                    invalidInst();
				}
                else
                invalidInst();
				break;

		case 'o': if(inst[i+1] == 'r')  
				{
					i = i + 2;
					if(inst[i] == ' ' || inst[i] == '\t')  //OR
					OR(inst, i);
					else if(inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t')) //ORI
					{
						i++;
					ORI(inst, i);
					}
                    else
                    invalidInst();
				}
                else
                invalidInst();
				break;

		case 'a': if(inst[i+1] == 'd'&&inst[i+2] == 'd')
				{
					
					i = i + 3;
					if(inst[i] == ' ' || inst[i] == '\t')  //ADD
					ADD(inst, i);
					else if(inst[i] == 'i' && (inst[i+1]==' ' || inst[i+1] == '\t')) //ADDI
					{
						i++;
                    ADDI(inst, i);
					}
                    else
                    invalidInst();
                }
				else if(inst[i+1] == 'n'&&inst[i+2]=='d')	//AND
				{
					i = i + 3;
					if(inst[i] == ' ' || inst[i] == '\t')  //AND
					AND(inst, i);
					else if(inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t')) //ANDI
					{
						i++;
					ANDI(inst,i);
					}
                    else
                    invalidInst();
                }
				else
                invalidInst();
				break;

		case 's':if(inst[i+1] == 'u' && inst[i+2] == 'b')	 //SUB
				{
					i = i + 3;
					if(inst[i] == ' ' || inst[i] == '\t')  //SUB
					SUB(inst, i);
                    else
                    invalidInst();
				}
				else if (inst[i+1] =='l' && inst[i+2] =='l')
				{
					i = i + 3;
					if (inst[i] == ' ' || inst[i] == '\t')  //shift left logical
					SLL(inst, i);
					else if (inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t'))  //SLLI
					{
						i++;
					SLLI(inst,i);
					}
                    else
                    invalidInst();
				}
				else if (inst[i+1] =='r' && inst[i+2] =='l')
		        {
		        	i = i + 3;
			        if (inst[i] == ' ' || inst[i] == '\t')  //shift right logical
			        SRL(inst, i);
			        else if (inst[i] == 'i' && (inst[i + 1] == ' ' || inst[i + 1] == '\t'))  //srli
					{
						i++;
			        SRLI(inst, i);
					}
                    else
                    invalidInst();
		        }
				else if (inst[i + 1] =='r' && inst[i + 2] =='a')
		        {
			       i = i + 3;
			       if (inst[i] == ' ' || inst[i] == '\t')  //shift left arithmetic
			       SRA(inst, i);
			       else if (inst[i] == 'i' && (inst[i + 1] == ' ' || inst[i + 1] == '\t'))  //srai
				   {
					   i++;
			       SRAI(inst, i);
				   }
                   else
                   invalidInst();
		        }
		        else if(inst[i+1] == 'b' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE BYTE
				{
					i += 3;
					STOREB(inst, i);
				}
				else if(inst[i+1] == 'h' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE HALFWORD
				{
					i += 3;
					STOREH(inst, i);
				}
				else if(inst[i+1] == 'w' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE WORD
				{
					i += 3;
					STOREW(inst,i);
				}
				else if(inst[i+1] == 'd' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE DOUBLEWORD
				{
                  i=i+3;
				  STORED(inst, i);
				}
			    else if (inst[i + 1] =='l' && inst[i + 2] =='t'&&(inst[i+3]==' '||inst[i+3]=='\t'))
		        {
		        	i = i + 3;
			        if (inst[i] == ' ' || inst[i] == '\t')  //slt
			        SLT(inst, i);
                    else if(inst[i]=='i'&&(inst[i+1]==' '||inst[i+1]=='\t')) //SLTI
					{
						i++;
                    SLTI(inst, i);
					}
                    else
                    invalidInst();
				}
				 
				else if (inst[i + 1] =='l' && inst[i + 2] =='t' && inst[i+3]=='u')
		        {
		        	i = i + 4;
			        if (inst[i] == ' ' || inst[i] == '\t')  //sltu
			        SLTU(inst, i);
                    else
                    invalidInst();
			    }
				else if (inst[i + 1] =='l' && inst[i + 2] =='t' && inst[i+3]=='i' && inst[i+4]=='u')
		        {
		        	i = i + 5;
			        if (inst[i] == ' ' || inst[i] == '\t')  //sltiu
			        SLTIU(inst, i);
                    else
                    invalidInst();
				}
                else
                invalidInst();
				break;
				
		case 'l':if(inst[i+1]=='b'&&(inst[i+2]==' '||inst[i+2]=='\t'))
		        {
					i=i+3;
					while(inst[i]==' '||inst[i]=='\t')
					i++;
					LOADB(inst, i);
				}			
				else if(inst[i+1]=='h'&&(inst[i+2]==' '||inst[i+2]=='\t'))
		        {
					i=i+3;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADH(inst, i);
				}
				else if(inst[i+1]=='w'&&(inst[i+2]==' '||inst[i+2]=='\t'))
		        {
					i=i+3;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADW(inst, i);
				}
                else if(inst[i+1]=='d'&&(inst[i+2]==' '||inst[i+2]=='\t'))
		        {
					i=i+3;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADD(inst, i);
				}
				else if(inst[i+1]=='b'&&inst[i+2]=='u'&&(inst[i+3]==' '||inst[i+3]=='\t'))
		        {
					i=i+4;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADBU(inst, i);

				}			
				else if(inst[i+1]=='h'&&inst[i+2]=='u'&&(inst[i+3]==' '||inst[i+3]=='\t'))
		        {
					i=i+4;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADHU(inst, i);
				}
				else if(inst[i+1]=='w'&&inst[i+2]=='u'&&(inst[i+3]==' '||inst[i+3]=='\t'))
		        {
					i=i+4;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADWU(inst, i);  
				}
                else
                invalidInst();
                break;

        case 'm':if(inst[i+1]=='u'&&inst[i+2]=='l'&&(inst[i+3]==' '||inst[i+3]=='\t'))
				{
					i=i+4;
                    while(inst[i]==' '||inst[i]=='\t')
					++i;
					MUL(inst, i);
				}
				else if(inst[i+1]=='u'&&inst[i+2]=='l'&&inst[i+3]=='i'&&(inst[i+4]==' '||inst[i+4]=='\t'))
				{
					i=i+4;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
                    MULI(inst, i);
				}
				else
				invalidInst();
				break;
		          
		case 'b': if(inst[i+1] == 'e' && inst[i+2] == 'q' && (inst[i+3] == ' ' || inst[i+3] == '\t'))		//BEQ
				{
					i += 4;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					BEQ(inst, i);
				}
				else if(inst[i+1] == 'g' && inst[i+2] == 'e' && (inst[i+3] == ' ' || inst[i+3] == '\t'))		//BGE
				{
					i += 4;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
				    BGE(inst, i);
				}
                 else if(inst[i+1] == 'G' && inst[i+2] == 'E' &&inst[i+3]=='u'&& (inst[i+4] == ' ' || inst[i+4] == '\t'))		//BGEU
				{
					i += 5;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					BGEU(inst,i);
				}
				else if(inst[i+1] == 'n' && inst[i+2] == 'e' && (inst[i+3] == ' ' || inst[i+3] == '\t'))		//BNE
				{
					i += 4;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					BNE(inst, i);
				}

				else if(inst[i+1] == 'l' && inst[i+2] == 't' && (inst[i+3] == ' ' || inst[i+3] == '\t'))		//BLT
				{
					i += 4;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					BLT(inst, i);
				}
                else if(inst[i+1] == 'l' && inst[i+2] == 't' &&inst[i+3]=='u'&& (inst[i+4] == ' ' || inst[i+4] == '\t'))		//BLTU
				{
					i += 5;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					BLTU(inst, i);
				}
                else
                invalidInst();
				break;

        case 'j':if(inst[i+1] == 'a' && inst[i+2] == 'l' && (inst[i+3] == ' ' || inst[i+3] == '\t'))  //JAL
				{
					i=i+4;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					JAL(inst, i);
                }
				else if(inst[i+1]=='a'&&inst[i+2]=='l'&&inst[i+3]=='r'&& (inst[i+4] == ' ' || inst[i+4] == '\t'))   //JALR
				{
					i=i+4;
                    while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					JALR(inst, i);
				}
                else
                invalidInst();
				break;

        case '.':  if(inst[i+1] == 'p' && inst[i+2] == 'r' && inst[i+3] == 'i' && inst[i+4] == 'n' && inst[i+5] == 't' && (inst[i+6] == ' ' || inst[i+6] == '\t'))	// .print
				{
					i += 7;
                    while(inst[i] == ' ' || inst[i] == '\t')
						++i;
                    PRINT(inst,i);
                }
				
    }
}
