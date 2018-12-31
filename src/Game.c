/**
 * @file Game.c
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-31
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#include "Game.h"

game_t* game_create(const size_t render_queue_size, const size_t window_height, const size_t window_width)
{
    //Init the game
    game_t game = {
        .gravity_is_active = 0,
        .level = NULL,
        .level_draw_parameter = NULL,
        .player = player_create(0, 0, GAME_PLAYER_JUMP_DISTANCE, GAME_PLAYER_MOVE_DISTANCE),
        .render_queue = render_queue_create(render_queue_size),
        .window = render_window_create(window_height, window_width)
    };

    //Allocate a pointer to the game
    game_t* pgame = (game_t*) malloc(sizeof(game));
    memcpy(pgame, &game, sizeof(game));


    //Assign the function to the newly aloocated pointer
    pgame->input_reader = key_reader_create(game_handle_input, pgame);
    pgame->player_draw_parameter = (player_draw_parameter_t){&pgame->player, &pgame->window};

    //Add all the player to the queue
    render_queue_add_item(&pgame->render_queue, &pgame->player.renderer, &pgame->player_draw_parameter);

    return pgame;
};

void game_destroy(game_t* game)
{
    key_reader_destroy(&game->input_reader);
    render_window_destroy(&game->window);
    render_queue_destroy(&game->render_queue);

    game_unload_current_level(game);
}

void game_load_level(game_t* game, level_t* level, level_draw_parameter_t* level_draw_parameter)
{
    //Make sure there is no level loaded
    game_unload_current_level(game);

    //Set the new levels
    game->level = level;
    game->level_draw_parameter = level_draw_parameter;

    game->gravity_is_active = 1;

    //Add them to the render queue
    render_queue_add_item(&game->render_queue, &game->level->renderer, game->level_draw_parameter);
}

void game_handle_input(char character, void* parameters)
{
    game_t* game = (game_t*) parameters;

    player_handle_key(&game->player, character);
}

void game_unload_current_level(game_t* game)
{
    if (game == NULL || game->level == NULL) return;
    if (render_queue_remove_item(&game->render_queue, &game->level->renderer) == 0)
    {
        printf("Unload succesfull\n");
        game->level = NULL;
        game->level_draw_parameter = NULL;
        game->gravity_is_active = 0;
    }
    else 
    {
        printf("Error unloading level!\n");
    }
}

void game_update(game_t* game)
{    
    if (TIME_SECONDS - game->time_last_frame > GAME_REFRESH_DELAY_SECONDS)
    {
        //Clear current window 
        render_window_flush(&game->window);

        //Execute funtions
        level_update_player(game->level, &game->player);


        //Render all objects
        render_queue_render(&game->render_queue);
        render_window_render(&game->window);

        //Update time
        game->time_last_frame = TIME_SECONDS;
    }
}