// corresponding header
#include "file_list_struct_functions.h"
#include "file_list_struct.h"
#include "cursor_history_struct_functions.h"

// others
#include <stdlib.h>
#include <stdio.h>
#include <micros.h>

// returns an empty mnu_filesystem_file_list_struct struct for use without sigservs or something
mnu_filesystem_file_list_struct mnu_filesystem_file_list_struct_constructor(){

    mnu_filesystem_file_list_struct constructed;
    constructed.length = 0;

    return constructed;
}

// frees all the data from the struct for hopefully no memory leaks later
void mnu_filesystem_file_list_struct_free(mnu_filesystem_file_list_struct* pointer){

    // all this checks not to free an unallocated space, I think it might break something if not checked but I'm not sure

    // will not do anything when it's empty, so that's great
    for (unsigned int n = 0; n < pointer->length; n++){

        free(pointer->names[n]);
    }

    // this can't be done in a loop
    if (pointer->length > 0){
        free(pointer->are_they_dirs);
        free(pointer->file_sizes);
        free(pointer->names);
    }

    // just to be safe
    pointer->length = 0;
}

// prepares things based on one index from the list, pass path from list, name from names and bool from are_they_dirs
// returns the name
char* local_fill_index(char* path, char* name, bool* is_it_dir, const char* path_main, uint32_t* size_pointer){
    
    // now the harder part: name getting
    // finding slash before name, same as in unadvancing
    // variable that will be used to find slash before, will contain it's index
    uint16_t n = strlen(path) - 2;

    // searching for the index of the last slash
    for (; path[n] != '/'; n--){}

    // to get the index of the first letter instead of slash
    n++;

    // allocating space for the name
    name = (char*)malloc((strlen(path) - n + 1) * sizeof(char));

    // adding values to the name
    // m is the index in the name, n is what's needed to be added to get the index in path I think
    for (uint16_t m = 0; m < strlen(path) - n; m++){

        name[m] = path[m + n];
    }

    // end of string
    name[strlen(path) - n] = '\0';

    // freeing path
    free(path);

    // dir checking
    // needs to create a path from path_main and name
    // it might be a micros fault or something but is_directory function done not work with paths gotten from system because of lack of <letter>:/ start
    // space (m)allocation
    char* path_full = (char*)malloc((strlen(path_main) + strlen(name) + 1));

    // filling
    strcpy(path_full, path_main);
    strcat(path_full, name);

    // check proper
    

    *is_it_dir = micros_filesystem_is_directory(path_full);
    if (*is_it_dir == 0){
        micros_filesystem_file_info file_info;
        micros_filesystem_get_file_info(path_full, &file_info);
        *size_pointer = file_info.size;
    }
    else{
        *size_pointer = micros_filesystem_get_entries_count_in_directory(path_full);
    }
   

    // freeing
    free(path_full);

    return name;
}

// fills the list with data from a given path, ALWAYS free it after this pls
void mnu_filesystem_file_list_struct_fill(mnu_filesystem_file_list_struct* pointer,
 const char* path_main, uint32_t* lower_border, uint32_t* upper_border, uint32_t* cursor_position, 
 bool is_cursor_saved, bool was_deleted, mnu_filesystem_cursor_history_struct* cursor_history, bool moved_dir){

    // freeing in case of it being full
    mnu_filesystem_file_list_struct_free(pointer);

    // temporary list of paths to be used in filling the struct
    char** list;
    
    // getting amount of files in dir
    pointer->length = micros_filesystem_get_entries_count_in_directory(path_main);

    // preparing space
    list = (char**)malloc(pointer->length * sizeof(char*));
    pointer->names = (char**)malloc(pointer->length * sizeof(char*));
    pointer->are_they_dirs = (bool*)malloc(pointer->length * sizeof(bool));
    pointer->file_sizes = (uint32_t*)malloc(pointer->length * sizeof(uint32_t));

    // getting file paths
    if (micros_filesystem_get_entries_in_directory(path_main, list)){
        // everything is fine, time to do stuff

        // preparing names and bools for each entry
        for (uint32_t n = 0; n < pointer->length; n++){
            pointer->names[n] = local_fill_index(list[n], pointer->names[n], &pointer->are_they_dirs[n], path_main, &pointer->file_sizes[n]);
        }

        // freeing, indexes were freed earlier
        free(list);

        // borders for displaying
        *lower_border = 0;
        *upper_border = pointer->length;

        if (*upper_border > 23){
            *upper_border = 23;
        }
    }
    else{
        // Oh no, nothing? Could I have broken it? Should not happen when using mnu with correct argv[1]

        // freeing things, cannot call function because indexes aren't filled
        free(list);
        free(pointer->names);
        free(pointer->are_they_dirs);
        free(pointer->file_sizes);
        pointer->length = 0;
    }

    if (moved_dir){
        if (is_cursor_saved){

            // proper saved cursor position
            mnu_filesystem_cursor_history_struct_get_pervious(cursor_history, pointer, was_deleted, cursor_position, lower_border, upper_border);
        }
        else{
        
            mnu_filesystem_cursor_history_struct_add_next(cursor_history, pointer, *cursor_position, cursor_position, lower_border, upper_border);

            // cursor zeroing
            *cursor_position = 0;
        }
    }
}