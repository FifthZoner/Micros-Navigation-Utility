#include "../drawing/elements/misc/file_list.h"


// this struct contains the general data used to move around the program, contained in one neat struct
struct mnu_info_struct{

    // where is the cursor
    unsigned short int cursor_position;
    // file list
    struct mnu_file_list main_file_list;
    // from where to display files
    unsigned short int lower_limit;
    // to where to display files
    unsigned short int upper_limit;

};

// function that needs to be called before using the struct to prepare is's values
void mnu_info_struct_prepare(struct mnu_info_struct* pointer){

    pointer->cursor_position = 0;
    pointer->main_file_list.length = 0;
    pointer->lower_limit = 0;
    pointer->upper_limit = 0;
}
