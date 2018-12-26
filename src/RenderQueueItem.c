/**
 * @file RenderQueueItem.c
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-26
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "RenderQueueItem.h"

render_queue_item_t render_queue_item_create(renderer_t* renderer, void* parameter)
{
    return (render_queue_item_t){parameter, renderer};
}