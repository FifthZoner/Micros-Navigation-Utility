#ifndef HEADER_FILE
#define HEADER_FILE

// this struct contains the general data used to move around the program, contained in one neat struct
struct mnu_info_struct;

// function that needs to be called befor using the struct to prepare is's values
void mnu_info_struct_prepare(struct mnu_info_struct* pointer);

#endif