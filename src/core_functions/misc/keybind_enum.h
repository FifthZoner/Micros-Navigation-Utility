#ifndef KEYBIND_ENUM_H
#define KEYBIND_ENUM_H

#include <micros/micros_keyboard.h>

enum mnu_keybind_enum{
    mnu_keybind_exit = key_esc,
    mnu_keybind_confirm = key_enter,
    mnu_keybind_directory_advance = key_enter,
    mnu_keybind_directory_unadvance = key_backspace,
    mnu_keybind_directory_up = key_keypad_8,
    mnu_keybind_directory_down = key_keypad_2,
    mnu_keybind_directory_create = key_keypad_plus,
    mnu_keybind_help_screen = key_f5,
    mnu_keybind_file_create = key_keypad_star,
    mnu_keybind_file_directory_delete = key_keypad_minus
};

#endif