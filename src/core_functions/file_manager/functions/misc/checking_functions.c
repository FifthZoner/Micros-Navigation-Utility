// corresponding header
#include "checking_functions.h"

#include <stdlib.h>
#include <string.h>
#include <micros/micros_filesystem.h>

// checks if given dir is empty, yes, name should have a / at end, check if it's a dir before calling
// returns 0 when not empty or not existing
// returns 1 when empty
uint8_t mnu_filesystem_directory_is_empty(const char* path_main, const char* name){

    // prepares a path for check
    char* path_full = (char*)malloc((strlen(path_main) + strlen(name) + 1));

    // fills the path
    strcpy(path_full, path_main);
    strcat(path_full, name);

    // proper check
    if (micros_filesystem_get_entries_count_in_directory(path_full) == 0){

        free(path_full);

        return 1;
    }
    
    free(path_full);

    return 0;
}