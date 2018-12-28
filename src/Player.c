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

player_t player_create(size_t x, size_t y, const size_t height, const size_t width, const size_t jump_distance, const size_t move_distance)
{
    player_t player = {
        .jump_distance = jump_distance,
        .move_distance = move_distance,
        .hit_box = rectangle_create(x, y, width, height, RECTANGLE_PROPERTY_IS_COLLIDABLE),
        .renderer = (renderer_t){player_draw},
        .x = x,
        .y = y
    };

    return player;
}

void player_handle_key(player_t* player, char key)
{
    switch (key)
    {
        case PLAYER_KEY_JUMP:
            player->y -= player->jump_distance;
            break;
        
        case PLAYER_KEY_MOVE_DOWN:
            player->y += player->move_distance;
            break;
        
        case PLAYER_KEY_MOVE_LEFT:
            player->x -= player->move_distance;
            break;

        case PLAYER_KEY_MOVE_RIGHT:
            player->x += player->move_distance;
            break;

        case PLAYER_KEY_MOVE_UP:
            player->y -= player->move_distance;
            break;
    }

}


void player_draw(void* parameters)
{

}
