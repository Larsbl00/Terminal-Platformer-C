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

#include <stdint.h>
#include <unistd.h>

#include "Renderer.h"

#define RECTANGLE_PROPERTY_IS_SOLID (0x1);
#define RECTANGLE_PROPERTY_IS_FILLED (0x2);

typedef struct rectangle
{
    const size_t height;
    const size_t width;
    const uint8_t properties;
    renderer_t renderer;
} rectangle_t;

/**
 * @brief Creates a rectangle
 * 
 * @param height 
 * @param width 
 * @param properties A collection of defined masks to give to the rectangle, e.g. RECTANGLE_PROPERTY_IS_FILLED
 * @return rectangle_t 
 */
rectangle_t rectangle_create(const size_t height, const size_t width, const uint8_t properties);

/**
 * @brief This function is supposed to draw a rectangle, but is made to be compatable with the renderer
 * 
 */
void rectangle_draw(void*);

#endif