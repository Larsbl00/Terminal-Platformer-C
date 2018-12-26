/**
 * @file RenderQueue.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-26
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include <stdint.h>
#include <unistd.h>

#include "Renderer.h"

#ifndef RENDER_QUEUE_H
#define RENDER_QUEUE_H

typedef struct render_queue
{
    const renderer_t** render_queue;
    size_t render_queue_current_size;
    const size_t render_queue_max_size;

} render_queue_t;

/**
 * @brief Creates a render queue
 * 
 * @param size Count of max allowed items in queue
 */
render_queue_t render_queue_create(const size_t size);

/**
 * @brief Destroys a render queue
 * 
 * @param render_queue 
 * 
 * @pre render_queue may not be NULL
 */
void render_queue_destroy(render_queue_t* render_queue);

/**
 * @brief Adds an item to the render queue
 * 
 * @param render_queue 
 * @param item_to_render A reference to the item to render
 * @return int8_t Returns -1 if the addition fails. i.e. a pointer refers to NULL or the item is already present
 */
int8_t render_queue_add_item(render_queue_t* render_queue, renderer_t* item_to_render);

/**
 * @brief Removes an item from the render queue
 * 
 * @param render_queue 
 * @param item_to_remove 
 * @return int8_t Returns -1 if the removal failed. i.e. a pointer refers to NULL or the item does not exist in the list
 */
int8_t render_queue_remove_item(render_queue_t* render_queue, renderer_t* item_to_remove);

/**
 * @brief Renders all items present in the queue
 * 
 * @param render_queue 
 * 
 * @pre render_queue may not be NULL
 */
void render_queue_render(render_queue_t* render_queue);

#endif