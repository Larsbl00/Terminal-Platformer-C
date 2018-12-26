/**
 * @file RenderWindow.c
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-26
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "RenderWindow.h"

render_window_t render_window_create(const size_t height, const size_t width)
{
    render_window_t window = {.height = height, .width = width};

    //Allocate the width of the buffer
    window.buffer = malloc(sizeof(*window.buffer) * width);

    //For each x...
    for (size_t x = 0; x < width; x++)
    {
        //...allocate the y-values
        window.buffer[x] = malloc(sizeof(**window.buffer) * height);

        //Clean the allocated values
        for (size_t y = 0; y < height; y++)
        {
            window.buffer[x][y] = 0;
        }
    }

    return window; 
}

void render_window_destroy(render_window_t* window)
{
    //For each x-values, remove the allocated y-values
    for (size_t x = 0; x < window->width; x++)
    {
        free(window->buffer[x]);
    }

    //Free the array holding all x-values
    free(window->buffer);
}