#ifndef KERNEL_H
#define KERNEL_H
#include "pcb.h"

int kernel();
void addToReady(struct PCB*);
int size();
struct PCB* pop();
int myinit(char*);
int scheduler();
void emptyReadyQueue();

#endif
