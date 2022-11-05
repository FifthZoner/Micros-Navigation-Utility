// corresponding header
#include "file_list_struct_functions.h"

// others
#include <stdlib.h>
#include <micros/micros_filesystem.h>

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
    }

    // just to be safe
    pointer->length = 0;
}

// prepares things based on one index from the list, pass path from list, name from names and bool from are_they_dirs
// returns the name
char* local_fill_index(char* path, char* name, bool* is_it_dir){
    
    // checking if it's a dir and giving bool it's value
    *is_it_dir = micros_filesystem_is_directory(path);

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

    return name;
}

// fills the list with data from a given path, ALWAYS free it after this pls
void mnu_filesystem_file_list_struct_fill(mnu_filesystem_file_list_struct* pointer, const char* path_main, uint32_t* lower_border, uint32_t* upper_border){

    // freeing in case of 


    // temporary list of paths to be used in filling the struct
    char** list;

    // getting amount of files in dir
    pointer->length = micros_filesystem_get_entries_count_in_directory(path_main);

    // preparing space
    list = (char**)malloc(pointer->length * sizeof(char*));
    pointer->names = (char**)malloc(pointer->length * sizeof(char*));
    pointer->are_they_dirs = (bool*)malloc(pointer->length * sizeof(bool));

    // getting file paths
    if (micros_filesystem_get_entries_in_directory(path_main, list)){
        // everything is fine, time to do stuff

        // preparing names and bools for each entry
        for (uint32_t n = 0; n < pointer->length; n++){
            pointer->names[n] = local_fill_index(list[n], pointer->names[n], &pointer->are_they_dirs[n]);
        }

        // freeing, indexes were freed earlier
        free(list);

        // borders for displaying
        *lower_border = 0;
        *upper_border = pointer->length;

        if (*upper_border > 22){
            *upper_border = 22;
        }
    }
    else{
        // Oh no, nothing? Could I have broken it? Should not happen when using mnu with correct argv[1]

        // freeing things, cannot call function because indexes aren't filled
        free(list);
        free(pointer->names);
        free(pointer->are_they_dirs);
        pointer->length = 0;
    }

}