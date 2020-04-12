#include<string.h>
#include"ram.h"
#include"interpreter.h"
#include"shell.h"

#define DEFAULT_QUANTA 2

struct CPU { 
    int IP; 
    char IR[1000]; 
    int quanta; 
} CPU;


int run(int quanta){
    
    if (quanta > DEFAULT_QUANTA ){
        quanta = DEFAULT_QUANTA;
    }

    for (int i = 0; i < quanta; i++)
    {
        strcpy(CPU.IR,ram[CPU.IP]);
        int errorCode = parseInput(CPU.IR);
        if (errorCode != 0){
            if (errorCode < 0){
                ram[CPU.IP][strlen(ram[CPU.IP])-2]='\0';
                displayCode(errorCode,ram[CPU.IP]);
            }
            return errorCode;
        }
        CPU.IP ++;
    }
    return 0;
}
