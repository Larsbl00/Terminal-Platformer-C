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

#define PLAYER_KEY_MOVE_DOWN ('s')
#define PLAYER_KEY_MOVE_LEFT ('d')
#define PLAYER_KEY_MOVE_RIGHT ('a')
#define PLAYER_KEY_MOVE_UP ('w')
#define PLAYER_KEY_JUMP (' ')

typedef struct player
{
    rectangle_t hit_box;
    renderer_t renderer;
    size_t x;
    size_t y;
} player_t;

/**
 * @brief Constructs a new player
 * 
 * @param height 
 * @param width 
 * @return player_t 
 */
player_t player_create(size_t x, size_t y, const size_t height, const size_t width);

/**
 * @brief Executes actions based on the pressed key
 * 
 * @param player 
 * @param key 
 */
void player_handle_key(player_t* player, char key);

/**
 * @brief Draws the player, and is made compateable with the renderers draw function
 * 
 */
void player_draw(void*);

#endif