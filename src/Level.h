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

#define LEVEL_RENDER_DISTANCE_FACTOR (0.75)

typedef struct level
{
    const size_t width;
    const size_t height;
    const size_t floor_count;

    rectangle_t* floors;
    uint8_t is_complete;
    renderer_t renderer;
} level_t;

typedef struct level_draw_parameter
{
    player_t* player;
    level_t* level;
    render_window_t* window;
} level_draw_parameter_t;

/**
 * @brief Create a level object
 * 
 * @param width Total width of the level
 * @param height Total height of the level 
 * @param floors A pointer to an array of rectangles to act as the floor
 * @param floor_count The amount of items stores in the floors values
 * @return level_t 
 */
level_t level_create(const size_t width, const size_t height, rectangle_t* floors, const size_t floor_count);

/**
 * @brief A draw function compatable with the renderers demand
 * 
 */
void level_draw(void*);

/**
 * @brief Checks if the player is hitting any surfaces
 * 
 * @param level 
 * @param player 
 * 
 * @pre level and player may not be NULL
 */
void level_update_player(level_t* level, player_t* player);

#endif