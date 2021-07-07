#include<stdio.h>
#include"Global_Variable.h"
#include"Register.h"
#include"Shift.h"
void SLL(char *inst, int i)  // function to perform left shifting (two source register)
{
    Rtype(inst, i);  // calls Rtype() that is defined in Register.h
    xreg[xd] = xreg[x1]<<xreg[x2];
}
void SLLI(char *inst, int i) // function to perform left shifting (one source register one immediate)
{
    Itype(inst, i);  // calls Itype() that is defined in Register.h
    xreg[xd] = xreg[x1]<<imm;
}
void SRA(char *inst, int i) // function to perform arithmetic right shifting (two source register)
{
    Rtype(inst, i);  // calls Rtype() that is defined in Register.h
    xreg[xd] = xreg[x1]>>xreg[x2];
}
void SRAI(char *inst, int i)  // function to perform arithmetic right shifting (one source register one immediate)
{
    Itype(inst, i);  // calls Itype() that is defined in Register.h
    xreg[xd] = xreg[x1]>>imm;
}
void SRL(char *inst, int i)  // function to perform logical right shifting (two source register)
{
    Rtype(inst, i);  // calls Rtype() that is defined in Register.h
    unsigned long long b;
	b = (unsigned long long)xreg[x1];
	xreg[xd] = b >> xreg[x2];
}
void SRLI(char *inst, int i) // function to logical right shifting (one source register one immediate)
{
    Itype(inst, i);  // calls Itype() that is defined in Register.h
	unsigned long long b;
	b = (unsigned long long)xreg[x1];
	xreg[xd] = b >> imm;
}
void SLLW(char *inst, int i)  // function to perform left shifting (two source register) on only 32-bit values
{
    Rtype(inst, i);  // calls Rtype() that is defined in Register.h
    xreg[xd] = (int)xreg[x1]<<(int)xreg[x2];
}
void SLLIW(char *inst, int i) // function to perform left shifting (one source register one immediate) on only 32-bit values
{
    Itype(inst, i);  // calls Itype() that is defined in Register.h
    xreg[xd] = (int)xreg[x1]<<imm;
}
void SRAW(char *inst, int i) // function to perform arithmetic right shifting (two source register) on only 32-bit values
{
    Rtype(inst, i);  // calls Rtype() that is defined in Register.h
    xreg[xd] = (int)xreg[x1]>>(int)xreg[x2];
}
void SRAIW(char *inst, int i)  // function to perform arithmetic right shifting (one source register one immediate) on only 32-bit values
{
    Itype(inst, i);  // calls Itype() that is defined in Register.h
    xreg[xd] = (int)xreg[x1]>>imm;
}
void SRLW(char *inst, int i)  // function to perform logical right shifting (two source register) on only 32-bit values
{
    Rtype(inst, i);  // calls Rtype() that is defined in Register.h
    unsigned int b;
	b = (unsigned int)xreg[x1];
	xreg[xd] = b >> (int)xreg[x2];
}
void SRLIW(char *inst, int i) // function to logical right shifting (one source register one immediate) on only 32-bit values
{
    Itype(inst, i);  // calls Itype() that is defined in Register.h
	unsigned int b;
	b = (unsigned int)xreg[x1];
	xreg[xd] = b >> imm;
}