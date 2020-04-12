#include <stdio.h>
#include <stdlib.h>

typedef struct PCB
{
    int PC; //Program Counter - cell number of ram[]
    int start; //start address - cell number of first instruction in program
    int end; //end address - cell number of last instruction in program
}PCB;


PCB* makePCB(int start, int end){
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    pcb->PC = start;
    pcb->start = start;
    pcb->end = end;
    return pcb;
}


