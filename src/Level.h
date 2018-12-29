/**
 * @file Level.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-29
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>
#include <unistd.h>

#include "Player.h"
#include "Renderer.h"
#include "RenderWindow.h"
#include "Rectangle.h"

typedef struct level
{
    const size_t width;
    const size_t height;
    const size_t floor_count;

    rectangle_t* floors;
} level_t;

/**
 * @brief Create a level object
 * 
 * @param width Total width of the level
 * @param height Total height of the level 
 * @param floors A pointer to an array of rectangles to act as the floor
 * @param floor_count The amount of items stores in the floors values
 * @return level_t 
 */
level_t create_level(const size_t width, const size_t height, rectangle_t* floors, const size_t floor_count);

#endif