#ifndef DRAW_FILE_MANAGER_H
#define DRAW_FILE_MANAGER_H

#include "../structs/navigation_struct.h"

// use these three to draw the top bar, don't use multiple at the same time
// top help and welcome bar
void mnu_filesystem_draw_welcome_bar( void );
// progress for some processes use values 0-50 that represent 2% each, don't use over ~23 characters
void mnu_filesystem_draw_progress_bar(const char* message, uint8_t percents);
// information about what happened recently
void mnu_filesystem_draw_information_bar(const char* message);

// draws the file manager to console
void mnu_filesystem_draw_file_manager(const char* path_main, const mnu_filesystem_navigation_struct* navigation_info);

#endif