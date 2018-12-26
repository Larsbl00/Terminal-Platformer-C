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

void key_reader_destroy(key_reader_t* key_reader)
{
    //Reset stdin to the old settings
    tcsetattr(fileno(stdin), TCSANOW, &key_reader->settings_old);

    //Free the resources used
    free(key_reader);
}

void key_reader_poll(key_reader_t* key_reader)
{
    //Create a timeout
    struct timeval timeout = INPUT_READ_TIMEOUT;

    fd_set descriptor;

    FD_ZERO(&descriptor);
    FD_SET(fileno(stdin), &descriptor);

    int8_t read_response = select(fileno(stdin) + 1, &descriptor, NULL, NULL, &timeout);

    if (read_response > 0)
    {
        //Data was read on the descriptor
        char pressed_char;
        read(fileno(stdin), &pressed_char, sizeof(pressed_char));
        key_reader->function_to_execute(pressed_char, key_reader->function_arguments);
    }
    else if (read_response < 0)
    {
        //Error while reding data
        printf("Error while reading\n");
    }
}