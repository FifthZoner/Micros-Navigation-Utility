#include <stdio.h>

#include "main_loop.h"
#include "file_manager/structs/navigation_struct.h"

// the main function that runs all of the program
void mnu_run_main_loop(char* path_main){
    printf("Loop works!\n");


    // deallocating the path string
    free(path_main);
}