#ifndef FILE_LIST_STRUCT_FUNCTIONS_H
#define FILE_LIST_STRUCT_FUNCTIONS_H

// the struct file
#include "file_list_struct.h"

// returns an empty mnu_filesystem_file_list_struct struct for use without sigservs or something
mnu_filesystem_file_list_struct mnu_filesystem_file_list_struct_constructor();

// frees all the data from the struct for hopefully no memory leaks later
void mnu_filesystem_file_list_struct_free(mnu_filesystem_file_list_struct* pointer);

#endif