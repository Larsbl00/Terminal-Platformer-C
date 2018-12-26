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

void render_queue_destroy(render_queue_t* render_queue)
{
    //Only the queue is freed, not the pointers to the items.
    free(render_queue->queue);
}

int8_t render_queue_add_item(render_queue_t* render_queue, renderer_t* item_to_render, void* parameter)
{
    //Early exit if renderer or queue are NULL, parameter may be NULL and it's responsibillity lies in the handler function
    if (render_queue == NULL || item_to_render == NULL) return -1;

    //Early exit if there is no more room left for the item
    if ((render_queue->queue_current_size + 1 >= render_queue->queue_max_size - 1)) return -1;

    
}

ssize_t render_queue_is_item_present(render_queue_t* render_queue, renderer_t* item)
{
    //Early exit if the pointers are NULL references
    if (render_queue == NULL || item == NULL) return -1;
}