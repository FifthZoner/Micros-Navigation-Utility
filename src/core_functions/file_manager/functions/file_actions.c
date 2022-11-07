// corresponding header
#include "file_actions.h"

#include <micros/micros_filesystem.h>
#include <micros/micros_console.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// gets and prepares name for the file
char* local_get_directory_name(){

    // for some reason name length limit is 8 characters even though name from dir info has 32
    char* name =  (char*)malloc(9 * sizeof(char));

    // clearing the console
    micros_console_clear();

    // input prompt
    micros_console_set_background_color(micros_console_color_black);
    micros_console_set_foreground_color(micros_console_color_light_gray);

    printf("Please input new directory name (up to 8 characters):\n");

    // maybye input will be colored?
    micros_console_set_foreground_color(micros_console_color_cyan);

    // getting right amount of characters
    scanf("%8s", name);

    // checking for newlines
    for (uint8_t n = 0; n < 9; n++){
        if (name[n] == '\n'){
            name[n] = '\0';
        }
    }

    return name;
}

// asks user for name and creates a new dir in a given dir,
// returns 1 if succesful
// in that case always fill file list
uint8_t mnu_filesystem_directory_create(const char* path_main){

    char* name = local_get_directory_name();

    // creating path
    char* path_full = (char*)malloc((strlen(path_main) + strlen(name) + 1) * sizeof(char));

    strcpy(path_full, path_main);
    strcat(path_full, name);

    free(name);

    // information in case it takes long
    micros_console_set_foreground_color(micros_console_color_light_gray);

    printf("Creating new directory at:\n%s\n", path_full);

    bool result = micros_filesystem_create_directory(path_full);

    free(path_full);

    return result;
}