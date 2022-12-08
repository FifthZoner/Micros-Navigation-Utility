// corresponding header
#include "dir_cursor_actions.h"

#include <stdint.h>

// calculates borders to have the cursor on in the middle
void mnu_filesystem_cursor_recalculate_borders(uint32_t* cursor_position, uint32_t* lowerr, uint32_t* upperr, uint32_t length){

    // checks if there is a reason to reacalculate
    if (length > 23){
        
        // okay I have no idea how to do it efficiently so it'll look like that

        // need to be signed for calculation
        int32_t lower; 
        uint32_t upper;

        lower = *cursor_position - 11;
        upper = *cursor_position + 12;

        // checking for edge cases
        if (lower < 0){

            // adding negative part of lower to upper
            upper -= lower;

            if (upper > length){
                upper = length;
            }

            if (upper > 23){

                upper = 23;
            }
        }
        else if (upper > length){

            lower = upper - 23;

            if (lower < 0){
                lower = 0;
            }
        }
        
        *lowerr = lower;
        *upperr = upper;

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
            pointer->cursor_position = pointer->lower_limit;
        }

        // border moving
        mnu_filesystem_cursor_recalculate_borders(&pointer->cursor_position, &pointer->lower_limit, &pointer->upper_limit, pointer->file_list.length);
    }
}