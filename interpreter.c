#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"shellmemory.h"
#include"shell.h"
#include"kernel.h"

#define TRUE 1
#define FALSE 0


int set(char * words[]){
    char* varName = words[1];
    char* value = words[2];
    int errorCode = addRecord(varName,value);
    return errorCode;
}


int print(char * words[]){
    char* varName = words[1];
    char* value = fetchValue(varName);
    if (strcmp(value,"_NONE_")==0) {
        printf ("Variable does not exist\n");
    } else {
        // else display variable value
        printf("%s\n",value);
    }
    return 0;
}

static int run(char * words[]){

    char * filename = words[1];
    FILE * fp = fopen(filename,"r");
    int errorCode = 0;
    if (fp==NULL) return -3;
    char buffer[1000];
    printf("--------> EXECUTING %s <--------\n",filename);
    while (!feof(fp)){
        fgets(buffer,999,fp);
        errorCode = parseInput(buffer);
        // User input the "quit" command. Terminate execution of this script file.
        if (errorCode == 1) {
            // Run command successfully executed so ERRORCODE 0. Stop reading file.
            errorCode = 0;
            break;
        } else if (errorCode != 0) {
            // An error occurred. Display it and stop reading the file.
            //removing the extra carriage return
            buffer[strlen(buffer)-2]='\0';
            displayCode(errorCode,buffer);
            break;
        }
    }
    printf("--------> FINISHING %s <--------\n",filename);
    fclose(fp);
    return 0;
}

int exec(char * words[]){
    //filter out duplicated text file names
    char * filename[3] = { "_NONE_", "_NONE_", "_NONE_"};
    int nextFree = 0;
    int errorCode = 0;
    for (int i = 1; i <= 3; i++)
    {
        if ( strcmp(words[i],"_NONE_") != 0 ) {
            int duplicate = FALSE;
            for (int j = 0; j<i-1; j++){
                if ( strcmp(filename[j],words[i]) == 0 ) {
                    duplicate = TRUE;
                    break;
                }
            }
            if (duplicate){
                displayCode(-6,words[i]);
            } else {
                filename[nextFree] = strdup(words[i]);
                nextFree++;
                errorCode = myinit(words[i]);
                if ( errorCode < 0){
                    displayCode(errorCode,words[i]);
                    printf("EXEC COMMAND ABORTED...\n");
                    emptyReadyQueue();
                    return 0;
                }
            }
        // Looped through all files
        } else {
            break;
        }
    }

    printf("|----------| ");
    printf("\tSTARTING CONCURRENT PROGRAMS ( ");
    for (int i = 0; i < 3; i++)
    {
        if ( strcmp(filename[i],"_NONE_") != 0 ){
            printf("%s ", filename[i]);
        }
    }
    printf(")\t|----------|\n");

    scheduler();

    printf("|----------| ");
    printf("\tTERMINATING ALL CONCURRENT PROGRAMS");
    printf("\t|----------|\n");
    return 0;
}


int interpreter(char* words[]){
    int errorCode = 0;
    if ( strcmp(words[0],"help") == 0 ) {
        //Prompt
        printf("-------------------------------------------------------------------------------------------------------\n");
        printf("COMMANDS\t\t\tDESCRIPTIONS\n");
        printf("-------------------------------------------------------------------------------------------------------\n");
        printf("help\t\t\t\tDisplays all commands\n");
        printf("quit\t\t\t\tTerminates the shell\n");
        printf("set VAR STRING\t\t\tAssigns the value STRING to the shell memory variable VAR\n");
        printf("print VAR\t\t\tDisplays the STRING value assigned to the shell memory variable VAR\n");
        printf("run SCRIPT.TXT\t\t\tExecutes the file SCRIPT.txt\n");
        printf("exec p1 p2 p3\t\t\tExecutes programs p1 p2 p3 concurrently\n");
        printf("-------------------------------------------------------------------------------------------------------\n");

    } else if ( strcmp(words[0],"quit") == 0) {
        errorCode = 1;

    } else if ( strcmp(words[0],"set") == 0 ) {
        if ( ( strcmp(words[1],"_NONE_") == 0 ) || ( strcmp(words[2],"_NONE_") == 0 ) ) {
            errorCode = -2;
        } else {
            errorCode = set(words);
        }
    }  else if ( strcmp(words[0],"print") == 0 ) {
        if ( strcmp(words[1],"_NONE_") == 0 ) return -2;
        errorCode = print(words);
    } else if ( strcmp(words[0],"run") == 0 ) {
        if ( strcmp(words[1],"_NONE_") == 0 ) return -2;
        errorCode = run(words);
    } else if ( strcmp(words[0],"exec") == 0 ) {
        // check if there's at least 2 arguments and not >= 4 arguments
        if ( strcmp(words[1],"_NONE_") == 0  || strcmp(words[4],"_NONE_") != 0 ) return -2;

        errorCode = exec(words);
    } else {
        errorCode = -4;
    }

    return errorCode;
    
}