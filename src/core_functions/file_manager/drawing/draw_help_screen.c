// corresponding header
#include "draw_help_screen.h"

// others
#include <stdio.h>
#include <micros/micros_console.h>

// draws the help screen, it's static so there's no need for input
void mnu_filesystem_draw_help_screen(){

    // prints the help screen
    micros_console_set_background_color(micros_console_color_dark_gray);
    micros_console_set_foreground_color(micros_console_color_black);
    printf("Welcome to MicrOS Navigation Utility's help screen!             \n");
    printf("To exit this state press "); 
    micros_console_set_foreground_color(micros_console_color_light_gray);
    printf("f5");
    micros_console_set_foreground_color(micros_console_color_black);
    printf("                                     \n");
    micros_console_set_background_color(micros_console_color_black);
    micros_console_set_foreground_color(micros_console_color_light_gray);

}