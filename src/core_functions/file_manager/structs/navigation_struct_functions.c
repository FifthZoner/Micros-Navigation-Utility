// corresponding header
#include "navigation_struct_functions.h"

// constructs the given struct name of which is so long I prefer to write this instead of it
mnu_filesystem_navigation_struct mnu_filesystem_navigation_struct_constructor(){

    mnu_filesystem_navigation_struct constructed;
    constructed.cursor_position = 0;
    constructed.lower_limit = 0;
    constructed.upper_limit = 0;
    constructed.file_list = mnu_filesystem_file_list_struct_constructor();

    return constructed;
}

// deallocates all the allocated memory
void mnu_filesystem_navigation_struct_free(mnu_filesystem_navigation_struct* pointer){

    // frees the list struct, so no need to do that outside of this
    mnu_filesystem_file_list_struct_free(&pointer->file_list);
}