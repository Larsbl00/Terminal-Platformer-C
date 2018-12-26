/**
 * @file RenderQueueItem.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-26
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef RENDER_QUEUE_ITEM_H
#define RENDER_QUEUE_ITEM_H

#include "Renderer.h"

typedef struct render_queue_item
{
    void* parameter;
    renderer_t* renderer;
} render_queue_item_t;

/**
 * @brief Creates a new item to add to the render queue
 * 
 * @param renderer 
 * @param parameter 
 * @return render_queue_item_t The item to add to the queue
 * 
 * @pre renderer and parameter may not be NULL
 */
render_queue_item_t render_queue_item_create(renderer_t* renderer, void* parameter);

#endif