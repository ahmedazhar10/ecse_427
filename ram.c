#include<stdio.h>
#include<string.h>

int nextFreeCell = 0;
char *ram[1000] = { NULL }; 

void removeFromRam (int start, int end){
    for (int i = start; i <= end; i++)
    {
        ram[i] = NULL;
    }
}

void addToRAM (FILE *p, int *start, int *end){
    *start = nextFreeCell;
    int i = *start;
    char buffer[1000];
    
    while (!feof(p) && i<1000){
        fgets(buffer,999,p);
        ram[i]= strdup(buffer);
        i++;
    }
    
    if (i>=1000 && !feof(p)){
        removeFromRam(0,i-1);
        nextFreeCell = 0;
        *start = -1;
        *end = -1;        
    
    } else {
        nextFreeCell=i;
        *end=i-1;
    }
}

/*
Reset free cell to 0
*/
void resetRAM(){
    nextFreeCell = 0;
}


