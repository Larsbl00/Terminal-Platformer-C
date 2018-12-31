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
    player->pressed_key = key;
}


void player_handle_movement(player_t* player)
{
    switch (player->pressed_key)
    {
        case PLAYER_KEY_JUMP:
            if (TIME_SECONDS - player->time_pressed_jump > PLAYER_JUMP_DELAY_SECONDS)
            {
                player_move(player, player->x, player->y - player->jump_distance);
                player->time_pressed_jump = TIME_SECONDS;
            }
            break;
        
        case PLAYER_KEY_MOVE_LEFT:
            player_move(player, player->x + player->move_distance, player->y);
            break;

        case PLAYER_KEY_MOVE_RIGHT:
            player_move(player, player->x - player->move_distance, player->y);
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


void player_move(player_t* player, const size_t x, const size_t y)
{
    player->x = x;
    player->y = y;

    player->hit_box.x = player->x;
    player->hit_box.y = player->y;
}