#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

//xreg will contain the value of the thirty-two registers x0 - x31
long long xreg[32];

// xd stores destination register, x1 and x2 store the source registers and imm is the immediate
long long xd, x1, x2, imm;

// Data Memory of 4096 bytes
long long Mem[512];

// m stores the modifier, isImm stores whether the instruction contains an immediate
int m;
long isImm;

// str is the string containing the whole program
char* str;

// Executes the instruction depending upon the value of pc
void executeInstruction(void);

// Stores the register numbers of a ld/st instruction in rd, rs1 and imm
void getLdSt(char* inst, int i);

// Stores the register numbers of a 3-address instruction in rd, rs1 and rs2 or imm
//void getReg3Add(char* inst, int i);

// Stores the register numbers of a 2-address instruction in rd and rs2 or imm
void getReg2Add(char* inst, int i);


// Stores the register numbers of a 3-address instruction in rd, rs1 and rs2 or imm
void getReg3Add(char* inst, int i);

// Prints the line number where an error has occured and exits the program
void invalidInst(void);	

// Returns decimal value of a hexadecimal digit
int dec(char ch);

// An array used to convert a hexadecimal immediate to decimal
int hexImm[8];


// sets pc for the main function
void setPcForMain(void);

// gets pc for a given label str[i,j]
int getPcForLabel(char* str, int i, int j);

// k stores the line number of the instruction
int k;

// pc stores the instruction number and therefore pc will be the (program counter)/4
int pc;

// lab_no stores the label number
int lab_no;

// lab_count stores the number of labels in the program
int lab_count;

// A struct for each instruction
struct instruction
{
	int i;		// starting index of inst
	int j;  	// ending index of inst
	int line;	// line in which the instruction appears
};

// An array of all instruction structs of the program (behaves somewhat like the instruction memory)
struct instruction *instructions;

// A struct for each label
struct label
{
	int i;  	  // starting index of label
	int j;  	  // ending index of label
	int inst_no;  // inst_no this label points to
};

// An array of label structs of the program
struct label *labels;

int main(int argc, char* argv[])
{

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
	int inst_count = pc;
	lab_count = lab_no;
	setPcForMain();
	xreg[31] = 4092;		// setting the stack pointer to 0xFFC (the end of the memory)
	while(pc < inst_count)
	{
		k = instructions[pc].line;	// Line number of the current pc
		executeInstruction();		// Executes the instruction corresponding to the current pc
		pc++;
	}
	return 0;
}

