#include<stdio.h>
extern long long xreg[32];
extern int isImm;
extern long long xd, x1, x2, imm;
extern long long Mem[512];
int y;
void STOREB(char *inst, int i) // function to store byte in memory
{
	if((xreg[x1]+imm)>4095||(xreg[x1]+imm)<0)
	{
		printf("Accessing Memory out of bound"); // we have 4kb memory
		exit(0);
	}
	getLdSt(inst, i); // defined in Register.h header file
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
    }
}
void STOREH(char *inst, int i) // function to store halfword in memory
{
	if((xreg[x1]+imm)>4095||(xreg[x1]+imm)<0)
	{
		printf("Accessing Memory out of bound"); // we have 4kb memory
		exit(0);
	}
    getLdSt(inst, i);  // defined in Register.h header file
	xreg[xd]=xreg[xd]&0x000000000000ffff;
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
    }
}
void STOREW(char *inst, int i) // function to store word in memory
{
	if((xreg[x1]+imm)>4095||(xreg[x1]+imm)<0)
	{
		printf("Accessing Memory out of bound"); // we have 4kb memory
		exit(0);
	}
    getLdSt(inst, i);  // defined in Register.h header file
	xreg[xd]=xreg[xd]&0x00000000ffffffff;
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
void STORED(char *inst, int i) // function to store doubleword in memory
{
	if((xreg[x1]+imm)>4095||(xreg[x1]+imm)<0)
	{
		printf("Accessing Memory out of bound"); // we have 4kb memory
		exit(0);
	}
    getLdSt(inst, i);  // defined in Register.h header file
	y=(xreg[x1]+imm)%8;
	switch(y)
	{
	case 7:
		Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]&0x00ffffffffffffff;
		Mem[(xreg[x1]+imm)/8]=Mem[(xreg[x1]+imm)/8]|(xreg[x1]<<56);
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
void LOADB(char *inst, int i)  // function to loab byte from memory to register
{
	if((xreg[x1]+imm)>4095||(xreg[x1]+imm)<0)
	{
		printf("Accessing Memory out of bound"); // we have 4kb memory
		exit(0);
	}
    getLdSt(inst, i);  // defined in Register.h header file
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
	}
	if(xreg[xd]>127)
	xreg[xd]-=256;
 }			
void LOADH(char *inst, int i)  // function to loab halfword from memory to register
{
	if((xreg[x1]+imm)>4095||(xreg[x1]+imm)<0)
	{
		printf("Accessing Memory out of bound"); // we have 4kb memory
		exit(0);
	}
	long long c=0;
    getLdSt(inst, i);  // defined in Register.h header file
    y=(xreg[x1]+imm)%8;
    xreg[xd]=xreg[xd]&0;
    xreg[xd]=xreg[xd]|Mem[(xreg[x1]+imm)/8];
	switch(y)
	{
	case 7:
	    xreg[xd]=xreg[xd]&0xff00000000000000;
		xreg[xd]=xreg[xd]>>56;
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
	}
	if(xreg[xd]>32767)
	xreg[xd]-=65536;
}
void LOADW(char *inst, int i)  // function to loab word from memory to register
{
	if((xreg[x1]+imm)>4095||(xreg[x1]+imm)<0)
	{
		printf("Accessing Memory out of bound"); // we have 4kb memory
		exit(0);
	}
    long long c=0;
    getLdSt(inst, i);  // defined in Register.h header file
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
	}
	if(xreg[xd]>2147483647)
	xreg[xd]-=4294967296;
}
void LOADD(char *inst, int i) // function to loab doubleword from memory to register
{
	if((xreg[x1]+imm)>4095||(xreg[x1]+imm)<0)
	{
		printf("Accessing Memory out of bound"); // we have 4kb memory
		exit(0);
	}
    getLdSt(inst,i);  // defined in Register.h header file
	y=(xreg[x1]+imm)%8;
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
void LOADBU(char *inst, int i) // function to loab unsigned byte from memory to register
{
	if((xreg[x1]+imm)>4095||(xreg[x1]+imm)<0)
	{
		printf("Accessing Memory out of bound"); // we have 4kb memory
		exit(0);
	}
	getLdSt(inst, i);  // defined in Register.h header file
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
	}
}
void LOADHU(char *inst, int i)  // function to loab unsigned halfword from memory to register
{
	if((xreg[x1]+imm)>4095||(xreg[x1]+imm)<0)
	{
		printf("Accessing Memory out of bound"); // we have 4kb memory
		exit(0);
	}
	long long c=0;
	getLdSt(inst, i);  // defined in Register.h header file
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
	}
}
void LOADWU(char *inst, int i) // function to loab unsigned word from memory to register
{
	if((xreg[x1]+imm)>4095||(xreg[x1]+imm)<0)
	{
		printf("Accessing Memory out of bound"); // we have 4kb memory
		exit(0);
	}
	getLdSt(inst, i);  // defined in Register.h header file
	long long  c=0;
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
	}
}