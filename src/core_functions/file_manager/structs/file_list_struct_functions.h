#ifndef FILE_LIST_STRUCT_FUNCTIONS_H
#define FILE_LIST_STRUCT_FUNCTIONS_H

// the struct file
#include "file_list_struct.h"
#include "cursor_history_struct.h"

#include <stdint.h>

// returns an empty mnu_filesystem_file_list_struct struct for use without sigservs or something
mnu_filesystem_file_list_struct mnu_filesystem_file_list_struct_constructor();

// frees all the data from the struct for hopefully no memory leaks later
void mnu_filesystem_file_list_struct_free(mnu_filesystem_file_list_struct* pointer);

// fills the list with data from a given path, ALWAYS free it after this pls
void mnu_filesystem_file_list_struct_fill(mnu_filesystem_file_list_struct* pointer,
 const char* path_main, uint32_t* lower_border, uint32_t* upper_border, uint32_t* cursor_position, 
 bool is_cursor_saved, bool was_deleted, mnu_filesystem_cursor_history_struct* cursor_history);


#endif