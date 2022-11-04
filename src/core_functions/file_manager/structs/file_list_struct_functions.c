// corresponding header
#include "file_list_struct_functions.h"

// others
#include <stdlib.h>

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

        free(pointer->list[n]);
        free(pointer->names[n]);
    }

    // this can't be done in a loop :(
    if (pointer->length > 0){
        free(pointer->are_they_dirs);
    }

    // just to be safe
    pointer->length = 0;
}