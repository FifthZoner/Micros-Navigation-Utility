#ifndef RECURSIVE_DELETE_H
#define RECURSIVE_DELETE_H

#include <stdint.h>

// recursive deletion main function
// deletes a dir and all it's subdirs and files
uint8_t mnu_filesystem_recursive_delete(const char* path);

#endif