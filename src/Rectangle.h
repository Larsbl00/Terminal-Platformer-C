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
#include "RenderWindow.h"

#define RECTANGLE_CHAR_FILLED ('#')
#define RECTANGLE_CHAR_VERTICAL_LINE ('|')
#define RECTANGLE_CHAR_HORIZONTAL_LINE ('_')

//Single border location
#define RECTANGLE_PROPERTY_BORDER_BOTTOM (0x80)
#define RECTANGLE_PROPERTY_BORDER_LEFT (0x40)
#define RECTANGLE_PROPERTY_BORDER_RIGHT (0x20)
#define RECTANGLE_PROPERTY_BORDER_TOP (0x10)
//Double border location
#define RECTANGLE_PROPERTY_BORDER_LEFT_RIGHT (RECTANGLE_PROPERTY_BORDER_LEFT | RECTANGLE_PROPERTY_BORDER_RIGHT)
#define RECTANGLE_PROPERTY_BORDER_TOP_BOTTOM (RECTANGLE_PROPERTY_BORDER_BOTTOM | RECTANGLE_PROPERTY_BORDER_TOP)
//Full border location
#define RECTANGLE_PROPERTY_BORDER_FULL (RECTANGLE_PROPERTY_BORDER_LEFT_RIGHT | RECTANGLE_PROPERTY_BORDER_TOP_BOTTOM)

//Special Properties
#define RECTANGLE_PROPERTY_IS_COLLIDABLE (0x01)
#define RECTANGLE_PROPERTY_IS_FILLED (0x02)

typedef struct rectangle
{
    const size_t width;
    const size_t height;
    const uint8_t properties;
    renderer_t renderer;
    size_t x;
    size_t y;
} rectangle_t;

typedef struct rectangle_draw_parameter
{
    rectangle_t* rect;
    render_window_t* window;
} rectangle_draw_parameter_t;

/**
 * @brief Creates a rectangle
 * 
 * @param x
 * @param y
 * @param width 
 * @param height 
 * @param properties A collection of defined masks to give to the rectangle, e.g. RECTANGLE_PROPERTY_IS_FILLED
 * @return rectangle_t 
 */
rectangle_t rectangle_create(const size_t x, const size_t y, const size_t width, const size_t height, const uint8_t properties);

/**
 * @brief Checks if a given x and y location hits the rectangle
 * 
 * @param rect 
 * @param x 
 * @param y 
 * @return uint8_t Returns 1 when the coordinate hits the rectangle, else it will return 0
 * 
 * @note Function will always return 0, if the rectangle does not have the IS_COLLIDEABLE property enabled
 */
uint8_t rectangle_collides(const rectangle_t* rect, const size_t x, const size_t y);

/**
 * @brief This function is supposed to draw a rectangle, but is made to be compatable with the renderer
 * 
 */
void rectangle_draw(void* parameter);

/**
 * @brief Set the location of the rectangle to a given value
 * 
 * @param x 
 * @param y 
 */
void rectangle_set_location(rectangle_t* rect, const size_t x, const size_t y);

#endif