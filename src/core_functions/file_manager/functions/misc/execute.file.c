#include <micros.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char partition_symbols[20];
int partitions_count;

void reduce_slashes(char *path)
{
    int length = strlen(path);
    int i = 0;
    
    while (i < length - 1)
    {
        if(path[i] == '/' && path[i + 1] == '/')
        {
            memmove(path + i, path + i + 1, 63 - i);
        }
        else
        {
            i++;
        }
    }
}

void split_to_path_and_args(const char *str, char *path, char *args)
{
    int length = strlen(str);
    
    for(int i = 0; i < length + 1; i++)
    {
        if(str[i] == ' ' || str[i] == 0)
        {
            memcpy(path, str, i);
            memcpy(args, str + i + 1, 63 - i);
            
            path[i] = 0;
            return;
        }
    }
    
    memcpy(path, str, length);
    args[0] = 0;
}

void capitalize_string(char *str)
{
    for(size_t i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
}

void mnu_filesystem_execute_app(const char *str, char partition_symbol, char* path_main)
{
    partitions_count = micros_partitions_get_count();
    micros_partitions_get_symbols(partition_symbols);

    char path[64];
    char args[64];
    
    split_to_path_and_args(str, path, args);
    capitalize_string(path);
    
    for (int p = 0; p < partitions_count; p++)
    {
        char path_variations[6][64];
        sprintf(path_variations[0], "%s", path);
        sprintf(path_variations[1], "%c:%s", partition_symbols[p], path);
        sprintf(path_variations[2], "%c:%s/%s", partition_symbols[p], path_main, path);
        sprintf(path_variations[3], "%c:%s/%s.ELF", partition_symbols[p], path_main, path);
        sprintf(path_variations[4], "%c:/ENV/%s", partition_symbols[p], path);
        sprintf(path_variations[5], "%c:/ENV/%s.ELF", partition_symbols[p], path);
    
        for (int i = 0; i < 6; i++)
        {
            reduce_slashes(path_variations[i]);
            if(micros_filesystem_file_exists(path_variations[i]))
            {
                char args_with_current_dir[64];
                sprintf(args_with_current_dir, "%c:%s %s", partition_symbol, path_main, args);
                
                if(args_with_current_dir[strlen(args_with_current_dir) - 1] == ' ')
                {
                    args_with_current_dir[strlen(args_with_current_dir) - 1] = 0;
                }

                uint32_t child_process_id = micros_process_start_process(path_variations[i], path_main, true, true);
                if((int32_t)child_process_id == -1)
                {
                    printf("Invalid ELF header\n");
                    return;
                }
                
                micros_process_wait_for_process(child_process_id);
                return;
            }
        }
    }
    
    printf("File not found\n");
}

