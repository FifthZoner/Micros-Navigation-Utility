// corresponding header
#include "dir_cursor_actions.h"

#include <stdint.h>

// calculates borders to have the cursor on in the middle
void local_cursor_recalculate_borders(mnu_filesystem_navigation_struct* pointer){

    // checks if there is a reason to reacalculate
    if (pointer->file_list.length > 23){
        
        // okay I have no idea how to do it efficiently so it'll look like that

        // need to be signed for calculation
        int32_t lower; 
        uint32_t upper;

        lower = pointer->cursor_position - 11;
        upper = pointer->cursor_position + 12;

        // checking for edge cases
        if (lower < 0){

            // adding negative part of lower to upper
            upper -= lower;

            if (upper > pointer->file_list.length){
                upper = pointer->file_list.length;
            }

            if (upper > 23){

                upper = 23;
            }
        }
        else if (upper > pointer->file_list.length){

            lower = upper - 23;

            if (lower < 0){
                lower = 0;
            }
        }
        
        pointer->lower_limit = lower;
        pointer->upper_limit = upper;

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
        local_cursor_recalculate_borders(pointer);
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
        local_cursor_recalculate_borders(pointer);
    }
}