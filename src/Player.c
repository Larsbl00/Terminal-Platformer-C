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

player_t player_create(size_t x, size_t y, const size_t jump_distance, const size_t move_distance)
{
    player_t player = {
        .jump_distance = jump_distance,
        .move_distance = move_distance,
        .hit_box = rectangle_create(x, y, PLAYER_SIZE_WIDTH, PLAYER_SIZE_HEIGHT, RECTANGLE_PROPERTY_IS_COLLIDABLE),
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

        default:
            break;
    }

}


void player_draw(void* parameters)
{
    if (parameters == NULL) return;

    player_draw_parameter_t* params = (player_draw_parameter_t*) parameters;

    render_window_t* window = params->window;
    player_t* player = params->player;

    for (size_t y = player->y; y < (player->y + PLAYER_SIZE_HEIGHT); y++)
    {
        for (size_t x = player->x; x < (player->x + PLAYER_SIZE_WIDTH); x++)
        {
            render_window_set(window, x, y, player_model[y - player->y][x - player->x]);
        }
    }
}