void executeInstruction(void)
{
	int b = instructions[pc].i;		// b is the beginning of the instruction
	int f = instructions[pc].j;		// f is the end of the instruction
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
		case 'x':if(inst[i+2] == 'r')
				{
					if(inst[i+1]=='o'){
						i = i + 3;
						if(inst[i] == ' ' || inst[i] == '\t')  //add
						{
							++i;
							m = 0;
							getReg3Add(inst, i);
							if(isImm)
								xreg[xd] = xreg[x1] ^ imm;
							else
								xreg[xd] = xreg[x1] ^ xreg[x2];
						}
						else if(inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t'))
						{
							++i;
							m = 0;
							getReg3Add(inst, i);
							if(isImm)
								xreg[xd] = xreg[x1] ^ imm;
							else
								xreg[xd] = xreg[x1] ^ xreg[x2];
						}
					}
				}
		case 'o': if(inst[i+1] == 'r')
				{
						i = i + 2;
						if(inst[i] == ' ' || inst[i] == '\t')  //OR
						{
							++i;
							m = 0;
							getReg3Add(inst, i);
								xreg[xd] = xreg[x1]|xreg[x2];
						}
						else if(inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t'))
						{
							++i;
							m = 0;
							getReg3Add(inst, i);
								xreg[xd] = xreg[x1]|imm;
						}
					}
		case 'a': if(inst[i+2] == 'd')
				{
					if(inst[i+1] == 'd')	//ADD
					{
						i = i + 3;
						if(inst[i] == ' ' || inst[i] == '\t')  //add
						{
							++i;
							m = 0;	// modifier is set to 0 (default)
							getReg3Add(inst, i);
							if(isImm)
								invalidInst();
							else
								xreg[xd] = xreg[x1] + xreg[x2];
						}
						else if(inst[i] == 'i' && (inst[i+1]==' ' || inst[i+1] == '\t')){
							++i;
							m = 0;
							getReg3Add(inst,i);
							if(isImm){
								xreg[xd] = xreg[x1] + imm;
							}
							else{
								invalidInst();
							}
						}

                    }
					else if(inst[i+1] == 'n')	//AND
					{
						i = i + 3;
						if(inst[i] == ' ' || inst[i] == '\t')  //and
						{
							++i;
							m = 0;
							getReg3Add(inst, i);
							if(isImm)
								xreg[xd] = xreg[x1] & imm;
							else
								xreg[xd] = xreg[x1] & xreg[x2];
						}

						else if(inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t'))
						{
							++i;
							m = 0;
							getReg3Add(inst, i);
							if(isImm)
								xreg[xd] = xreg[x1] & imm;
							else
								xreg[xd] = xreg[x1] & xreg[x2];
						}
					}
                }
				
		case 's':if(inst[i+1] == 'u' && inst[i+2] == 'b')	 //SUB
				{
					i = i + 3;
					if(inst[i] == ' ' || inst[i] == '\t')  //sub
					{
						++i;
						m = 0;
						getReg3Add(inst, i);
						if(isImm)
							invalidInst();
						else
							xreg[xd] = xreg[x1] - xreg[x2];
					}
					else if(inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t'))  //subi
					{
						i = i + 2;
						m = 1;
						getReg3Add(inst, i);
						if(isImm)
							xreg[xd] = xreg[x1] - imm;
						else
							invalidInst();	//subu and rs2 are incompatible
					}
				}
				else if (inst[i + 1] =='l' && inst[i + 2] =='l')
				{
					i = i + 3;
					if (inst[i] == ' ' || inst[i] == '\t')  //shift left logical
					{
						++i;
						m = 0;
						getReg3Add(inst, i);
						if (isImm)
							invalidInst();
						else
							xreg[xd] = xreg[x1] <<xreg[x2];
					}
					else if (inst[i] == 'i' && (inst[i+1] == ' ' || inst[i+1] == '\t'))  //subi
					{
						i = i + 2;
						m = 1;
						getReg3Add(inst, i);
						if (isImm)
							xreg[xd] = xreg[x1]<<imm;
						else
							invalidInst();
					}
				}
				else if (inst[i + 1] =='r' && inst[i + 2] =='l')
		         {
		        	i = i + 3;
			     if (inst[i] == ' ' || inst[i] == '\t')  //shift right logical
			    {
				    ++i;
			    	m = 0;
				    getReg3Add(inst, i);
				   if (isImm)
					invalidInst();
				   else
				   {
					  unsigned long int b;
					   if (xreg[x1] < 0)
						   b = 4294967296+xreg[x1];
					   xreg[xd] = b >> xreg[x2];
				   }
			     }
			     else if (inst[i] == 'i' && (inst[i + 1] == ' ' || inst[i + 1] == '\t'))  //srli
			     {
				   i = i + 2;
				   m = 1;
				   getReg3Add(inst, i);
				   if (isImm)
				   {
					   unsigned long int b;
					   if (xreg[x1] < 0)
						   b = 4294967296+xreg[x1];
					   xreg[xd] = b >> imm;
				   }
				else
					invalidInst();
			     }
		        }
				else if (inst[i + 1] =='r' && inst[i + 2] =='a')
		         {
			       i = i + 3;
			       if (inst[i] == ' ' || inst[i] == '\t')  //shift left arithmetic
			       {
				    ++i;
				    m = 0;
				    getReg3Add(inst, i);
				    if (isImm)
					invalidInst();
				    else
					xreg[xd] = xreg[x1] >> xreg[x2];
			        }
			       else if (inst[i] == 'i' && (inst[i + 1] == ' ' || inst[i + 1] == '\t'))  //srai
			       {
				   i = i + 2;
				   m = 1;
				   getReg3Add(inst, i);
				   if (isImm)
					xreg[xd] = xreg[x1] << imm;
				   else
					invalidInst();
			}
		}
		        else if(inst[i+1] == 'b' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE BYTE
				{
					i += 3;
					int y;
					getLdSt(inst, i);
					y=(xreg[x1]+imm)%8;
					xreg[xd]=xreg[xd]&0x00000000000000ff;
					switch(y)
					{
					case 7:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0x00ffffffffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<56);
						break;
					case 6:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xff00ffffffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<48);
						break;
					case 5:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffff00ffffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<40);
						break;
					case 4:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffffff00ffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<32);
						break;
					case 3:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffffffff00ffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<24);
						break;
					case 2:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffffffffff00ffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<16);
						break;
					case 1:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffffffffffff00ff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<8);
						break;
					case 0:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffffffffffffff00;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|xreg[xd];
						break;
					}
				}
				else if(inst[i+1] == 'h' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE HALFWORD
				{
					i += 3;
					getLdSt(inst, i);
					xreg[xd]=xreg[xd]&0x000000000000ffff;
					int y;
					y=(xreg[x1]+imm)%8;
					switch(y)
					{
					case 7:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0x00ffffffffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<56);
						Mem[(xreg[x1]+imm)/8+1] = Mem[(xreg[x1]+imm)/8+1]&0xffffffffffffff00;
						Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]|(xreg[xd]>>8);
						break;
					case 6:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0x0000ffffffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<48);
						break;
					case 5:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xff0000ffffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<40);
						break;
					case 4:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffff0000ffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<32);
						break;
					case 3:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffffff0000ffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<24);
						break;
					case 2:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffffffff0000ffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<16);
						break;
					case 1:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffffffffff0000ff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<8);
						break;
					case 0:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffffffffffff0000;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]);
						break;
					}
				}
				else if(inst[i+1] == 'w' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE WORD
				{
					i += 3;
					getLdSt(inst, i);
					xreg[xd]=xreg[xd]&0x00000000ffffffff;
					int y;
					y=(xreg[x1]+imm)%8;
					switch(y)
					{
					case 7:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0x00ffffffffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<56);
						Mem[(xreg[x1]+imm)/8+1] = Mem[(xreg[x1]+imm)/8+1]&0xffffffffff000000;
						Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]|(xreg[xd]>>8);
						break;
					case 6:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0x0000ffffffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<48);
						Mem[(xreg[x1]+imm)/8+1] = Mem[(xreg[x1]+imm)/8+1]&0xffffffffffff0000;
						Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]|(xreg[xd]>>16);
						break;
					case 5:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0x000000ffffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<40);
						Mem[(xreg[x1]+imm)/8+1] = Mem[(xreg[x1]+imm)/8+1]&0xffffffffffffff00;
						Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]|(xreg[xd]>>24);
						break;
					case 4:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0x00000000ffffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<32);
						break;
					case 3:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xff00000000ffffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<24);
						break;
					case 2:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffff00000000ffff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<16);
						break;
					case 1:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffffff00000000ff;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]<<8);
						break;
					case 0:
					    Mem[(xreg[x1]+imm)/8] = Mem[(xreg[x1]+imm)/8]&0xffffffff00000000;
						Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[xd]);
						break;
				}

				}
				else if(inst[i+1] == 'd' && (inst[i+2] == ' ' || inst[i+2] == '\t'))		// STORE DOUBLEWORD
				{
                  i=i+3;
				  getLdSt(inst, i);
				  int y;
				  y=(xreg[x1]+imm)%8;
				  switch(y)
				  {
					  case 7:
					     Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]&0x00ffffffffffffff;
						 Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[x1]<<y*56);
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]&0xff00000000000000;
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]|(xreg[x1]>>8);
						 break;
					  case 6:
					     Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]&0x0000ffffffffffff;
						 Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[x1]<<48);
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]&0xffff000000000000;
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]|(xreg[x1]>>16);
						 break;
					  case 5:
					     Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]&0x000000ffffffffff;
						 Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[x1]<<40);
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]&0xffffff0000000000;
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]|(xreg[x1]>>24);
						 break;
					  case 4:
					     Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]&0x00000000ffffffff;
						 Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[x1]<<32);
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]&0xffffffff00000000;
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]|(xreg[x1]>>32);
						 break;
					  case 3:
					     Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]&0x0000000000ffffff;
						 Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[x1]<<24);
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]&0xffffffffff000000;
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]|(xreg[x1]>>40);
						 break;
					  case 2:
					     Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]&0x000000000000ffff;
						 Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[x1]<<16);
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]&0xffffffffffff0000;
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]|(xreg[x1]>>48);
						 break;
					  case 1:
					     Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]&0x00000000000000ff;
						 Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[x1]<<8);
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]&0xffffffffffffff00;
						 Mem[(xreg[x1]+imm)/8+1]=Mem[(xreg[x1]+imm)/8+1]|(xreg[x1]>>56);
						 break;
					  case 0:
					     Mem[(xreg[x1]+imm)/8]=xreg[xd];
				  }
				}

				
		case 'l': if(inst[i+1]=='b'&&(inst[i+2]==' '||inst[i+2]=='\t'))
		           {
					   i=i+3;
					   while(inst[i]==' '||inst[i]=='\t')
					   ++i;
					   getLdSt(inst, i);
					   int y;
					   y=(xreg[x1]+imm)%8;
					   xreg[xd]=xreg[xd]&0;
					   xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
					switch(y)
					{
					case 7:
					    xreg[xd]=xreg[xd]&0xff00000000000000;
						xreg[xd]=xreg[xd]>>56;
						break;
					case 6:
					    xreg[xd]=xreg[xd]&0x00ff000000000000;
						xreg[xd]=xreg[xd]>>48;
						break;
					case 5:
					    xreg[xd]=xreg[xd]&0x0000ff0000000000;
						xreg[xd]=xreg[xd]>>40;
						break;
					case 4:
					    xreg[xd]=xreg[xd]&0x000000ff00000000;
						xreg[xd]=xreg[xd]>>32;
						break;
					case 3:
					    xreg[xd]=xreg[xd]&0x00000000ff000000;
						xreg[xd]=xreg[xd]>>24;
						break;
					case 2:
					    xreg[xd]=xreg[xd]&0x0000000000ff0000;
						xreg[xd]=xreg[xd]>>16;
						break;
					case 1:
					    xreg[xd]=xreg[xd]&0x0000000000000ff00;
						xreg[xd]=xreg[xd]>>8;
						break;
					case 0:
					    xreg[xd]=xreg[xd]&0x00000000000000ff;
						break;
					}
					if(xreg[xd]>127)
					xreg[xd]-=256;

				   }			
				   else if(inst[i+1]=='h'&&(inst[i+2]==' '||inst[i+2]=='\t'))
		           {
					   i=i+3;
					   while(inst[i]==' '||inst[i]=='\t')
					   ++i;
					   int y;
					   getLdSt(inst, i);
					   y=(xreg[x1]+imm)%8;
					   xreg[xd]=xreg[xd]&0;
					   xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
					switch(y)
					{
					case 7:
					    xreg[xd]=xreg[xd]&0xff00000000000000;
						xreg[xd]=xreg[xd]>>56;
						int c=0;
						c=c|Mem[(xreg[x1]+imm)/8+1];
						c=c&0x00000000000000ff;
						c=c<<8;
						xreg[xd]=xreg[xd]|c;
						break;
					case 6:
					    xreg[xd]=xreg[xd]&0xffff000000000000;
						xreg[xd]=xreg[xd]>>48;
						break;
					case 5:
					    xreg[xd]=xreg[xd]&0x00ffff0000000000;
						xreg[xd]=xreg[xd]>>40;
						break;
					case 4:
					    xreg[xd]=xreg[xd]&0x0000ffff00000000;
						xreg[xd]=xreg[xd]>>32;
						break;
					case 3:
					    xreg[xd]=xreg[xd]&0x000000ffff000000;
						xreg[xd]=xreg[xd]>>24;
						break;
					case 2:
					    xreg[xd]=xreg[xd]&0x00000000ffff0000;
						xreg[xd]=xreg[xd]>>16;
						break;
					case 1:
					    xreg[xd]=xreg[xd]&0x00000000000ffff00;
						xreg[xd]=xreg[xd]>>8;
						break;
					case 0:
					    xreg[xd]=xreg[xd]&0x000000000000ffff;
						break;
					}
					if(xreg[xd]>32767)
					xreg[xd]-=65536;
				   }
				    else if(inst[i+1]=='w'&&(inst[i+2]==' '||inst[i+2]=='\t'))
		           {
					   i=i+3;
					   long long c=0;
					   while(inst[i]==' '||inst[i]=='\t')
					   ++i;
					   int y;
					   getLdSt(inst, i);
					   y=(xreg[x1]+imm)%8;
					   xreg[xd]=xreg[xd]&0;
					   xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
					switch(y)
					{
					case 7:
					    xreg[xd]=xreg[xd]&0xff00000000000000;
						xreg[xd]=xreg[xd]>>52;
						c=c|Mem[(xreg[x1]+imm)/8+1];
						c=c&0x0000000000ffffff;
						c=c<<8;
						xreg[xd]=xreg[xd]|c;
						break;
					case 6:
					    xreg[xd]=xreg[xd]&0xffff000000000000;
						xreg[xd]=xreg[xd]>>48;
						c=c|Mem[(xreg[x1]+imm)/8+1];
						c=c&0x000000000000ffff;
						c=c<<16;
						xreg[xd]=xreg[xd]|c;
						break;
					case 5:
					    xreg[xd]=xreg[xd]&0xffffff0000000000;
						xreg[xd]=xreg[xd]>>40;
						c=c|Mem[(xreg[x1]+imm)/8+1];
						c=c&0x00000000000000ff;
						c=c<<24;
						xreg[xd]=xreg[xd]|c;
						break;
					case 4:
					    xreg[xd]=xreg[xd]&0xffffffff00000000;
						xreg[xd]=xreg[xd]>>32;
						break;
					case 3:
					    xreg[xd]=xreg[xd]&0x00ffffffff000000;
						xreg[xd]=xreg[xd]>>24;
						break;
					case 2:
					    xreg[xd]=xreg[xd]&0x0000ffffffff0000;
						xreg[xd]=xreg[xd]>>16;
						break;
					case 1:
					    xreg[xd]=xreg[xd]&0x0000000ffffffff00;
						xreg[xd]=xreg[xd]>>8;
						break;
					case 0:
					    xreg[xd]=xreg[xd]&0x00000000ffffffff;
						break;
					}
					if(xreg[xd]>2147483647)
					xreg[xd]-=4294967296;
				   }
                     else if(inst[i+1]=='d'&&(inst[i+2]==' '||inst[i+2]=='\t'))
		           {
					   i=i+3;
					   getLdSt(inst,i);
					   int y=(xreg[x1]+imm)%8;
					   xreg[xd]=xreg[xd]&0;
					   long long c=0;
					   switch(y)
					   {
						   case 7:
						      xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
							  xreg[xd]=xreg[xd]&0xff00000000000000;
							  xreg[xd]=xreg[xd]>>56;
							  xreg[xd]=xreg[xd]&0x00000000000000ff;
							  c=c|Mem[(xreg[x1]+imm)/8+1];
							  c=c<<8;
							  xreg[xd]=xreg[xd]|c;
							  break;
							case 6:
						      xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
							  xreg[xd]=xreg[xd]&0xffff000000000000;
							  xreg[xd]=xreg[xd]>>48;
							  xreg[xd]=xreg[xd]&0x000000000000ffff;
							  c=c|Mem[(xreg[x1]+imm)/8+1];
							  c=c<<16;
							  xreg[xd]=xreg[xd]|c;
							  break;
							case 5:
						      xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
							  xreg[xd]=xreg[xd]&0xffffff0000000000;
							  xreg[xd]=xreg[xd]>>40;
							  xreg[xd]=xreg[xd]&0x0000000000ffffff;
							  c=c|Mem[(xreg[x1]+imm)/8+1];
							  c=c<<24;
							  xreg[xd]=xreg[xd]|c;
							  break;
							case 4:
						      xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
							  xreg[xd]=xreg[xd]&0xffffffff00000000;
							  xreg[xd]=xreg[xd]>>32;
							  xreg[xd]=xreg[xd]&0x00000000ffffffff;
							  c=c|Mem[(xreg[x1]+imm)/8+1];
							  c=c<<32;
							  xreg[xd]=xreg[xd]|c;
							  break;
							case 3:
						      xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
							  xreg[xd]=xreg[xd]&0xffffffffff000000;
							  xreg[xd]=xreg[xd]>>24;
							  xreg[xd]=xreg[xd]&0x000000ffffffffff;
							  c=c|Mem[(xreg[x1]+imm)/8+1];
							  c=c<<40;
							  xreg[xd]=xreg[xd]|c;
							  break;
							case 2:
						      xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
							  xreg[xd]=xreg[xd]&0xffffffffffff0000;
							  xreg[xd]=xreg[xd]>>16;
							  xreg[xd]=xreg[xd]&0x0000ffffffffffff;
							  c=c|Mem[(xreg[x1]+imm)/8+1];
							  c=c<<48;
							  xreg[xd]=xreg[xd]|c;
							  break;
							case 1:
						      xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
							  xreg[xd]=xreg[xd]&0xffffffffffffff00;
							  xreg[xd]=xreg[xd]>>8;
							  xreg[xd]=xreg[xd]&0x00ffffffffffffff;
							  c=c|Mem[(xreg[x1]+imm)/8+1];
							  c=c<<56;
							  xreg[xd]=xreg[xd]|c;
							  break;
							case 0:
						      xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];

					   }
					  
				   }
				    else if(inst[i+1]=='b'&&inst[i+2]=='u'&&(inst[i+3]==' '||inst[i+3]=='\t'))
		           {
					   i=i+4;
					   while(inst[i]==' '||inst[i]=='\t')
					   ++i;
					   int y;
					   getLdSt(inst, i);
					   y=(xreg[x1]+imm)%8;
					   xreg[xd]=xreg[xd]&0;
					   xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
					switch(y)
					{
					case 7:
					    xreg[xd]=xreg[xd]&0xff00000000000000;
						xreg[xd]=xreg[xd]>>56;
						break;
					case 6:
					    xreg[xd]=xreg[xd]&0x00ff000000000000;
						xreg[xd]=xreg[xd]>>48;
						break;
					case 5:
					    xreg[xd]=xreg[xd]&0x0000ff0000000000;
						xreg[xd]=xreg[xd]>>40;
						break;
					case 4:
					    xreg[xd]=xreg[xd]&0x000000ff00000000;
						xreg[xd]=xreg[xd]>>32;
						break;
					case 3:
					    xreg[xd]=xreg[xd]&0x00000000ff000000;
						xreg[xd]=xreg[xd]>>24;
						break;
					case 2:
					    xreg[xd]=xreg[xd]&0x0000000000ff0000;
						xreg[xd]=xreg[xd]>>16;
						break;
					case 1:
					    xreg[xd]=xreg[xd]&0x0000000000000ff00;
						xreg[xd]=xreg[xd]>>8;
						break;
					case 0:
					    xreg[xd]=xreg[xd]&0x00000000000000ff;
						break;
					}

				   }			
				   else if(inst[i+1]=='h'&&inst[i+2]=='u'&&(inst[i+3]==' '||inst[i+3]=='\t'))
		           {
					   i=i+4;
					   while(inst[i]==' '||inst[i]=='\t')
					   ++i;
					   int y;
					   long long c=0;
					   getLdSt(inst, i);
					   y=(xreg[x1]+imm)%8;
					   xreg[xd]=xreg[xd]&0;
					   xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
					switch(y)
					{
					case 7:
					    xreg[xd]=xreg[xd]&0xff00000000000000;
						xreg[xd]=xreg[xd]>>52;
						c=c|Mem[(xreg[x1]+imm)/8+1];
						c=c&0x00000000000000ff;
						c=c<<8;
						xreg[xd]=xreg[xd]|c;
						break;
					case 6:
					    xreg[xd]=xreg[xd]&0xffff000000000000;
						xreg[xd]=xreg[xd]>>48;
						break;
					case 5:
					    xreg[xd]=xreg[xd]&0x00ffff0000000000;
						xreg[xd]=xreg[xd]>>40;
						break;
					case 4:
					    xreg[xd]=xreg[xd]&0x0000ffff00000000;
						xreg[xd]=xreg[xd]>>32;
						break;
					case 3:
					    xreg[xd]=xreg[xd]&0x000000ffff000000;
						xreg[xd]=xreg[xd]>>24;
						break;
					case 2:
					    xreg[xd]=xreg[xd]&0x00000000ffff0000;
						xreg[xd]=xreg[xd]>>16;
						break;
					case 1:
					    xreg[xd]=xreg[xd]&0x00000000000ffff00;
						xreg[xd]=xreg[xd]>>8;
						break;
					case 0:
					    xreg[xd]=xreg[xd]&0x000000000000ffff;
						break;
					}
				   }
				    else if(inst[i+1]=='w'&&inst[i+2]=='u'&&(inst[i+3]==' '||inst[i+3]=='\t'))
		           {
					   i=i+4;
					   while(inst[i]==' '||inst[i]=='\t')
					   ++i;
					   int y;
					   getLdSt(inst, i);
					   long long c=0;
					   y=(xreg[x1]+imm)%8;
					   xreg[xd]=xreg[xd]&0;
					   xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
					switch(y)
					{
					case 7:
					    xreg[xd]=xreg[xd]&0xff00000000000000;
						xreg[xd]=xreg[xd]>>52;
						c=c|Mem[(xreg[x1]+imm)/8+1];
						c=c&0x0000000000ffffff;
						c=c<<8;
						xreg[xd]=xreg[xd]|c;
						break;
					case 6:
					    xreg[xd]=xreg[xd]&0xffff000000000000;
						xreg[xd]=xreg[xd]>>48;
						c=c|Mem[(xreg[x1]+imm)/8+1];
						c=c&0x000000000000ffff;
						c=c<<16;
						xreg[xd]=xreg[xd]|c;
						break;
					case 5:
					    xreg[xd]=xreg[xd]&0xffffff0000000000;
						xreg[xd]=xreg[xd]>>40;
						c=c|Mem[(xreg[x1]+imm)/8+1];
						c=c&0x00000000000000ff;
						c=c<<24;
						xreg[xd]=xreg[xd]|c;
						break;
					case 4:
					    xreg[xd]=xreg[xd]&0xffffffff00000000;
						xreg[xd]=xreg[xd]>>32;
						break;
					case 3:
					    xreg[xd]=xreg[xd]&0x00ffffffff000000;
						xreg[xd]=xreg[xd]>>24;
						break;
					case 2:
					    xreg[xd]=xreg[xd]&0x0000ffffffff0000;
						xreg[xd]=xreg[xd]>>16;
						break;
					case 1:
					    xreg[xd]=xreg[xd]&0x0000000ffffffff00;
						xreg[xd]=xreg[xd]>>8;
						break;
					case 0:
					    xreg[xd]=xreg[xd]&0x00000000ffffffff;
						break;
					}
				   }


					
        case 'm':  if(inst[i+1] == 'v'){
					i = i + 2;
					if(inst[i] == ' ' || inst[i] == '\t')  //mv
					{
						++i;
						m = 0;
						getReg2Add(inst, i);
						if(isImm)
							xreg[xd] = imm;
						else
							xreg[xd] = xreg[x2];
					}
					else
						invalidInst();
					}

		case 'b': if(inst[i+1] == 'e' && inst[i+2] == 'q' && (inst[i+3] == ' ' || inst[i+3] == '\t'))		//BEQ
				{
					if(flags[0])
					{
						i += 4;
						while(inst[i] == ' ' || inst[i] == '\t')
							++i;
						// Reading the label which beq has to jump to
						int label_init = i;
						while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
							++i;
						pc = getPcForLabel(str, b+label_init, b+i) - 1;  // Subtract 1 so that after the instruction, when pc is incremented with pc++ we will reach the correct instruction
					}
				}


				else if(inst[i+1] == 'g' && inst[i+2] == 't' && (inst[i+3] == ' ' || inst[i+3] == '\t'))		//BGT
				{
					if(flags[1])
					{
						i += 4;
						while(inst[i] == ' ' || inst[i] == '\t')
							++i;
						// Reading the label which bgt has to jump to
						int label_init = i;
						while(inst[i] != '\0' && inst[i] != ' ' && inst[i] != '\t')
							++i;
						pc = getPcForLabel(str, b+label_init, b+i) - 1;  // Subtract 1 so that after the instruction, when pc is incremented with pc++ we will reach the correct instruction
					}
				}

				else
					invalidInst();

				break;



        case '.':  if(inst[i+1] == 'p' && inst[i+2] == 'r' && inst[i+3] == 'i' && inst[i+4] == 'n' && inst[i+5] == 't' && (inst[i+6] == ' ' || inst[i+6] == '\t'))	// .print
				{
					i += 7;
					// This loop will print all the registers that are to be printed
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
							if(inst[i] == 'a')
							{
								xd = 31;
								++i;
							}
							else if(isdigit(inst[i]))
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
						printf("r%-2d: %lld\n",xd, xreg[xd]);
						while(inst[i] == ' ' || inst[i] == '\t')
							i++;
						if(inst[i] != ',')
							break;
						++i;
					}
    			}

    }
}

