#include<stdio.h>
#include<stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include"ram.h"
#include"kernel.h"

void clear_BackingStore(){
    DIR *directFind;
    directFind = opendir("BackingStore");
    if (directFind)
    {   
        remove("BackingStore/rem.txt"); //delete that file
        closedir(directFind);
        rmdir("BackingStore");
        mkdir("BackingStore", S_IRWXU); //S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH
    }
    else{
        mkdir("BackingStore", S_IRWXU);
    }
}

void boot(){
    clear_BackingStore();
}

int main(int argc, char const *argv[])
{   
    
   int error=0;
   boot();  
   
   //error = kernel();  
   return error;
}