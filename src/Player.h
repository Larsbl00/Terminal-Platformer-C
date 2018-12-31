/**
 * @file Player.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-28
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <unistd.h>

#include "Renderer.h"
#include "RenderWindow.h"
#include "Rectangle.h"

#define PLAYER_KEY_JUMP (' ')
#define PLAYER_KEY_MOVE_LEFT ('d')
#define PLAYER_KEY_MOVE_RIGHT ('a')

#define PLAYER_SIZE_HEIGHT (0x03)
#define PLAYER_SIZE_WIDTH (0x05)

const static char player_model[PLAYER_SIZE_HEIGHT][PLAYER_SIZE_WIDTH] = {
    {'(', 'O', '-', 'O', ')'},
    {' ', ' ', '|', ' ', ' '},
    {' ', '/', ' ', '\\', ' '},
};

typedef struct player
{
    const size_t jump_distance;
    const size_t move_distance;
    rectangle_t hit_box;
    renderer_t renderer;
    size_t x;
    size_t y;
} player_t;

typedef struct player_draw_parameter
{
    player_t* player;
    render_window_t* window;
} player_draw_parameter_t;


/**
 * @brief Constructs a new player
 * 
 * @param height 
 * @param width 
 * @return player_t 
 */
player_t player_create(size_t x, size_t y, const size_t jump_distance, const size_t move_distance);

/**
 * @brief Executes actions based on the pressed key
 * 
 * @param player 
 * @param key 
 * 
 * @pre player may not be NULL
 */
void player_handle_key(player_t* player, char key);

/**
 * @brief Draws the player, and is made compateable with the renderers draw function
 * 
 */
void player_draw(void*);

/**
 * @brief Moves the player and it's hitbox
 * 
 * @param player 
 * @param x 
 * @param y 
 */
void player_move(player_t* player, const size_t x, const size_t y);

#endif