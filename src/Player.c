/**
 * @file Player.c
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-28
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "Player.h"

player_t player_create(size_t x, size_t y, const size_t height, const size_t width)
{
    player_t player = {
        .hit_box = rectangle_create(x, y, width, height, RECTANGLE_PROPERTY_IS_COLLIDABLE),
        .renderer = (renderer_t){player_draw},
        .x = x,
        .y = y
    };

    return player;
}

void player_handle_key(player_t* player, char key)
{
    
}


void player_draw(void* parameters)
{

}
