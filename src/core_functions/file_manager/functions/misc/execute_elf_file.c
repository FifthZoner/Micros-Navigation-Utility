#include <micros.h>
#include <stdio.h>
#include "execute_elf_file.h"

void mnu_filesystem_execute_app(char* path, char* path_main){

    uint32_t child_process_id = micros_process_start_process(path, path_main, true, true);
    if((int32_t)child_process_id == -1){
        printf("ERROR\n");
        return;
    }
                
    micros_process_wait_for_process(child_process_id);
}