// corresponding header
#include "dir_movement.h"
// other headers
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// this file contains functions used to navigate between directories in the file exploration stage

// adds given dir name to the path, pass path_main and the name of the dir to use from the list
// returns changed char*
char* mnu_filesystem_directory_advance(char* path_main, const char* name){


    // realloc cannot be used here as well

    // fix code

    // allocating
    char* path_new =(char*)malloc((strlen(path_main) + strlen(name) + 1) * sizeof(char));

    // filling
    strcpy(path_new, path_main);
    strcat(path_new, name);

    // freeing main
    free(path_main);


    path_main = path_new;
        
    return path_new;
}

// changes the path to go back one directory or stays the same if in the lowest one
// returns changed char* or non changed one if there was no way to change it
char* mnu_filesystem_directory_unadvance(char* path_main){
    // checking if the dir isn't like A:/
    if (strlen(path_main) > 3){
        

        // for some reason the bug with realloc seems to have happened again so let's do it

        // variable that will be used to alloc
        uint16_t n = strlen(path_main) - 2;

        // searching for the index of the last slash
        for (; path_main[n] != '/'; n--){}

        // end of new string
        path_main[n + 1] = '\0';

        // fix code

        // allocating
        char* path_new =(char*)malloc((n + 2) * sizeof(char));

        // filling
        strcpy(path_new, path_main);

        // freeing main
        free(path_main);


        path_main = path_new;
        
        return path_main;
    }

    // returns the same variable if nothing happended
    return path_main;
}