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

    // starting the loop proper
    mnu_run_main_loop(path_main);

    return 0;
}