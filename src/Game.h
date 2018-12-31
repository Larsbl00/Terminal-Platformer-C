/**
 * @file Game.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-31
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef GAME_H
#define GAME_H


#include "KeyReader.h"
#include "Level.h"
#include "RenderQueue.h"
#include "RenderWindow.h"
#include "Rectangle.h"
#include "Player.h"

typedef struct game
{
    level_t* level;
    level_draw_parameter_t* level_draw_parameter;
    player_t player;
    player_draw_parameter_t player_draw_parameter;
    render_queue_t render_queue;
    render_window_t window;
} game_t;

/**
 * @brief Creates a game
 * 
 * @param render_queue_size 
 * @param window_height 
 * @param window_width 
 * @return game_t 
 */
game_t game_create(const size_t render_queue_size, const size_t window_height, const size_t window_width);

/**
 * @brief Destroys the game and clean up the memory
 * 
 * @param game 
 */
void game_destroy(game_t* game);

/**
 * @brief 
 * 
 * @param game 
 */
void game_update(game_t* game);

/**
 * @brief Attracts the player to the ground, this is the only object effected by gravity this far
 * 
 * @param game 
 */
void game_update_gravity(game_t* game);

#endif