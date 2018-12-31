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

#include <string.h>
#include <time.h>

#define GAME_PLAYER_FALL_DISTANCE (1)
#define GAME_PLAYER_JUMP_DISTANCE (8)
#define GAME_PLAYER_MOVE_DISTANCE (3)
#define GAME_REFRESH_DELAY_SECONDS (0.05)
#define TIME_SECONDS ((double) clock()/CLOCKS_PER_SEC)

#define GAME_STATUS_GAME_ACTIVE (0x02)
#define GAME_STATUS_GAME_WON (0x04)
#define GAME_STATUS_GRAVITY_ACTIVE (0x01)

typedef struct game
{
    uint8_t game_status;
    key_reader_t input_reader;
    level_t* level;
    level_draw_parameter_t* level_draw_parameter;
    player_t player;
    player_draw_parameter_t player_draw_parameter;
    render_queue_t render_queue;
    double time_last_frame;
    render_window_t window;
} game_t;

/**
 * @brief Creates a game
 * 
 * @param render_queue_size
 * @param window_width  
 * @param window_height 
 * @return game_t 
 */
game_t* game_create(const size_t render_queue_size, const size_t window_width, const size_t window_height);

/**
 * @brief Destroys the game and clean up the memory
 * 
 * @param game 
 */
void game_destroy(game_t* game);

/**
 * @brief Loads a level into the game
 * 
 * @param game 
 * @param level 
 * @param level_draw_parameter 
 */
void game_load_level(game_t* game, level_t* level, level_draw_parameter_t* level_draw_parameter);

/**
 * @brief Handles the user input, according to the key_reader's standard
 * 
 * @param character 
 * @param parameters 
 */
void game_handle_input(char character, void* parameters);

/**
 * @brief Unloads a level if there is one loaded
 * 
 * @param game 
 */
void game_unload_current_level(game_t* game);

/**
 * @brief forces the game to update
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