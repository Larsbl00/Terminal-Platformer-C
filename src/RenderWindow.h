/**
 * @file RenderWindow.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-26
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RENDER_WINDOW_EMPTY_CHAR (' ')
#define RENDER_WINDOW_NEW_LINE ('\n')

typedef struct render_window
{
    const size_t height;
    const size_t width;
    char** buffer;
} render_window_t;

/**
 * @brief Creates an easy to use window to do stuff in
 * 
 * @param height 
 * @param width 
 * @return render_window_t 
 */
render_window_t render_window_create(const size_t height, const size_t width);

/**
 * @brief 
 * 
 * @param window
 * 
 * @pre window may not be NULL 
 */
void render_window_destroy(render_window_t* window);

/**
 * @brief Flushes all data currently stored in the buffer
 * 
 * @param window 
 * 
 * @pre window may not be NULL
 */
void render_window_flush(render_window_t* window);

/**
 * @brief Prints everything in the buffer 
 * 
 * @param window 
 * 
 * @pre window may not be NULL
 */
void render_window_render(render_window_t* window);

/**
 * @brief An easier wayto set the values in the buffer
 * 
 * @param window
 * @param x 
 * @param y 
 * @param value 
 * 
 * @pre window may not be NULL
 */
void render_window_set(render_window_t* window, const size_t x, const size_t y, char value);

#endif