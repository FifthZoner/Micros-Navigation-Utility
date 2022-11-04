// welcome my dear code diver, this is the main file of the glorious thing called MicrOS Navigation Utility or MNU!
// This is my attempt at making a file explorer for the incredible, best that exists os, that is called MicrOS
// Written by Szymon Jabloński for SKNI "KOD"

// normal headers
#include <string.h>
#include <micros.h>

// my retarded headers
#include "core_functions/main_loop.h"

// main function of the program
int main(int argc, const char* argv[]){

    // some MicrOS things
    micros_process_set_current_process_name("MNU");
    micros_console_set_cursor_visibility(false);

    // current path to argv to avoid changing it
    char* path_main = malloc(strlen(argv[1]) + 1);
    path_main[0] = '\0';
    strcpy(path_main, argv[1]);

    mnu_run_main_loop(path_main);

    return 0;
}