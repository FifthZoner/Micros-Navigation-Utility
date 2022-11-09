// corresponding header
#include "checking_functions.h"

#include <stdlib.h>
#include <string.h>
#include <micros/micros_filesystem.h>

// checks if given dir is empty
// returns 0 when not empty or not existing
// returns 1 when empty
uint8_t mnu_filesystem_directory_is_empty(const char* path_full){

    // proper check
    if (micros_filesystem_get_entries_count_in_directory(path_full) == 0){

        return 1;
    }

    return 0;
}