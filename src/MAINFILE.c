#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include"Global_Variable.h"
#include"Execution.h" // includes header file Execution.h
//xreg will contain the value of the thirty-two registers x0 - x31
long long xreg[32];

// xd stores destination register, x1 and x2 store the source registers and imm is the immediate
int xd, x1, x2, imm;

// Data Memory of 4096 bytes
long long Mem[512];

// isImm stores whether the instruction contains an immediate
int isImm;

// str is the string containing the whole program
char* str;

// An array used to convert a hexadecimal immediate to decimal
int hexImm[5];

// sets pc for the main function
void setPcForMain(void);

// k stores the line number of the instruction
int k;

// pc stores the instruction number and therefore pc will be the (program counter)/4
int pc;

// lab_no stores the label number
int lab_no;

// lab_count stores the number of labels in the program
int lab_count;

//inst_count stores the number of inatructions in the program
int inst_count;

// An array of all instruction structs of the program (behaves somewhat like the instruction memory)
struct instruction *instructions;

// An array of label structs of the program | structure of label defined in BranchInst.h header file
struct label *labels;

int main(int argc, char* argv[])
{
    xreg[0]=0;
	k = 1;

	//Code for opening the file and computing the size of the program
	long int size;
	FILE* f = fopen(argv[1], "r");		// argv[1] is the name of the file in which the program is written
	if(f == 0)
	{
		printf("Could not read file!!!\n");
		exit(0);
	}
	else
	{
		fseek(f, 0, SEEK_END);	// fseek takes f to EOF
		size = ftell(f);		// ftell gives the position of f which is EOF and hence returns the length of the file
	}
	size = size + 2;			// We add 2 to accomodate for an extra '\n' and a '\0'
	
	// Code for storing the whole program into the string str
	str = malloc(size*(sizeof(char)));
	rewind(f);					// Brings f to the beginning of the file
	int colon_count = 0;		// colon_count will contain the number of colons in the program which decides the maximum number of labels
	int line_count = 0;			// line_count will contain the number of lines in the program which decides the maximum number of instructions
	int i = 0;
	int x = fgetc(f);
	while(x != EOF)
	{
		if(x != 13)				// We neglect the carriage returns (ASCII 13) if present
		{
			if(x == '/')		// We simply neglect the multi-line comments and DON'T add them to the string str
			{
				x = fgetc(f);
				if(x == '*')
				{
					while(1)
					{
						x = fgetc(f);
						if(x == EOF)
						{
							printf("Error: Unterminated Comment!\n");
							exit(0);
						}
						else if(x == '*')
						{
							x = fgetc(f);
							if(x == '/')
							{
								x = fgetc(f);
								break;
							}
						}
					}
				}
				else if(x == EOF)
				{
					str[i++] = '/';
					break;
				}
				else
					str[i++] = '/';
			}
			if(x == EOF)
				break;
			str[i++] = x;
			if(x == '\n')
				line_count++;
			else if(x == ':')
				colon_count++;
		}
		x = fgetc(f);
	}
	str[i++] = '\n';
	str[i] = '\0';

	instructions = malloc(line_count*sizeof(struct instruction));
	labels = malloc(colon_count*sizeof(struct label));

	x = 0;
	while(str[x] == '\n')
	{
		x++;
		k++;	// Incrementing the line number
	}
	i = x;		// Beginnning of the first non-empty line
	int j, t;
	pc = 0;
	lab_no = 0;
	while(str[x] != '\0')
	{
		if(str[x] == ':')	// to obtain the instruction which the label is identifying
		{
			t = x--;		// t stores the position of the colon
			while(str[x] != ' ' && str[x] != '\t' && str[x] != '\n')
			{
				x--;
				if(x < 0)
					break;
			}
			labels[lab_no].i = x+1;
			labels[lab_no].j = t;
			j = x;
			x = t+1;
			while(str[x] == ' ' || str[x] == '\t')
				++x;
			if(str[x] == '\n')	// label is pointing to the instruction in the next line
			{
				while(j > 0)
				{
					if(str[j] != ' ' && str[j] != '\t')
						break;
					--j;
				}
				if(str[j] == '\n' || j == -1)
					labels[lab_no++].inst_no = pc;		// There is no instruction in the line of this label
				else
				{
					labels[lab_no++].inst_no = pc+1;	// There is an instruction before this label in the same line but label points to the next line
					instructions[pc].i = i;
					instructions[pc].j = j+1;
					instructions[pc].line = k;
					pc++;
				}
			}
			else
			{
				labels[lab_no++].inst_no = pc;		// Label points to an instruction in the same line
				instructions[pc].i = x;
				while(str[x] != '\n')
					x++;
				instructions[pc].j = x;
				instructions[pc].line = k;
				pc++;
			}
			while(str[x] == '\n')	// Neglecting all blank lines after this label
			{
				x++;
				k++;	// Incrementing the line number
			}
			i = x;
		}
		else if(str[x] == '\n')			// This is the end of an instruction
		{
			j = x;
			instructions[pc].i = i;		// i is the beginning of the instruction
			instructions[pc].j = j;
			instructions[pc].line = k;
			pc++;
			while(str[x] == '\n')		// Neglecting all blank lines after this instruction
			{
				x++;
				k++;	// Incrementing the line number
			}
			i = x;
		}
		else
			x++;
	}
	inst_count = pc;
	lab_count = lab_no;
	setPcForMain();
	xreg[2] = 4095;		// setting the stack pointer to 0xFFE (the end of the memory)
	while(pc < inst_count)
	{
		k = instructions[pc].line;	// Line number of the current pc
		executeInstruction();		// calls function executeInstruction()that is defined in header file Execution.h and Executes the instruction corresponding to the current pc takes starting and ending index as argument
		pc++;
		xreg[0]=0; // any operation can't change value of x0
	}
	return 0;
}
void setPcForMain(void) // sets pc at Label main
{
	int lab_c = 0;
	int i, j;
	while(lab_c < lab_count)
	{
		i = labels[lab_c].i;
		j = labels[lab_c].j;
		if(j-i == 5)
		{
			if(strncmp(&str[i],".main",5) == 0)
			{
				pc = labels[lab_c].inst_no;
				return;
			}
		}
		lab_c++;
	}
	printf("There is no .main label in the program !!!\n");
	exit(0);
}
