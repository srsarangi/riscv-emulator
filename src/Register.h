#ifndef REGISTER_H
#define REGISTER_H
extern void invalidInst(void);
extern int dec(char ch);
extern void Stype(char* inst, int i);
extern void Rtype(char *inst, int i);
extern void Itype(char *inst, int i);
extern void ItypeL(char *inst, int i);
extern int Btype(char *inst, int i);
extern int Utype(char *inst, int i);
# endif
