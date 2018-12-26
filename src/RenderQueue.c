/**
 * @file RenderQueue.c
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-26
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "RenderQueue.h"

render_queue_t render_queue_create(const size_t size)
{
    //Set the max size
    render_queue_t queue = {.queue_max_size = size, .queue_current_size = 0};

    const size_t array_size = sizeof(*queue.queue) * size;

    //Allocate memory for the buffer
    queue.queue = malloc(array_size);

    //Clear memory in allocated memory
    for (size_t i = 0; i < queue.queue_max_size; i++)
    {
        queue.queue[i] = render_queue_item_create(NULL, NULL);
    }

    return queue;
}

