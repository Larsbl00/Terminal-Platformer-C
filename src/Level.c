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
    level_draw_parameter_t* params = (level_draw_parameter_t*) parameters;

    level_t* level = params->level;
    player_t* player = params->player;
    render_window_t* window = params->window;

    for (size_t i = 0; i < level->floor_count; i++)
    {
        rectangle_t* pfloor = &level->floors[i];

        //Check if the item ate the utmost right needs to be present
        if (
            (player->hit_box.x + player->hit_box.width) + (window->width * LEVEL_RENDER_DISTANCE_FACTOR) > pfloor->x &&
            (player->hit_box.x - (window->width * LEVEL_RENDER_DISTANCE_FACTOR)) < (pfloor->x + pfloor->width)
        )
        {
            rectangle_draw_parameter_t rect_param = (rectangle_draw_parameter_t){pfloor, window};
            rectangle_draw(&rect_param);
        }
    }
}

void level_update_player(level_t* level, player_t* player)
{
    //Check each floor to see if the player is near the floor. 
    for (size_t i = 0; i < level->floor_count; i ++)
    {
        rectangle_t* pfloor = &level->floors[i];
        
        //Check if the floor has collision enabled
        if (pfloor->properties & RECTANGLE_PROPERTY_IS_COLLIDABLE)
        {
            //Player is present in the domain of the rectangle 
            if (player->hit_box.x >= pfloor->x && player->hit_box.x <= (pfloor->x + pfloor->width))
            {
                //Correct player when they try to go through the bottom
                if (player->hit_box.y < (pfloor->y + pfloor->height))
                {
                    printf("Player hits bottom\n");
                    player_move(player, 0, ((pfloor->y - pfloor->height)) + 1);
                }
                //Check if the player is about to fall through the floor
                else if ((player->hit_box.y + player->hit_box.height) > pfloor->y)
                {
                    printf("Player hits top\n");
                    player_move(player, 0, pfloor->y - player->hit_box.height + 1);
                }
                else 
                {
                    printf("No Collision with floor\n");
                }
            }
        }
    }
}