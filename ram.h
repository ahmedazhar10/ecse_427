#ifndef RAM_H
#define RAM_H
#include<stdio.h>

char* ram[1000];

void addToRAM (FILE *, int *, int *);

void removeFromRam (int, int);

void resetRAM();
#endif 