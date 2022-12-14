#ifndef FILE_LIST_STRUCT_H
#define FILE_LIST_STRUCT_H

#include <stdint.h>
#include <stdlib.h>

// This one is used to store data about files for displaying and actions
typedef struct mnu_filesystem_file_list_struct{

    // yes, I am aware that this uses quite a bit of memory, however this is for faster reaction to user action

    // length of the list, int is a bit of an overkill, yes, however propably there is someone who would like to add over 65k files in one dir
    uint32_t length;
    // list of generated names of files/dirs, to be displayed
    char** names;
    // to see if something is a dir or a file, using a char and not a bool because I don't care enough to search for a way to use it on micros
    bool* are_they_dirs;
    // file sizes
    uint32_t* file_sizes;

}mnu_filesystem_file_list_struct;

#endif