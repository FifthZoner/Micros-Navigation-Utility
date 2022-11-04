#ifndef NAVIGATION_STRUCT_FUNCTIONS_H
#define NAVIGATION_STRUCT_FUNCTIONS_H

// the struct file
#include "navigation_struct.h"

// constructs the given struct name of which is so long I prefer to write this instead of it
mnu_filesystem_navigation_struct mnu_filesystem_navigation_struct_constructor();

// deallocates all the allocated memory
void mnu_filesystem_navigation_struct_free(mnu_filesystem_navigation_struct* pointer);

#endif