void getReg3Add(char* inst, int i)
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
		if(inst[i] == 'a')
		{
			xd = 31;
			++i;
		}
		else if(isdigit(inst[i]))
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
		if(inst[i] == 'a')
		{
			x1 = 31;
			++i;
		}
		else if(isdigit(inst[i]))
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
		if(inst[i] == 'a')
		{
			x2 = 31;
			++i;
			isImm = 0;
		}
		else if(isdigit(inst[i]))
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
		if(hexIndex == 4)
		{
			if(m != 1 && hexImm[0] >= 8)
				imm -= 65536;
		}
		if(m == 2)
			imm *= 65536;
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
		if(imm > 65535)
			invalidInst(); 		// The immediate cannot be greater than 16 bits and largest 16 bit unsigned number is 0xFFFF = 65535
		if(m == 0 || m == 2)
		{
			if(imm > 32767)
				invalidInst();	//The largest positive number in 16 bit signed numbers is 0x7FFF = 32767
		}
		if(m == 2)
			imm *= 65536;
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
		if(imm < -32768)
			invalidInst();	// Since the smallest negative number in 16 bit signed numbers is 0x8000 = -32768
		if(m == 1)
			imm += 65536;
		else if(m == 2)
			imm *= 65536;
		isImm = 1;
	}

	else
		invalidInst();
}

