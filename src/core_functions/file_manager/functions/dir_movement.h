#ifndef DIR_MOVEMENT_H
#define DIR_MOVEMENT_H

// adds given dir name to the path, pass path_main and the name of the dir to use from the list
char* mnu_filesystem_directory_advance(char* path_main, const char* name);

// changes the path to go back one directory or stays the same if in the lowest one
char* mnu_filesystem_directory_unadvance(char* path_main);

#endif