// corresponding header
#include "main_loop.h"

#include <stdio.h>

#include "file_manager/structs/navigation_struct_functions.h"
#include "file_manager/functions/dir_movement.h"

// the main function that runs all of the program
void mnu_run_main_loop(char* path_main){
    printf("Loop works!\n");

    // navigation struct that will be passed to all the lovely functions
    mnu_filesystem_navigation_struct navigation_info = mnu_filesystem_navigation_struct_constructor();



    // deallocating the path string
    free(path_main);
}