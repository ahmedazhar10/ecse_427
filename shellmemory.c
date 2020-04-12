#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "shell.h"
#include "interpreter.h"
#include "shellmemory.h"

struct MEMORY {
    char* var;
    char* value;
} memory[25];

int size_memory = 25; //restricts memory size to 25
int lastIndex = 0; //Stores last index of memory


int searchVariable(char * var) {
    for (int i = 0; i<lastIndex; i++){
        if ( strcmp(memory[i].var,var) == 0 ){
            return i;
        }
    }
    return -1;
}

int addVariable (char *var, char* value){

    if (lastIndex == size_memory) return -1;
    memory[lastIndex].var = var;
    memory[lastIndex].value = value;
    lastIndex ++;
    return 0;
}

int addRecord (char * var, char * value) {
    
    int pos = searchVariable(var);
    if (pos == -1){//Not found, add var
        return addVariable(var, value);
    } else {
        memory[pos].value = value;
    }

    return 0;
}

char* fetchValue (char *var){
    int position = searchVariable(var);
    if (position==-1) return "_NONE_";
    return memory[position].value;
}
