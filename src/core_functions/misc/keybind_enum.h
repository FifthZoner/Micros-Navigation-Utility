#ifndef KEYBIND_ENUM_H
#define KEYBIND_ENUM_H

#include <micros/micros_keyboard.h>

enum mnu_keybind_enum{
    mnu_keybind_exit = key_esc,
    mnu_keybind_confirm = key_enter,
    mnu_keybind_directory_advance = key_enter,
    mnu_keybind_directory_unadvance = key_backspace,
    mnu_keybind_directory_up = key_keypad_8,
    mnu_keybind_directory_down = key_keypad_2
};

#endif