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
    render_window_t window = {
        .height = height, 
        .width = width, 
        .x = 0, 
        .y = 0
    };


    //Allocate the width of the buffer
    window.buffer = malloc(sizeof(*window.buffer) * height);

    //For each x...
    for (size_t y = 0; y < height; y++)
    {
        //...allocate the y-values
        window.buffer[y] = malloc(sizeof(**window.buffer) * width);

        //Clean the allocated values
        for (size_t x = 0; x < width; x++)
        {
            window.buffer[y][x] = RENDER_WINDOW_EMPTY_CHAR;
        }
    }

    return window; 
}

void render_window_destroy(render_window_t* window)
{
    //For each y-values, remove the allocated x-values
    for (size_t y = 0; y < window->height; y++)
    {
        free(window->buffer[y]);
    }

    //Free the array holding all y-values
    free(window->buffer);
}

void render_window_move(render_window_t* window, size_t new_x, size_t new_y)
{
    window->x = new_x;
    window->y = new_y;
}

void render_window_flush(render_window_t* window)
{
    for (size_t y = 0; y < window->height; y++)
    {
        for (size_t x = 0; x < window->width; x++)
        {
            window->buffer[y][x] = RENDER_WINDOW_EMPTY_CHAR;
        }
    }
}

void render_window_render(render_window_t* window)
{
    char new_line = RENDER_WINDOW_NEW_LINE;
    for (size_t y = 0; y < (window->height); y++)
    {
        for (size_t x = 0; x < (window->width); x++)
        {
            char* character = &window->buffer[y][x];
            write(fileno(stdout), character, sizeof(*character));
        }
        write(fileno(stdout), &new_line, sizeof(new_line));
    }
}

void render_window_set(render_window_t* window, const size_t x, const size_t y, char value)
{
    //Early exit if out of bounds
    if (
        x >= window->x &&
        x < window->x + window->width && 
        y >= window->y &&
        y < window->y + window->height
    )
    {
        //Set y first because we render from top left to bottom right
        window->buffer[y - window->y][x - window->x] = value;
    }
}