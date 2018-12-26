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
    renderer_t* renderer;
    void* parameter;
} render_queue_item_t;

#endif