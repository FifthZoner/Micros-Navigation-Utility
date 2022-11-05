#ifndef NAVIGATION_STRUCT_H
#define NAVIGATION_STRUCT_H

#include "file_list_struct_functions.h"

#include <stdint.h>

// This struct serves as a way for reducing the amount of pointers passed to functions used to navigate the dir list
// Functions for it are defined in navigation_struct_functions files
// never declare it without corresponding function to give if initial values!
typedef struct mnu_filesystem_navigation_struct{

    // position of the cursor relative to the start of file list
    uint32_t cursor_position;
    // file list structure
    mnu_filesystem_file_list_struct file_list;
    // index from which to display files
    uint32_t lower_limit;
    // index + 1 to which to display files, should be around upper_limit = lower_limit + <0, 23>
    // not just an index to maybye limit comparitions and to allow for use of unsigned variables
    uint32_t upper_limit;

}mnu_filesystem_navigation_struct;

#endif