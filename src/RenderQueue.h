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


#include <unistd.h>

#include "Renderer.h"

#ifndef RENDER_QUEUE_H
#define RENDER_QUEUE_H

typedef struct render_queue
{
    const renderer_t* render_queue;
    const size_t render_queue_size;

} render_queue_t;

#endif