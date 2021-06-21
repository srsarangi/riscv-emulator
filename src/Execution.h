#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include"Register.h" // includes user-defined header file Register.h
#include"Arithmetic.h" // includes user-defined header file Arithmetic.h
#include"DataTransfer.h" // includes user-defined header file DataTransfer.h
#include"Logical.h" // includes user-defined header file Logical.h
#include"Shift.h" // includes user-defined header file Shift.h
#include"BranchInst.h" // includes user-defined file BranchInst.h
extern long long xreg[32];
int b;
extern char *str;
extern int pc;
void PRINT(char *inst, int i) //  Arguments:(instruction, index) | extract index of specified register and  prints value stored in them
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
void executeInstruction(int a, int c) // function to execute instruction of specified pc. it takes beginning and ending index of instruction as arguments.
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
		case 'x': if(inst[i+1]=='o'&&inst[i+2] == 'r') //bit-by-bit Exclusive-OR
				{
					i = i + 3;
					if(inst[i] == ' ' || inst[i] == '\t')  //XOR
					XOR(inst,i); //calls function XOR() that is defined in Logical.h header file
					else if(inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t')) //XORI
					{
						i++;
					XORI(inst,i); //calls function XORI() that is defined in Logical.h header file
					}
                    else
                    invalidInst();
				}
                else
                invalidInst();
				break;

		case 'o': if(inst[i+1] == 'r') // bit-by-bit or
				{
					i = i + 2;
					if(inst[i] == ' ' || inst[i] == '\t')  //OR
					OR(inst, i); // calls function XOR() that is defined in Logical.h header file
					else if(inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t')) //ORI
					{
						i++;
					ORI(inst, i); // calls function XOR() that is defined in Logical.h header file
					}
                    else
                    invalidInst();
				}
                else
                invalidInst();
				break;

		case 'a': if(inst[i+1] == 'd'&&inst[i+2] == 'd') // Addition
				{
					
					i = i + 3;
					if(inst[i] == ' ' || inst[i] == '\t')  //ADD
					ADD(inst, i);  //calls function ADD() that is defined in Arithmetic.h header file
					else if(inst[i] == 'i' && (inst[i+1]==' ' || inst[i+1] == '\t')) //ADDI
					{
						i++;
                    ADDI(inst, i); // calls function ADDI() that is defined in Arithmetic.h header file
					}
                    else
                    invalidInst();
                }
				else if(inst[i+1] == 'n'&&inst[i+2]=='d')	// bit-by-bit
				{
					i = i + 3;
					if(inst[i] == ' ' || inst[i] == '\t')  //AND
					AND(inst, i);  // calls function AND() that is defined in Logical.h header file
					else if(inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t')) //ANDI
					{
						i++;
					ANDI(inst,i); // calls function ANDI() that is defined in Logical.h header file
					}
                    else
                    invalidInst();
                }
				else
                invalidInst();
				break;

		case 's':if(inst[i+1] == 'u' && inst[i+2] == 'b')	 //Substraction
				{
					i = i + 3;
					if(inst[i] == ' ' || inst[i] == '\t')  //SUB
					SUB(inst, i);  // calls function SUB() that is defined in Arithmetic.h header file
                    else
                    invalidInst();
				}
				else if (inst[i+1] =='l' && inst[i+2] =='l') // Shift Left
				{
					i = i + 3;
					if (inst[i] == ' ' || inst[i] == '\t')  //shift left logical
					SLL(inst, i); // calls function SLL() that is defined in Shift.h header file
					else if (inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t'))  //SLLI
					{
						i++;
					SLLI(inst,i); // calls function SLLI() that is defined in Shift.h header file
					}
                    else
                    invalidInst();
				}
				else if (inst[i+1] =='r' && inst[i+2] =='l') // shift right
		        {
		        	i = i + 3;
			        if (inst[i] == ' ' || inst[i] == '\t')  //shift right logical
			        SRL(inst, i); // calls function SRL() that is defined in Shift.h header file
			        else if (inst[i] == 'i' && (inst[i + 1] == ' ' || inst[i + 1] == '\t'))  //srli
					{
						i++;
			        SRLI(inst, i); // calls function SRLI() that is defined in Shift.h header file
					}
                    else
                    invalidInst();
		        }
				else if (inst[i + 1] =='r' && inst[i + 2] =='a') // Arithmetic Right Shift
		        {
			       i = i + 3;
			       if (inst[i] == ' ' || inst[i] == '\t')  //shift left arithmetic
			       SRA(inst, i); //  calls function SRA() that is defined in Shift.h header file
			       else if (inst[i] == 'i' && (inst[i + 1] == ' ' || inst[i + 1] == '\t'))  //srai
				   {
					   i++;
			       SRAI(inst, i); //  calls function SRAI() that is defined in Shift.h header file
				   }
                   else
                   invalidInst();
		        }
		        else if(inst[i+1] == 'b' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE BYTE
				{
					i += 3;
					STOREB(inst, i); // calls function STOREB() that is defined in DataTansfer.h header file to store byte in memory
				}
				else if(inst[i+1] == 'h' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE HALFWORD
				{
					i += 3;
					STOREH(inst, i); // calls function STOREH() that is defined in DataTransfer.h header file to store halfword in memory
				}
				else if(inst[i+1] == 'w' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE WORD
				{
					i += 3;
					STOREW(inst,i); //  calls function STOREW()) that is defined in DataTransfer.h header file to store word in memory
				}
				else if(inst[i+1] == 'd' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE DOUBLEWORD
				{
                  i=i+3;
				  STORED(inst, i); // calls function STOED() that is defined in DataTransfer.h header file to store doubleword in memory
				}
			    else if (inst[i + 1] =='l' && inst[i + 2] =='t'&&(inst[i+3]==' '||inst[i+3]=='\t')) // set if less than
		        {
		        	i = i + 3;
			        if (inst[i] == ' ' || inst[i] == '\t')  //slt
			        SLT(inst, i); // calls function SLT() that is defined in Shift.h header file
                    else if(inst[i]=='i'&&(inst[i+1]==' '||inst[i+1]=='\t')) //SLTI
					{
						i++;
                    SLTI(inst, i); //  calls function SLTI() that is defined in Shift.h header file
					}
                    else
                    invalidInst();
				}
				 
				else if (inst[i + 1] =='l' && inst[i + 2] =='t' && inst[i+3]=='u') // set if less than unsigned
		        {
		        	i = i + 4;
			        if (inst[i] == ' ' || inst[i] == '\t')  //sltu
			        SLTU(inst, i); // calls function SLTU() that is defined in Shift.h header file
                    else
                    invalidInst();
			    }
				else if (inst[i + 1] =='l' && inst[i + 2] =='t' && inst[i+3]=='i' && inst[i+4]=='u')
		        {
		        	i = i + 5;
			        if (inst[i] == ' ' || inst[i] == '\t')  //sltiu
			        SLTIU(inst, i); // calls function SLTIU() that is defined in Shift.h header file
                    else
                    invalidInst();
				}
                else
                invalidInst();
				break;
				
		case 'l':if(inst[i+1]=='b'&&(inst[i+2]==' '||inst[i+2]=='\t')) // LOAD BYTE
		        {
					i=i+3;
					while(inst[i]==' '||inst[i]=='\t')
					i++;
					LOADB(inst, i); //  calls function LOADB() that is defined in DataTransfer.h header file to loab byte from memory to register
				}			
				else if(inst[i+1]=='h'&&(inst[i+2]==' '||inst[i+2]=='\t'))  //  LOAD HALFWORD
		        {
					i=i+3;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADH(inst, i);  //  calls function LOADH() that is defined in DataTransfer.h header file to load halfword from memory to register
				}
				else if(inst[i+1]=='w'&&(inst[i+2]==' '||inst[i+2]=='\t'))   // LOAD WORD
		        {
					i=i+3;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADW(inst, i);   //  calls function LOADW() that is defined in DataTransfer.h header file to load word from memory to register
				}
                else if(inst[i+1]=='d'&&(inst[i+2]==' '||inst[i+2]=='\t'))    // LOAD DOUBLEWORD
		        {
					i=i+3;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADD(inst, i); //  calls function LOADD() that is defined in DataTransfer.h header file to load doubleword from memory to register
				}
				else if(inst[i+1]=='b'&&inst[i+2]=='u'&&(inst[i+3]==' '||inst[i+3]=='\t')) // LOAD BYTE UNSIGNED
		        {
					i=i+4;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADBU(inst, i); //  calls function LOADBU() that is defined in DataTransfer.h header file to load unsigned byte from memory to register

				}			
				else if(inst[i+1]=='h'&&inst[i+2]=='u'&&(inst[i+3]==' '||inst[i+3]=='\t'))   // LOAD HALFWORD UNSIGNED
		        {
					i=i+4;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADHU(inst, i);  //  calls function LOADHU() that is defined in DataTransfer.h header file to load unsigned halfword from memory to register
				}
				else if(inst[i+1]=='w'&&inst[i+2]=='u'&&(inst[i+3]==' '||inst[i+3]=='\t')) // LOAD WORD UNSIGNED
		        {
					i=i+4;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
					LOADWU(inst, i);  // calls function LOADWU() that is defined in DataTransfer.h header file to load unsigned word from memory to register
				}
                else
                invalidInst();
                break;

        case 'm':if(inst[i+1]=='u'&&inst[i+2]=='l'&&(inst[i+3]==' '||inst[i+3]=='\t')) // multiplication
				{
					i=i+4;
                    while(inst[i]==' '||inst[i]=='\t')
					++i;
					MUL(inst, i); //  calls function MUL() that is defined in Arithmetic.h header file to perform multiplication on values stored in rs1 and rs2
				}
				else if(inst[i+1]=='u'&&inst[i+2]=='l'&&inst[i+3]=='i'&&(inst[i+4]==' '||inst[i+4]=='\t')) // muli
				{
					i=i+4;
					while(inst[i]==' '||inst[i]=='\t')
					++i;
                    MULI(inst, i);  //  calls function MULI() that is defined in Arithmetic.h header file to perform multiplication on values stored in rs1 and immediaate
				}
				else
				invalidInst();
				break;
		          
		case 'b': if(inst[i+1] == 'e' && inst[i+2] == 'q' && (inst[i+3] == ' ' || inst[i+3] == '\t'))		//BEQ
				{
					i += 4;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					BEQ(inst, i);  // calls function BEQ() that is defined in BranchInst.h header file
				}
				else if(inst[i+1] == 'g' && inst[i+2] == 'e' && (inst[i+3] == ' ' || inst[i+3] == '\t'))		//BGE
				{
					i += 4;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
				    BGE(inst, i);  //  calls function BGE() that is defined in BranchInst.h header file
				}
                 else if(inst[i+1] == 'g' && inst[i+2] == 'e' &&inst[i+3]=='u'&& (inst[i+4] == ' ' || inst[i+4] == '\t'))		//BGEU
				{
					i += 5;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					BGEU(inst,i);  //  calls function BGEU() that is defined in BranchInst.h header file
				}
				else if(inst[i+1] == 'n' && inst[i+2] == 'e' && (inst[i+3] == ' ' || inst[i+3] == '\t'))		//BNE
				{
					i += 4;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					BNE(inst, i);   //  calls function BNE() that is defined in BranchInst.h header file
				}

				else if(inst[i+1] == 'l' && inst[i+2] == 't' && (inst[i+3] == ' ' || inst[i+3] == '\t'))		//BLT
				{
					i += 4;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					BLT(inst, i); //  calls function BLT() that is defined in BranchInst.h header file 
				}
                else if(inst[i+1] == 'l' && inst[i+2] == 't' &&inst[i+3]=='u'&& (inst[i+4] == ' ' || inst[i+4] == '\t'))		//BLTU
				{
					i += 5;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					BLTU(inst, i);  //  calls function BLTU() that is defined in BranchInst.h header file
				}
                else
                invalidInst();
				break;

        case 'j':if(inst[i+1] == 'a' && inst[i+2] == 'l' && (inst[i+3] == ' ' || inst[i+3] == '\t'))  //JAL
				{
					i=i+4;
					while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					JAL(inst, i);  //  calls function JAL() that is defined in BranchInst.h header file
                }
				else if(inst[i+1]=='a'&&inst[i+2]=='l'&&inst[i+3]=='r'&& (inst[i+4] == ' ' || inst[i+4] == '\t'))   //JALR
				{
					i=i+4;
                    while(inst[i] == ' ' || inst[i] == '\t')
						++i;
					JALR(inst, i);  //  calls function JALR() that is defined in BranchInst.h header file
				}
                else
                invalidInst();
				break;

        case '.':  if(inst[i+1] == 'p' && inst[i+2] == 'r' && inst[i+3] == 'i' && inst[i+4] == 'n' && inst[i+5] == 't' && (inst[i+6] == ' ' || inst[i+6] == '\t'))	// .print
				{
					i += 7;
                    while(inst[i] == ' ' || inst[i] == '\t')
						++i;
                    PRINT(inst,i);  // calls function PRINT()
                }
				
    }
}
