// corresponding header
#include "main_loop.h"

#include <stdio.h>
#include <stdint.h>
#include <micros.h>

#include "file_manager/drawing/draw_help_screen.h"
#include "file_manager/drawing/draw_file_manager.h"
#include "file_manager/structs/navigation_struct_functions.h"
#include "file_manager/functions/dir_movement.h"
#include "misc/stage_enum.h"

// handles all the key input in the given iteration
void local_handle_keys(char* path_main, mnu_filesystem_navigation_struct* navigation_info, uint8_t* current_stage, bool* itsAlive){

    do{
            micros_keyboard_scan_ascii_pair key_pair;

            micros_keyboard_wait_for_key_press(&key_pair);

            switch(key_pair.scancode){

                // ends the loop
                case key_esc:

                    *itsAlive = 0;
                    break;

                // up key
                case key_keypad_8:
                    //mnu_move_file_cursor_up();
                    break;

                // down
                case key_keypad_2:
                    //mnu_move_file_cursor_down();
                    break;

                // enter, enters a new dir or opens a file (?)
                case key_enter:

                    break;

                // going back a dir
                case key_backspace:

                    break;

                default:
                    continue;
                
            }
        }
        while (0);

}

// the main function that runs all of the program
void mnu_run_main_loop(char* path_main){

    // navigation struct that will be passed to all the lovely functions
    mnu_filesystem_navigation_struct navigation_info = mnu_filesystem_navigation_struct_constructor();

    // first fill of the file list
    mnu_filesystem_file_list_struct_fill(&navigation_info.file_list, path_main, &navigation_info.lower_limit, &navigation_info.upper_limit);

    // loop condition, will probably be useless and replaced with break but it's here
    bool itsAlive = true;

    // stage variable to chceck what is happening, always starts in file explorer, at least for now
    uint8_t current_stage = mnu_main_loop_stage_file_explorer_main;

    // main loop
    while(itsAlive){

        // clearing the screen
        micros_console_clear();

        // main drawing switch
        switch (current_stage){
            
            case mnu_main_loop_stage_file_explorer_main:

                mnu_filesystem_draw_file_manager(path_main, &navigation_info);
                break;


            case mnu_main_loop_stage_help_screen:

                break;


            default:

                break;
        }

        // key input and generally all the glorious things related to doing anything
        local_handle_keys(path_main, &navigation_info, &current_stage, &itsAlive);

    }

    // deallocating the path string
    free(path_main);

    // freeing the navigation thing
    mnu_filesystem_navigation_struct_free(&navigation_info);

    // to not leave weird things
    micros_console_clear();
}