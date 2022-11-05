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

    // extends the space for path: size of path + size of dir name + space for slash + space for \0
    path_main = realloc(path_main, (strlen(path_main) + strlen(name) + 1) * sizeof(char));

    // adding name to the end of path to achieve something like: <path>/<name>\0
    strcat(path_main, name);

    // the end of string thingy
    path_main[strlen(path_main)] = '\0';

    return path_main;
}

// changes the path to go back one directory or stays the same if in the lowest one
// returns changed char* or non changed one if there was no way to change it
char* mnu_filesystem_directory_unadvance(char* path_main){

    // checking if the dir isn't like A:/
    if (strlen(path_main) > 3){

        // for some reason the bug with realloc seems to have happened again so let's do it

        // variable that will be used to realloc
        uint16_t n = strlen(path_main) - 2;

        // searching for the index of the last slash
        for (; path_main[n] != '/'; n--){}

        // end of new string
        path_main[n + 1] = '\0';

        // fix code

        return realloc(path_main, (n + 2) * sizeof(char));
    }

    // returns the same variable if nothing happended
    return path_main;
}