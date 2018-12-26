/**
 * @file Rectangle.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-26
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <unistd.h>

#include "Renderer.h"

typedef struct rectangle
{
    const size_t height;
    const size_t width;
    renderer_t renderer;
} rectangle_t;

#endif