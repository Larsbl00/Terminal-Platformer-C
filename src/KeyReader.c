/**
 * @file KeyReader.c
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-26
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "KeyReader.h"

key_reader_t key_reader_create(void (*function_to_execute)(char, void*), void* function_arguments)
{
    //Initialize the initial reader
    key_reader_t reader = {
        .function_arguments = function_arguments,
        .function_to_execute = function_to_execute
    };

    //Save the current input method.
    tcgetattr(fileno(stdin), &reader.settings_old);

    //Copy the old settings over to the new settings
    reader.settings_new = reader.settings_old;


    //Disable everything except for the ICANNON and ECHO flags
    reader.settings_new.c_lflag = 0 | ICANON | ECHO;

    //Upload new settings
    tcsetattr(fileno(stdin), TCSANOW, &reader.settings_new);
}