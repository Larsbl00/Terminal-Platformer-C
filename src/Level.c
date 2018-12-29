/**
 * @file Level.c
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-29
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "Level.h"

level_t level_create(const size_t width, const size_t height, rectangle_t* floors, const size_t floor_count)
{
    level_t level = {
        .width = width,
        .height = height,
        .floor_count = floor_count,
        .floors = floors,
        .is_complete = 0,
        .renderer = (renderer_t){level_draw}
    };

    return level;
}

void level_draw(void* parameters)
{

}

void level_update_player(level_t* level, player_t* player)
{
    
}