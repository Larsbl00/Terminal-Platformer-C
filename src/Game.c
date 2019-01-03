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

game_t* game_create(const size_t render_queue_size, const size_t window_width, const size_t window_height)
{
    //Init the game
    game_t game = {
        .game_status = GAME_STATUS_GAME_ACTIVE,
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

    game->game_status |= GAME_STATUS_GRAVITY_ACTIVE;

    //Add them to the render queue
    render_queue_add_item(&game->render_queue, &game->level->renderer, game->level_draw_parameter);
}

void game_handle_input(char character, void* parameters)
{
    game_t* game = (game_t*) parameters;
    player_handle_key(&game->player, character);
}

void game_handle_player_render_zone(game_t* game)
{
    //Check if the player is leaving the field horizontally
    if (game->player.x < (game->window.x))
    {
        render_window_move(&game->window, game->window.width - (game->player.x + game->player.hit_box.width), game->window.y);
    }
    else if ((game->player.x + game->player.hit_box.width) >= (game->window.x + game->window.width))
    {
        render_window_move(&game->window, game->player.x, game->window.y);
    }

    //Check if the player is leaving via the bottom
    else if (game->player.y > (game->window.y + game->window.height))
    {
        render_window_move(&game->window, game->window.x, game->player.y);
    }
    else if ((game->player.y + game->player.hit_box.height) < game->window.y)
    {
        render_window_move(&game->window, game->window.x, (game->player.y + game->player.hit_box.height));
    }

}

void game_unload_current_level(game_t* game)
{
    if (game == NULL || game->level == NULL) return;
    if (render_queue_remove_item(&game->render_queue, &game->level->renderer) == 0)
    {
        printf("Level Unloaded\n");
        game->level = NULL;
        game->level_draw_parameter = NULL;
        game->game_status &= ~GAME_STATUS_GRAVITY_ACTIVE;
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


        //Let the gravity do his thing
        game_update_gravity(game);

        //Read pressed key
        key_reader_poll(&game->input_reader);

        player_handle_movement(&game->player);

        //Update player
        level_update_player(game->level, &game->player);
    
        
        //Player won game
        if (game->player.x > game->level->width)
        {
            //Stop game
            game->game_status &= ~GAME_STATUS_GAME_ACTIVE; 

            //Flag for victory
            game->game_status |= GAME_STATUS_GAME_WON;
        }
        //Player fell out of map
        else if (game->player.y > game->level->height)
        {
            //Stop game
            game->game_status &= ~GAME_STATUS_GAME_ACTIVE; 
            //Flag for loss
            game->game_status &= ~GAME_STATUS_GAME_WON;
        }

        game_handle_player_render_zone(game);

        //Render all objects
        render_queue_render(&game->render_queue);
        render_window_render(&game->window);

        //Update time
        game->time_last_frame = TIME_SECONDS;
    }
}

void game_update_gravity(game_t* game)
{
    player_t* player = &game->player;
    player_move(player, player->x, player->y + GAME_PLAYER_FALL_DISTANCE);
}