void getReg2Add(char* inst, int i)
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
		if(inst[i] == 'a')
		{
			xd = 31;
			++i;
		}
		else if(isdigit(inst[i]))
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
		x2 = 30;
		i += 2;
		isImm = 0;
	}
	else if(inst[i] == 'x')	// if we have rs2
	{
		++i;
		if(inst[i] == 'a')
		{
			x2 = 31;
			++i;
			isImm = 0;
		}
		else if(isdigit(inst[i]))
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
		while(inst[i] != '\0' && hexIndex < 4)
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
			if(m != 1 && hexImm[0] >= 8)
				imm -= 65536;
		}
		if(m == 2)
			imm *= 65536;
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
		if(imm > 65535)
			invalidInst(); 		// The immediate cannot be greater than 16 bits and largest 16 bit unsigned number is 0xFFFF = 65535
		if(m == 0 || m == 2)
		{
			if(imm > 32767)
				invalidInst();	//The largest positive number in 16 bit signed numbers is 0x7FFF = 32767
		}
		if(m == 2)
			imm *= 65536;
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
		if(imm < -32768)
			invalidInst();	// Since the smallest negative number in 16 bit signed numbers is 0x8000 = -32768
		if(m == 1)
			imm += 65536;
		else if(m == 2)
			imm *= 65536;
		isImm = 1;
	}

	else
		invalidInst();
}

int dec(char ch)
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

void setPcForMain(void)
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

int getPcForLabel(char* str, int i, int j)
{
	int lab_c = 0;
	int li, lj;
	// Search for that label which has the same name as the label in the instruction
	while(lab_c < lab_count)
	{
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

	if(inst[i] == '[')		 // if we are using just register indirect mode of addressing
		imm = 0;

	else if(inst[i] == '0' && inst[i+1] == 'x')	// if we have a hexadecimal immediate
	{
		i = i + 2;
		while(inst[i] == ' ' || inst[i] == '\t')
			++i;
		if(inst[i] == '[' || inst[i] == '\0')
			invalidInst();
		int hexIndex = 0;
		while(inst[i] != '[' && hexIndex < 4)
		{
			hexImm[hexIndex++] = dec(inst[i++]);
			while(inst[i] == ' ' || inst[i] == '\t')
				++i;
		}
		if(inst[i] != '[')
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
	if(inst[i] != '[')
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
	if(inst[i] != ']')
		invalidInst();
}

void invalidInst(void)
{
	printf("The instruction in line number %d is INVALID.\n", k);
	exit(0);	// EXIT the interpreter
}
