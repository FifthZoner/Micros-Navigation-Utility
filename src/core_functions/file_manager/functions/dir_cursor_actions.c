// corresponding header
#include "dir_cursor_actions.h"

#include <stdint.h>

#include <stdio.h>

// calculates borders to have the cursor on in the middle
void mnu_filesystem_cursor_recalculate_borders(uint32_t* cursor_position, uint32_t* lowerr, uint32_t* upperr, uint32_t length){


    // more than the screen
    if (length > 23){
        int32_t lower = *cursor_position - 11;
        int32_t upper = *cursor_position + 12;

        if (lower < 0){
            upper -= lower;
            lower = 0;
        }

        if (upper > (int32_t)length){
            upper = (int32_t)length;
        }

        lower = upper - 23;
        if (lower < 0){
            lower = 0;
        }

        *upperr = upper;
        *lowerr = lower;
    }
    else{
        *upperr = length;
        *lowerr = 0;
    }

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
        mnu_filesystem_cursor_recalculate_borders(&pointer->cursor_position, &pointer->lower_limit, &pointer->upper_limit, pointer->file_list.length);
    }
}

// moves the cursor down with looping and border changes
void mnu_filesystem_cursor_move_down(mnu_filesystem_navigation_struct* pointer){

    // not empty check
    if (pointer->file_list.length > 0){

        // cursor moving with looping
        if (pointer->cursor_position < pointer->file_list.length - 1){
            pointer->cursor_position++;
        }
        else {
            pointer->cursor_position = 0;
        }

        // border moving
        mnu_filesystem_cursor_recalculate_borders(&pointer->cursor_position, &pointer->lower_limit, &pointer->upper_limit, pointer->file_list.length);
    }
}