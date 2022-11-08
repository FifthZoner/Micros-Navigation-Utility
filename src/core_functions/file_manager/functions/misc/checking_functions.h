#ifndef CHECKING_FUNCTIONS_H
#define CHECKING_FUNCTIONS_H

#include <stdint.h>

// checks if given dir is empty
// returns 0 when not empty or not existing
// returns 1 when empty
uint8_t mnu_filesystem_directory_is_empty(const char* path_main, const char* name);

#endif