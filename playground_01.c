// I am making this playground to learn and test direct.h library . So that i dont mess up the main code while checking . 

// Currently I am trying to read the directory using dirent.h

#include <stdio.h>
#include <dirent.h>

int main(){

    DIR *directory = opendir("./Imagess"); // DIR is a special type of data type provided by dirent.h . * for pointer and opendir is a function provided by dirent.h whose job is to just open the directory. and "." here this dot means current directory.

    if(directory == NULL){
        printf("Could not open directory.\n");
        return 1;
    }else{
        printf("Successfully opend the directory.\n");
    }
    return 0;
}