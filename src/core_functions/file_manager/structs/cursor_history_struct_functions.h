#ifndef CURSOR_HISTORY_STRUCT_FUNCTIONS_H
#define CURSOR_HISTORY_STRUCT_FUNCTIONS_H

// struct file
#include "cursor_history_struct.h"
#include "navigation_struct.h"

#include <stdint.h>

// constructor of the struct, always get initial value from this, path_main for checking of current depth
mnu_filesystem_cursor_history_struct mnu_filesystem_cursor_history_struct_constructor(const char* path_main);

// frees the struct things that need freeing
void mnu_filesystem_cursor_history_struct_free(mnu_filesystem_cursor_history_struct* pointer);

// gets the data from a level below, also reallocs the array to delete the now useless old position
// needs navigation info and was_deleted for checking if it does have a proper index, also checks for unforseen happenings
// saves to navigation struct
void mnu_filesystem_cursor_history_struct_get_pervious(mnu_filesystem_cursor_history_struct* pointer, 
mnu_filesystem_navigation_struct* navigation_info, bool was_deleted);

// adds a value to the array and sets it to struct, always call when advancing in dir
void mnu_filesystem_cursor_history_struct_add_next(mnu_filesystem_cursor_history_struct* pointer, 
mnu_filesystem_navigation_struct* navigation_info, uint32_t index);

#endif