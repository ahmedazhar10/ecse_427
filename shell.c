#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interpreter.h"


void displayCode(int errorCode, char *command)
{
    switch (errorCode)
    {
    case -1:
        printf("ERROR -1 : NO MORE SHELL MEMORY\n");
        break;
    case -2:
        printf("ERROR -2 : INCORRECT NUMBER OF ARGUMENTS. TRY 'help'\n");
        break;
    case -3:
        printf("ERROR -3 : SCRIPT NOT FOUND\n");
        break;
    case -4:
        printf("ERROR -4 : UNKNOWN COMMAND. TRY 'help'\n");
        break;
    case -5:
        printf("ERROR -5 : NOT ENOUGH RAM SPACE\n");
        break;
    case -6:
        printf("ERROR -6 : LOADED ALREADY \n");
        break;
    }

    return;
}

int parseInput(char ui[])
{
    
    char tmp[200];
    int a, b;
    char *words[10];
    int w = 0; // wordsIdx
    for (int i = 0; i < 10; i++)
    {
        words[i] = "_NONE_";
    }
    for (a = 0; ui[a] == ' ' && a < 1000; a++)
        ; // skip white spaces
    while (ui[a] != '\0' && ui[a] != '\n' && a < 1000)
    {
        for (b = 0; ui[a] != '\0' && ui[a] != '\n' && ui[a] != '\r' && ui[a] != ' ' && a < 1000; a++, b++)
            tmp[b] = ui[a]; // extract a word
        tmp[b] = '\0';
        words[w] = strdup(tmp);
        if (ui[a] == '\0' || ui[a] == '\n' || ui[a] == '\r')
            break;
        for (; ui[a] == ' ' && a < 1000; a++)
            ; // skip white spaces
        w++;
    }
    return (interpreter(words));
    
}

/*
main loop where 
users gets to use the shell.
*/
int shellUI()
{
    printf(
        "\n----------------------------------\nKernel 1.0 loaded!\nWelcome to the Ahmed Azhar Shell!\nShell Version 2.0 Updated February 2020\n----------------------------------\n");
    char prompt[15] = {'$', '\0'};
    char userinput[1000];
    int errorCode;

    while (1)
    {
        // prints prompt
        printf("%s", prompt);
        //gets user input
        fgets(userinput, 999, stdin);
        // parses and interprets the command
        errorCode = parseInput(userinput);
        //If the user entered the "quit" command
        if (errorCode == 1)
        {
            printf("----------------------------------\nExiting Ahmed Azhar Shell. Goodbye...\n----------------------------------\n");
            break;
            //else if an error occurred, display what that error is
        }
        else if (errorCode != 0)
        {
            //removing the extra carriage return
            userinput[strlen(userinput) - 1] = '\0';
            displayCode(errorCode, userinput);
        }
    }
    return 0;
}
