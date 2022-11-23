#ifndef CURSOR_HISTORY_STRUCT_H
#define CURSOR_HISTORY_STRUCT_H

#include <stdint.h>

typedef struct mnu_filesystem_cursor_history_struct{

    // this is going to contain positions
    // they need to be reduced by 1 or 0 if index was the first in case of deletion
    // needs to have path chacked at the beginning to fill the proper lengt with 0's
    uint32_t* position_array;
    // contains info about the length of the array
    uint8_t array_length;

}mnu_filesystem_cursor_history_struct;

#endif