// corresponding header
#include "recursive_delete.h"

#include <micros/micros_filesystem.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// does things for a single dir/file
void local_handle_entry(const char* path, char* path_gotten){

    // creating a new path

    // finding the last slash before the name

    // variable that will be used to realloc
        uint16_t n = strlen(path_gotten) - 2;

    // searching for the index of the last slash
    for (; path_gotten[n] != '/'; n--){}

    // allocating for new path
    char* path_new = (char*)malloc((strlen(path) + strlen(path_gotten) - n));

    // filling
    strcpy(path_new, path);
    // name copy here

    // freeing memory
    free(path_gotten);
}

// recursive deletion main function
// deletes a dir and all it's subdirs and files
// pass path to dir
// hopefull does not cause memory leaks
void mnu_filesystem_recursive_delete(const char* path){

    // getting amount of things to delete
    uint32_t entry_amount = micros_filesystem_get_entries_count_in_directory(path);

    // checking if empty
    if (entry_amount == 0){

        micros_filesystem_delete_directory(path);

        return;
    }

    // allocating
    char** entries = (char*)malloc(entry_amount * sizeof(char*));

    // doing things
    micros_filesystem_get_entries_in_directory(path, entries);

    // does things for each entry
    for (uint32_t n = 0; n < entry_amount; n++){

        local_handle_entry(path, entries[n]);

    }


    free(entries);
}