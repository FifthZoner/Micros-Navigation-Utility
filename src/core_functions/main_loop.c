// corresponding header
#include "main_loop.h"

#include <stdio.h>
#include <stdint.h>
#include <micros.h>

#include "file_manager/drawing/draw_help_screen.h"
#include "file_manager/drawing/draw_file_manager.h"
#include "file_manager/structs/navigation_struct_functions.h"
#include "file_manager/structs/cursor_history_struct_functions.h"
#include "file_manager/functions/dir_movement.h"
#include "file_manager/functions/dir_cursor_actions.h"
#include "file_manager/functions/file_actions.h"
#include "file_manager/functions/file_handling.h"
#include "misc/keybind_enum.h"
#include "misc/stage_enum.h"

// handles keys for help screen
void local_handle_keys_help_screen(uint8_t* current_stage, bool* itsAlive){

    do{
        micros_keyboard_scan_ascii_pair key_pair;

        micros_keyboard_wait_for_key_press(&key_pair);

        switch(key_pair.scancode){

            // ends the loop
            case mnu_keybind_exit:

                *itsAlive = 0;
                break;

            // goes back
            case mnu_keybind_help_screen:

                
                *current_stage = mnu_main_loop_stage_file_explorer_main;

                break;

            default:
                continue;
                
         }
    }
    while (0);
}

// handles keys for file manager
char* local_handle_keys_file_manager(char* path_main, mnu_filesystem_navigation_struct* navigation_info, 
uint8_t* current_stage, bool* itsAlive, mnu_filesystem_cursor_history_struct* cursor_history){

    do{
        micros_keyboard_scan_ascii_pair key_pair;

        micros_keyboard_wait_for_key_press(&key_pair);

        switch(key_pair.scancode){

            // ends the loop
            case mnu_keybind_exit:

                *itsAlive = 0;
                break;


            // up key
            case mnu_keybind_directory_up:

                mnu_filesystem_cursor_move_up(navigation_info);
                break;


            // down
            case mnu_keybind_directory_down:
            
                mnu_filesystem_cursor_move_down(navigation_info);
                break;


            // enter, enters a new dir or opens a file (?)
            case mnu_keybind_directory_advance:

                // check for dir
                if (navigation_info->file_list.length > 0 && navigation_info->file_list.are_they_dirs[navigation_info->cursor_position] == true){

                    path_main = mnu_filesystem_directory_advance(path_main, navigation_info->file_list.names[navigation_info->cursor_position]);
                    
                    mnu_filesystem_file_list_struct_fill(&navigation_info->file_list,
                    path_main, &navigation_info->lower_limit, &navigation_info->upper_limit, &navigation_info->cursor_position,
                    0, 0, cursor_history, 1);
                }
                else if (navigation_info->file_list.length > 0 && navigation_info->file_list.are_they_dirs[navigation_info->cursor_position] == false){


                    char* file_path = (char*)malloc((strlen(path_main) + strlen(navigation_info->file_list.names[navigation_info->cursor_position]) + 1) * sizeof(char));

                    strcpy(file_path, path_main);
                    strcat(file_path, navigation_info->file_list.names[navigation_info->cursor_position]);


                    mnu_filesystem_handle_file(file_path, path_main);

                    free(file_path);

                }

                break;


            // going back a dir
            case mnu_keybind_directory_unadvance:

                if (strlen(path_main) > 3){

                    path_main = mnu_filesystem_directory_unadvance(path_main);

                    mnu_filesystem_file_list_struct_fill(&navigation_info->file_list,
                    path_main, &navigation_info->lower_limit, &navigation_info->upper_limit, &navigation_info->cursor_position,
                    1, 0, cursor_history, 1);
                
                }

                break;


            // goes to help
            case mnu_keybind_help_screen:

                // this always exits back to mnu or completly so no need for clearing list now
                *current_stage = mnu_main_loop_stage_help_screen;

                break;

            
            case mnu_keybind_directory_create:

                // creates a dir
                if (mnu_filesystem_directory_create(path_main) == 1){

                    mnu_filesystem_file_list_struct_fill(&navigation_info->file_list,
                    path_main, &navigation_info->lower_limit, &navigation_info->upper_limit, &navigation_info->cursor_position, 
                    0, 0, cursor_history, 0);
                }


                break;


            case mnu_keybind_file_create:

                // creates a file
                if (mnu_filesystem_file_create(path_main) == 1){

                    mnu_filesystem_file_list_struct_fill(&navigation_info->file_list,
                    path_main, &navigation_info->lower_limit, &navigation_info->upper_limit, &navigation_info->cursor_position,
                    0, 0, cursor_history, 0);
                }

                break;


            case mnu_keybind_file_directory_delete:

                // removes a dir or file after asking for confirmation
                if (navigation_info->file_list.length > 0 && navigation_info->file_list.are_they_dirs[navigation_info->cursor_position] == 1){
                    // dir

                    if (mnu_filesystem_directory_delete(path_main, navigation_info->file_list.names[navigation_info->cursor_position]) == 1){

                        // refreshing
                        mnu_filesystem_file_list_struct_fill(&navigation_info->file_list,
                        path_main, &navigation_info->lower_limit, &navigation_info->upper_limit, &navigation_info->cursor_position,
                        0, 1, cursor_history, 0);
                    }
                }
                else if (navigation_info->file_list.length > 0){
                    // file
                    if (mnu_filesystem_file_delete(path_main, navigation_info->file_list.names[navigation_info->cursor_position]) == 1){

                        // refreshing
                        mnu_filesystem_file_list_struct_fill(&navigation_info->file_list,
                        path_main, &navigation_info->lower_limit, &navigation_info->upper_limit, &navigation_info->cursor_position,
                        0, 1, cursor_history, 0);
                    }

                }

                break;

            default:
                continue;
                
            }
        }
        while (0);

    return path_main;
}

