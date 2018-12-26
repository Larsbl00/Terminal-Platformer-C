/**
 * @file KeyReader.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-26
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef KEY_READER_H
#define KEY_READER_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <termio.h>
#include <unistd.h>

typedef struct key_reader
{
    fd_set file_descriptor;
    void (*function_to_execute)(char, void*);
    void* function_arguments;
    struct termios settings_old;
    struct termios settings_new;
} key_reader_t;

/**
 * @brief Create a key reader object
 * 
 * @param function_to_execute 
 * @param functoin_arguments 
 * @return key_reader 
 */
key_reader_t key_reader_create(void (*function_to_execute)(char, void*), void* function_arguments);

/**
 * @brief Destroys a key reader and restores all settings
 * 
 * @param key_reader A pointer to the key reader to destroy
 * 
 * @pre key_reader may not be NULL
 */
void key_reader_destroy(key_reader_t* key_reader);

/**
 * @brief Polls to see if a button was pressed, if so it launches the event given upon constructing the object
 * 
 * @param key_reader 
 * 
 * @pre key_reader may not be NULL
 */
void key_reader_poll(key_reader_t* key_reader);

#endif