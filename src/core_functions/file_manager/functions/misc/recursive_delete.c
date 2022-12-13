// corresponding header
#include "recursive_delete.h"

#include <micros.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// pass path to dir entry is in and path gotten from micros
uint8_t local_handle_entry(const char* path_before, const char* entry_path){

    // generating path in format of X:/.../name/ or X:/.../name.extension from entry_path without drive letter and path_before without the name
    // searching for name length
    uint16_t length = 1;
    uint16_t path_before_length = strlen(path_before);
    uint16_t entry_length = strlen(entry_path);
    for (;entry_path[entry_length - 1 - length] != '/'; length++){}
    // X:/.../ + (name/ v name.extension) + '\0'
    char* path = (char*)malloc((path_before_length + length + 1) * sizeof(char));

    strcpy(path, path_before);
    for (uint16_t n = 0; n < length; n++){
        path[path_before_length + n] = entry_path[entry_length - length + n];
    }
    path[path_before_length + length] = '\0';

    // proper deletion and possible further recursion
    if (micros_filesystem_is_directory(path)){

        uint8_t result = mnu_filesystem_recursive_delete(path);

        free(path);

        return result;

    }
    else if (micros_filesystem_is_file(path)){

        // info
        micros_console_set_foreground_color(micros_console_color_light_gray);
        printf("Deleting at: ");
        micros_console_set_foreground_color(micros_console_color_yellow);
        printf("%s\n", path);
        micros_process_current_process_sleep(100);

        uint8_t result = micros_filesystem_delete_file(path);

        free(path);

        return result;
    }

    return 0;
}


// recursive deletion main function
// deletes a dir and all it's subdirs and files
uint8_t mnu_filesystem_recursive_delete(const char* path){

    // checking if given dir is empty
    uint32_t entry_amount = micros_filesystem_get_entries_count_in_directory(path);

    if (entry_amount > 0){

        // handling all the entries
        char** list = (char**)malloc(entry_amount * sizeof(char*));
        micros_filesystem_get_entries_in_directory(path, list);

        // racursion or not for each entry
        for (uint32_t n = 0; n < entry_amount; n++){

            local_handle_entry(path, list[n]);


            free(list[n]);
        }


        free(list);
    }

    // info
    micros_console_set_foreground_color(micros_console_color_light_gray);
    printf("Deleting at: ");
    micros_console_set_foreground_color(micros_console_color_cyan);
    printf("%s\n", path);

    // for now no deletion
    return micros_filesystem_delete_directory(path);
}