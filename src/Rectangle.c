/**
 * @file Rectangle.c
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-26
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "Rectangle.h"

rectangle_t rectangle_create(const size_t x, const size_t y, const size_t height, const size_t width, const uint8_t properties)
{
    rectangle_t rect = {.height = height, .width = width, .properties = properties, .x = x, .y = y};

    //Assign the renderer to the draw rectangle
    rect.renderer = (renderer_t){rectangle_draw};

    return rect;
}

void rectangle_draw(void* parameter)
{
    if (parameter == NULL) return;

    rectangle_draw_parameter_t* param = (rectangle_draw_parameter_t*) parameter;
    rectangle_t* rect = param->rect;
    render_window_t* window = param->window;

    //Set all x values
    for (size_t y = rect->y; y < (rect->y + rect->height); y++)
    {
        for (size_t x = rect->x; x < (rect->x + rect->width); x++)
        {   
            //Check if there is a left side
            if ((rect->properties & RECTANGLE_PROPERTY_BORDER_TOP) &&  (y == rect->y))
            {
                render_window_set(window, x, y, RECTANGLE_CHAR_HORIZONTAL_LINE);
            }
            //Check if there is a right side
            else if ((rect->properties & RECTANGLE_PROPERTY_BORDER_BOTTOM) && (y == (rect->y + rect->height) - 1))
            {
                render_window_set(window, x, y, RECTANGLE_CHAR_HORIZONTAL_LINE);
            }
            //Check if it there is a top
            else if ((rect->properties & RECTANGLE_PROPERTY_BORDER_LEFT) && (x == rect->x))
            {
                render_window_set(window, x, y, RECTANGLE_CHAR_VERTICAL_LINE);
            }
            //Check if there is a bottom
            else if ((rect->properties & RECTANGLE_PROPERTY_BORDER_RIGHT) && (x == (rect->x + rect->width) - 1))
            {
                render_window_set(window, x, y, RECTANGLE_CHAR_VERTICAL_LINE);
            }
            else 
            {
                if ((rect->properties & RECTANGLE_PROPERTY_IS_FILLED))
                {
                    render_window_set(window, x, y, RECTANGLE_CHAR_FILLED);
                }
            }
        } 
    }
}

void rectangle_set_location(rectangle_t* rect, const size_t x, const size_t y)
{
    rect->x = x; 
    rect->y = y;
}
