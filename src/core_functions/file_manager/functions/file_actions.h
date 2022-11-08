#ifndef FILE_MANAGER_FILE_ACTIONS_H
#define FILE_MANAGER_FILE_ACTIONS_H

#include <stdint.h>

// asks user for name and creates a new dir in a given dir,
// returns 1 if succesful
// in that case always fill file list
// 0 if not
uint8_t mnu_filesystem_directory_create(const char* path_main);

// asks user for name and creates a new dile in a given dir,
// returns 1 if succesful
// in that case always fill file list
// 0 if not
uint8_t mnu_filesystem_file_create(const char* path_main);

// deletes a file after asking for a confirmation
void mnu_filesystem_file_delete(const char* path_main, const char* name);

// deletes a directory after asking for a confirmation
// if it's empty deletes instantly, if not then asks for confirmation to delete recursively
void mnu_filesystem_directory_delete(const char* path_main, const char* name);

#endif