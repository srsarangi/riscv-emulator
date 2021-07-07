#ifndef LOGICAL_H
#define LOGICAL_H

extern void XOR(char *inst, int i);  // function to perform xor operation on content of both source register
extern void XORI(char *inst, int i); // function to perform xor operation on content of rs1 and immediate
extern void OR(char *inst, int i); // function to perform or operation on content of both source register
extern void ORI(char *inst, int i); // function to perform xor operation on content of rs1 and immediate
extern void AND(char *inst, int i); // // function to perform and operation on content of both source register
extern void ANDI(char *inst, int i); // function to perform xor operation on content of rs1 and immediate

#endif
