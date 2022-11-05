// corresponding header
#include "dir_cursor_actions.h"

// calculates borders to have the cursor on in the middle
void local_cursor_recalculate_borders(mnu_filesystem_navigation_struct* pointer){

}

// moves the cursor up with looping and border changes
void mnu_filesystem_cursor_move_up(mnu_filesystem_navigation_struct* pointer){

    // not empty check
    if (pointer->file_list.length > 0){

        // cursor moving with looping
        if (pointer->cursor_position > 0){
            pointer->cursor_position--;
        }
        else {
            pointer->cursor_position = pointer->upper_limit - 1;
        }

        // border moving
        local_cursor_recalculate_borders(pointer);
    }
}

// moves the cursor down with looping and border changes
void mnu_filesystem_cursor_move_down(mnu_filesystem_navigation_struct* pointer){

    // not empty check
    if (pointer->file_list.length > 0){

        // cursor moving with looping
        if (pointer->cursor_position < pointer->upper_limit - 1){
            pointer->cursor_position++;
        }
        else {
            pointer->cursor_position = pointer->lower_limit;
        }

        // border moving
        local_cursor_recalculate_borders(pointer);
    }
}