// handles all the key input in the given iteration
char* local_handle_keys(char* path_main, mnu_filesystem_navigation_struct* navigation_info, 
uint8_t* current_stage, bool* itsAlive, mnu_filesystem_cursor_history_struct* cursor_history){

    // main drawing switch
        switch (*current_stage){
            
            case mnu_main_loop_stage_file_explorer_main:

                path_main = local_handle_keys_file_manager(path_main, navigation_info, current_stage, itsAlive, cursor_history);
                break;


            case mnu_main_loop_stage_help_screen:

                local_handle_keys_help_screen(current_stage, itsAlive);
                break;


            default:

                break;
        }

    return path_main;
}

// the main function that runs all of the program
void mnu_run_main_loop(char* path_main){

    // navigation struct that will be passed to all the lovely functions
    mnu_filesystem_navigation_struct navigation_info = mnu_filesystem_navigation_struct_constructor();

    // creating of the cursor hustory struct
    mnu_filesystem_cursor_history_struct cursor_history = mnu_filesystem_cursor_history_struct_constructor(path_main);

    // first fill of the file list
    mnu_filesystem_file_list_struct_fill(&navigation_info.file_list, path_main, &navigation_info.lower_limit, 
    &navigation_info.upper_limit, &navigation_info.cursor_position, 0, 0, &cursor_history, 05);

    // loop condition, will probably be useless and replaced with break but it's here
    bool itsAlive = true;

    // stage variable to chceck what is happening, always starts in file explorer, at least for now, 256 possibilities should be enough
    uint8_t current_stage = mnu_main_loop_stage_file_explorer_main;

    // main loop
    while(itsAlive){

        // clearing the screen
        micros_console_clear();

        // main drawing switch
        switch (current_stage){
            
            case mnu_main_loop_stage_file_explorer_main:

                mnu_filesystem_draw_welcome_bar();
                mnu_filesystem_draw_file_manager(path_main, &navigation_info);
                break;


            case mnu_main_loop_stage_help_screen:

                mnu_filesystem_draw_help_screen();
                break;


            default:

                break;
        }

        // key input and generally all the glorious things related to doing anything
        path_main = local_handle_keys(path_main, &navigation_info, &current_stage, &itsAlive, &cursor_history);

    }

    // deallocating
    free(path_main);
    mnu_filesystem_navigation_struct_free(&navigation_info);
    mnu_filesystem_cursor_history_struct_free(&cursor_history);

    // to not leave weird things
    micros_console_clear();
}