// corresponding header
#include "file_actions.h"

#include "misc/checking_functions.h"
#include "../../misc/keybind_enum.h"
#include "misc/recursive_delete.h"

#include <micros/micros_filesystem.h>
#include <micros/micros_console.h>
#include <micros/micros_keyboard.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

// gets and prepares name for the file
char* local_get_directory_name(){

    // for some reason name length limit is 8 characters even though name from dir info has 32, buffer of 128 to guard against people's thinking
    char* name =  (char*)malloc(129 * sizeof(char));

    // clearing the console
    micros_console_clear();

    // input prompt
    micros_console_set_background_color(micros_console_color_black);
    micros_console_set_foreground_color(micros_console_color_light_gray);

    printf("Please input new directory name (up to 8 characters):\n");

    // maybye input will be colored?
    micros_console_set_foreground_color(micros_console_color_cyan);

    // getting right amount of characters
    gets(name);

    // shortening to 8
    if (strlen(name) > 8){
        name[8] = '\0';
    }

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
// 0 if not
uint8_t mnu_filesystem_directory_create(const char* path_main){

    char* name = local_get_directory_name();

    if (strlen(name) == 0){
        free(name);
        return 0;
    }

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

char* local_get_file_name(){

    // for some reason name length limit is 12 characters even though name from dir info has 32, buffer of 128 to guard against people's thinking
    char* name =  (char*)malloc(127 * sizeof(char));

    // clearing the console
    micros_console_clear();

    // input prompt
    micros_console_set_background_color(micros_console_color_black);
    micros_console_set_foreground_color(micros_console_color_light_gray);

    printf("Please input new file name (up to 8 characters + dot + 3 for extension):\n");

    // maybye input will be colored?
    micros_console_set_foreground_color(micros_console_color_yellow);

    // getting right amount of characters
    gets(name);

    // shortening to 12
    if (strlen(name) > 12){
        name[12] = '\0';
    }

    // checking for newlines
    for (uint8_t n = 0; n < 13; n++){
        if (name[n] == '\n'){
            name[n] = '\0';
        }
    }

    return name;

}

// asks user for name and creates a new dile in a given dir,
// returns 1 if succesful
// in that case always fill file list
// 0 if not
uint8_t mnu_filesystem_file_create(const char* path_main){

    // file name size limit seems to be 12

    char* name = local_get_file_name();

    if (strlen(name) == 0){
        free(name);
        return 0;
    }

    // creating path
    char* path_full = (char*)malloc((strlen(path_main) + strlen(name) + 1) * sizeof(char));

    strcpy(path_full, path_main);
    strcat(path_full, name);

    free(name);

    // information in case it takes long
    micros_console_set_foreground_color(micros_console_color_light_gray);

    printf("Creating new file at:\n%s\n", path_full);

    bool result = micros_filesystem_create_file(path_full);

    free(path_full);

    return result;
}

// deletes dir
uint8_t local_delete_dir(char* path_full){

    uint8_t result = micros_filesystem_delete_directory(path_full);

    free(path_full);

    return result;

}

// deletes a directory after asking for a confirmation
// if it's empty deletes instantly, if not then asks for confirmation to delete recursively
// returns 1 when succesful
uint8_t mnu_filesystem_directory_delete(const char* path_main, const char* name){

    // getting full path
    char* path_full = (char*)malloc((strlen(path_main) + strlen(name) + 1));

    // filling path
    strcpy(path_full, path_main);
    strcat(path_full, name);

    // emptyness check
    if (mnu_filesystem_directory_is_empty(path_full) == 1){

        // without asking for confirmation

        uint8_t result = micros_filesystem_delete_directory(path_full);

        free(path_full);

        return result;
    }
    else{

        // with confirmation

        micros_console_clear();
        micros_console_set_background_color(micros_console_color_black);
        micros_console_set_foreground_color(micros_console_color_light_gray);
        printf("Are you sure that you want to delete this directory and it's contents?\n");
        printf("Press confirm button to accept, any other to cancel:\n");

        // waiting for enter
        do{
        micros_keyboard_scan_ascii_pair key_pair;

        micros_keyboard_wait_for_key_press(&key_pair);

        switch(key_pair.scancode){

            // does the deletion
            case mnu_keybind_confirm:

                return mnu_filesystem_recursive_delete(path_full);

                break;

            default:
                // cancels
                break;
                
            }
        }
        while (0);
    }


    free(path_full);

    return 0;

}

// deletes file
uint8_t local_delete_file(char* path_full){

    uint8_t result = micros_filesystem_delete_file(path_full);

    free(path_full);

    return result;

}

// deletes a file after getting a confirmation
// returns 1 when successful
uint8_t mnu_filesystem_file_delete(const char* path_main, const char* name){

    // getting full path
    char* path_full = (char*)malloc((strlen(path_main) + strlen(name) + 1));

    // filling path
    strcpy(path_full, path_main);
    strcat(path_full, name);

    // with confirmation

    micros_console_clear();
    micros_console_set_background_color(micros_console_color_black);
    micros_console_set_foreground_color(micros_console_color_light_gray);
    printf("Are you sure that you want to delete this file and it's contents?\n");
    printf("Press confirm button to accept, any other to cancel:\n");

    // waiting for enter
    do{
        micros_keyboard_scan_ascii_pair key_pair;

        micros_keyboard_wait_for_key_press(&key_pair);

        switch(key_pair.scancode){

            // does the deletion
            case mnu_keybind_confirm:

                return local_delete_file(path_full);

                break;

            default:
                // cancels
                break;
                
            }
        }
    while (0);

    free(path_full);

    return 0;
}