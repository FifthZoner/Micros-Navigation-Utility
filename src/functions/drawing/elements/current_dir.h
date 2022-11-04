#ifndef HEADER_FILE
#define HEADER_FILE

#include <micros.h>
#include <stdio.h>
#include "misc/file_list.h"



// this draws current cirectory information
void mnu_draw_current_dir(char* path_main){

    micros_console_set_background_color(micros_console_color_black);
    micros_console_set_foreground_color(micros_console_color_white);

    printf("Current dir: ");

    micros_console_set_foreground_color(micros_console_color_cyan);
    printf("%s\n", path_main);
}

#endif