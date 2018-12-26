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

    //Check if item is already present, escape if it is present
    size_t index;
    if (render_queue_is_item_present(render_queue, item_to_render, &index) >= 0) return -1;

    //Add item to the current size, and auto increment it
    render_queue->queue[render_queue->queue_current_size++] = render_queue_item_create(item_to_render, parameter);
    
    return 0;
}

int8_t render_queue_is_item_present(render_queue_t* render_queue, renderer_t* item, size_t* index)
{
    //Early exit if the pointers are NULL references
    if (render_queue == NULL || item == NULL) return -1;

    //Go through all currently stored items
    for (size_t i = 0; i < render_queue->queue_current_size; i++)
    {
        //Exit if item is located
        if (render_queue->queue[i].renderer == item)
        {
            printf("Item Located at %li\n", i);
            *index = i;
            return 0;
        }
    }

    //Item not located
    return -1;
}

int8_t render_queue_remove_item(render_queue_t* render_queue, renderer_t* item_to_remove)
{
    //Early exit if there are NULL references
    if (render_queue == NULL || item_to_remove == NULL) return -1;

    size_t index;

    //Check if item exists in list, if it does not exit the function
    if (render_queue_is_item_present(render_queue, item_to_remove, &index) < 0) return -1;

    for (size_t i = index; i < render_queue->queue_current_size; i++)
    {
        render_queue->queue[i] = render_queue->queue[i + 1];
    }

    //Decrement the size, due to an item being removed
    render_queue->queue_current_size--;

    return 0;
}