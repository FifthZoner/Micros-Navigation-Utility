// corresponding header
#include "draw_file_manager.h"

#include <micros/micros_console.h>
#include <stdio.h>
#include <string.h>

#include "../structs/navigation_struct.h"

void local_draw_top(const char* path_main){

    // top info with colored f1 as it's the only useful thing there
    micros_console_set_background_color(micros_console_color_dark_gray);
    micros_console_set_foreground_color(micros_console_color_black);
    printf("Welcome to MicrOS Navigation Utility! For help press ");
    micros_console_set_foreground_color(micros_console_color_light_gray);
    printf("f5");
    micros_console_set_foreground_color(micros_console_color_black);
    printf("!\n");

    // dir current dir text
    micros_console_set_background_color(micros_console_color_black);
    micros_console_set_foreground_color(micros_console_color_light_gray);
    printf("Current dir: ");

    // current dir string
    micros_console_set_foreground_color(micros_console_color_cyan);
    printf("%s\n", path_main);

}

// draws file list
void local_draw_file_list(const mnu_filesystem_navigation_struct* navigation_info){

    micros_console_set_background_color(micros_console_color_black);

    // for each index in given range
    for (uint32_t n = navigation_info->lower_limit; n < navigation_info->upper_limit; n++){

        // <
        micros_console_set_foreground_color(micros_console_color_light_gray);
        printf(" <");

        // <> content
        if (navigation_info->file_list.are_they_dirs[n] == 1){
            // dir

            micros_console_set_foreground_color(micros_console_color_cyan);
            printf("dir ");
        
        }
        else{
            // file

            micros_console_set_foreground_color(micros_console_color_yellow);
            printf("file");

        }

        // >
        micros_console_set_foreground_color(micros_console_color_light_gray);
        printf("> ");

        // cursor
        if (navigation_info->cursor_position == n){

            micros_console_set_foreground_color(micros_console_color_green);
            printf("-> ");
            micros_console_set_foreground_color(micros_console_color_light_gray);
        }

        // file/dir names
        printf("%s", navigation_info->file_list.names[n]);
    
        micros_console_position temp;
        temp.x = 24;
        temp.y = 2 + n;

        micros_console_set_cursor_position(&temp);

        if (navigation_info->cursor_position == n){
            micros_console_set_foreground_color(micros_console_color_green);
            printf("-> ");
        }

        if (navigation_info->file_list.are_they_dirs[n] == 0){

            micros_console_set_foreground_color(micros_console_color_magenta);
            printf("%i Bytes", navigation_info->file_list.file_sizes[n]);

        }
        else{

            // file amount
            micros_console_set_foreground_color(micros_console_color_light_red);
            printf("%i Elements", navigation_info->file_list.file_sizes[n]);
        }


        printf("\n");
        
    }
}

// draws the file manager to console
void mnu_filesystem_draw_file_manager(const char* path_main, const mnu_filesystem_navigation_struct* navigation_info){

    // top info and current dir
    local_draw_top(path_main);

    // files
    local_draw_file_list(navigation_info);

}