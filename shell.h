
#ifndef SHELL_H
#define SHELL_H

void displayCode(int errorCode,char* command);

int parseInput(char ui[]);

int shellUI();

#endif