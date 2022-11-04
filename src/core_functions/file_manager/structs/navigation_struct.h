#ifndef NAVIGATION_STRUCT_H
#define NAVIGATION_STRUCT_H

#include "file_list_struct_functions.h"

// This struct serves as a way for reducing the amount of pointers passed to functions used to navigate the dir list
// Functions for it are defined in navigation_struct_functions files
// never declare it without corresponding function to give if initial values!
typedef struct mnu_filesystem_navigation_struct{

    // position of the cursor relative to the start of file list
    unsigned short int cursor_position;
    // file list structure
    mnu_filesystem_file_list_struct file_list;
    // index from which to display files
    unsigned short int lower_limit;
    // index to which to display files, should be around upper_limit = lower_limit + <0, 22>
    unsigned short int upper_limit;

}mnu_filesystem_navigation_struct;

#endif