#ifndef DIR_CURSOR_ACTIONS_H
#define DIR_DURSOR_ACTIONS_H

#include "../structs/navigation_struct.h"

// recalculated the indexes to be shown
void mnu_filesystem_cursor_recalculate_borders(uint32_t* cursor_position, uint32_t* lowerr, uint32_t* upperr, uint32_t length);

// moves the cursor up with looping and border changes
void mnu_filesystem_cursor_move_up(mnu_filesystem_navigation_struct* pointer);

// moves the cursor down with looping and border changes
void mnu_filesystem_cursor_move_down(mnu_filesystem_navigation_struct* pointer);

#endif