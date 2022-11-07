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
    printf("To exit MNU press ");
    micros_console_set_foreground_color(micros_console_color_light_gray);
    printf("escape");
    micros_console_set_foreground_color(micros_console_color_black);
    printf("                                        \n");
    micros_console_set_background_color(micros_console_color_black);
    micros_console_set_foreground_color(micros_console_color_light_gray);

    // other help info
    printf("\n");
    printf("To navigate inside a directory use arrows\n");
    printf("To change directories use enter and backspace\n");
    printf("To add a new directory in current location use the keypad + button\n");
    printf("\n");
    printf("In the current state only dir exploration and creation works, more to come!\n");
    printf("Planned features will make it possible to do as much as in the main terminal\n");
}