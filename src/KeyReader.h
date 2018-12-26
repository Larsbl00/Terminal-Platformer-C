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
} key_readet_t;

#endif