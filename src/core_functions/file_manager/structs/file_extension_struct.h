#include <stdint.h>

typedef struct file_extension_struct{

    // extension name AFTER the dot, for example "elf\0"
    char name[4];

    // used to determine type of action to do with giver file extension
    // at least for not it will be a table of these structs
    uint8_t action_type;

}file_extension_struct;