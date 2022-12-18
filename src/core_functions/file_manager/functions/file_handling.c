// corresponding header
#include "file_handling.h"
#include "misc/execute_elf_file.h"

#include <micros.h>
#include <stdio.h>
#include <string.h>


// takes a file name and checks extension to do what is needed and does it 
void mnu_filesystem_handle_file(char* file_path, char* path_main){

    // getting extension name
    // should be the first letter of extension
    uint16_t offset = strlen(file_path) - 1;
    for (; file_path[offset]!='.'; offset--){}
    offset++;

    char extension[4];

    for (uint16_t n = 0; n < 4; n++){
        extension[n] = file_path[n + offset];
    }

    // for now only .elf because there's no text editor
    if (strcmp(extension, "ELF") == 0){

        mnu_filesystem_execute_app(file_path, path_main);
    }
}