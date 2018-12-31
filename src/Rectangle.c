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

rectangle_t rectangle_create(const size_t x, const size_t y, const size_t width, const size_t height, const uint8_t properties)
{
    rectangle_t rect = {.height = height, .width = width, .properties = properties, .x = x, .y = y};

    //Assign the renderer to the draw rectangle
    rect.renderer = (renderer_t){rectangle_draw};

    return rect;
}

uint8_t rectangle_collides(const rectangle_t* rect, const size_t x, const size_t y)
{
    //Early exit if the pointer is invallid, or if the rect is not hittable
    if (rect == NULL || !(rect->properties & RECTANGLE_PROPERTY_IS_COLLIDABLE)) return 0;

    if (
        (x >= rect->x) && // Check if requested x is greater than the x of the rect
        (x <= rect->x + rect->width) && //Check if the x is smaller than the end of the object 
        (y >= rect->y) && //Check if the requested y is greater than the y of the object
        (y <= rect->y + rect->height) //Check if the y is smaller than the end of the rect
    )
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

uint8_t rectangle_collides_with_rectangle(const rectangle_t* rect1, const rectangle_t* rect2)
{
    //Early exits if the params are NULL or non hitable
    if (rect1 == NULL || rect2 == NULL || !(rect1->properties & RECTANGLE_PROPERTY_IS_COLLIDABLE) || 
        !(rect2->properties & RECTANGLE_PROPERTY_IS_COLLIDABLE)) 
    {
        return 0;
    }

    //Check if the corners of the rect hit, the rest is irrelevant
    if (rectangle_collides(rect1, rect2->x, rect2->y) || rectangle_collides(rect1, rect2->x + rect2->width, rect2->y) ||
       rectangle_collides(rect1, rect2->x, rect2->y + rect2->height) + rectangle_collides(rect1, rect2->x + rect2->width, rect2->y + rect2->height))
    {
        return 1;
    }
    else 
    {
        return 0;
    }
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
            //Check if there is room for object to be rendered
            if (window->buffer[y][x] == RENDER_WINDOW_EMPTY_CHAR)
            {
                //Check if there is a top
                if ((rect->properties & RECTANGLE_PROPERTY_BORDER_TOP) &&  (y == rect->y))
                {
                    render_window_set(window, x, y, RECTANGLE_CHAR_HORIZONTAL_LINE);
                }
                //Check if there is a bottom
                else if ((rect->properties & RECTANGLE_PROPERTY_BORDER_BOTTOM) && (y == (rect->y + rect->height) - 1))
                {
                    render_window_set(window, x, y, RECTANGLE_CHAR_HORIZONTAL_LINE);
                }
                //Check if it there is a left side
                else if ((rect->properties & RECTANGLE_PROPERTY_BORDER_LEFT) && (x == rect->x))
                {
                    render_window_set(window, x, y, RECTANGLE_CHAR_VERTICAL_LINE);
                }
                //Check if there is a right side
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
}

void rectangle_set_location(rectangle_t* rect, const size_t x, const size_t y)
{
    rect->x = x; 
    rect->y = y;
}
