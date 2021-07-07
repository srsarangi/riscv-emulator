//xreg will contain the value of the thirty-two registers x0 - x31
extern long long xreg[32];

// xd stores destination register, x1 and x2 store the source registers and imm is the immediate
extern int xd, x1, x2, imm;

// Data Memory of 4096 bytes
extern long long Mem[512];

// isImm stores whether the instruction contains an immediate
extern int isImm;

// str is the string containing the whole program
extern char* str;

// An array used to convert a hexadecimal immediate to decimal
extern int hexImm[5];
// k stores the line number of the instruction
extern int k;

// pc stores the instruction number and therefore pc will be the (program counter)/4
extern int pc;

// lab_no stores the label number
extern int lab_no;

// lab_count stores the number of labels in the program
extern int lab_count;

//inst_count stores the number of inatructions in the program
extern int inst_count;

extern int b;

// An array of all instruction structs of the program (behaves somewhat like the instruction memory)
extern struct instruction *instructions;

struct instruction
{
	int i;		// starting index of inst
	int j;  	// ending index of inst
	int line;	// line in which the instruction appears
};
// An array of label structs of the program | structure of label defined in BranchInst.h header file
extern struct label *labels;

struct label
{
	int i;  	  // starting index of label
	int j;  	  // ending index of label
	int inst_no;  // inst_no this label points to
};