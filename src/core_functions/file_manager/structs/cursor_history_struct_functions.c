// corresponding header
#include "cursor_history_struct_functions.h"
#include "cursor_history_struct.h"
#include "navigation_struct.h"

#include <string.h>
#include <stdint.h>

// constructor of the struct, always get initial value from this, path_main for checking of current depth
mnu_filesystem_cursor_history_struct mnu_cursor_history_struct_constructor(const char* path_main){

    // to be passed
    mnu_filesystem_cursor_history_struct temp;

    // initial value
    temp.array_length = 1;

    // looks for slashes, starts at the second one after 2'nd index of for example A:/..., as the first one is included
    for (uint16_t n = 3; n < strlen(path_main); n++){
        if (path_main[n] == '/'){
            temp.array_length++;
        }
    }

    // allocating memory
    temp.position_array = (uint32_t*)calloc(0, temp.array_length * sizeof(uint32_t));


    return temp;
}

// frees the struct things that need freeing
void mnu_cursor_history_struct_free(mnu_filesystem_cursor_history_struct* pointer){

    free(pointer);
}

// gets the data from a level below, also reallocs the array to delete the now useless old position
// needs navigation info and was_deleted for checking if it does have a proper index, also checks for unforseen happenings
// saves to navigation struct
void mnu_cursor_history_struct_get_pervious(mnu_filesystem_cursor_history_struct* pointer, 
mnu_filesystem_navigation_struct* navigation_info, bool was_deleted){



    
}

// adds a value to the array, always call when advancing in dir
void mnu_cursor_history_struct_add_next(uint32_t index){

}