// corresponding header
#include "cursor_history_struct_functions.h"
#include "cursor_history_struct.h"
#include "navigation_struct.h"
#include "../functions/dir_cursor_actions.h"

#include <string.h>
#include <stdint.h>

// constructor of the struct, always get initial value from this, path_main for checking of current depth
mnu_filesystem_cursor_history_struct mnu_filesystem_cursor_history_struct_constructor(const char* path_main){

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
void mnu_filesystem_cursor_history_struct_free(mnu_filesystem_cursor_history_struct* pointer){

    if (pointer->array_length > 0){
        free(pointer);  
    }
}

// gets the data from a level below, also reallocs the array to delete the now useless old position
// needs navigation info and was_deleted for checking if it does have a proper index, also checks for unforseen happenings
// saves to navigation struct
void mnu_filesystem_cursor_history_struct_get_pervious(mnu_filesystem_cursor_history_struct* pointer, 
mnu_filesystem_navigation_struct* navigation_info, bool was_deleted){

    // if the index is within the bounds
    if (pointer->position_array[pointer->array_length - 1] < navigation_info->file_list.length){
        navigation_info->cursor_position = pointer->position_array[pointer->array_length - 1];
    }
    else {
        navigation_info->cursor_position = 0;
    }

    // shortening the array
    pointer->array_length--;
    pointer->position_array = realloc(pointer->position_array, pointer->array_length);

    // racalculating view
    mnu_filesystem_cursor_recalculate_borders(navigation_info);
}

// adds a value to the array and sets it to struct, always call when advancing in dir
void mnu_filesystem_cursor_history_struct_add_next(mnu_filesystem_cursor_history_struct* pointer, 
mnu_filesystem_navigation_struct* navigation_info, uint32_t index){

    // expanding the array
    pointer->array_length++;
    pointer->position_array = realloc(pointer->position_array, pointer->array_length);

    // setting the value
    pointer->position_array[pointer->array_length - 1] = index;
    navigation_info->cursor_position = index;

    // racalculating view
    mnu_filesystem_cursor_recalculate_borders(navigation_info);
}