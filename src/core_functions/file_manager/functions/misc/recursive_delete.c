// corresponding header
#include "recursive_delete.h"

#include <micros/micros_filesystem.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// for debug
//#include <micros.h>

// does things for a single dir/file
void local_handle_entry(const char* path, char* path_gotten){

    // creating a new path

    // finding the last slash before the name

    // variable that will be used to fill
        uint16_t n = strlen(path_gotten) - 2;

    // searching for the index of the last slash
    for (; path_gotten[n] != '/'; n--){}

    // allocating for new path
    char* path_new = (char*)malloc((strlen(path) + strlen(path_gotten) - n));

    // filling
    strcpy(path_new, path);
    // name copy here
    uint16_t path_index = strlen(path);
    for (uint16_t m = n + 1; m <  strlen(path) + strlen(path_gotten) - n; m++){

        path_new[path_index] = path_gotten[m]; 
        path_index++;
    }

    printf("%s\n", path_new);

    // for debug
    //micros_process_current_process_sleep(100);
    
    // proper deletion
    if (micros_filesystem_is_directory(path_new)){
        // if there's more
        mnu_filesystem_recursive_delete(path_new);
    }
    else{
        micros_filesystem_delete_file(path_new);
    }

    // freeing memory
    free(path_gotten);
    free(path_new);
}

// recursive deletion main function
// deletes a dir and all it's subdirs and files
// pass path to dir
// hopefull does not cause memory leaks
uint8_t mnu_filesystem_recursive_delete(const char* path){

    // getting amount of things to delete
    uint32_t entry_amount = micros_filesystem_get_entries_count_in_directory(path);

    // checking if empty
    if (entry_amount == 0){

        micros_filesystem_delete_directory(path);

        return 1;
    }

    // allocating
    char** entries = (char**)malloc(entry_amount * sizeof(char*));

    // doing things
    micros_filesystem_get_entries_in_directory(path, entries);

    // does things for each entry
    for (uint32_t n = 0; n < entry_amount; n++){

        local_handle_entry(path, entries[n]);

    }

    
    if (entry_amount > 0){
        free(entries);
    }

    // deleteing the folder
    return micros_filesystem_delete_directory(path);
}