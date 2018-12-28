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

typedef struct player
{

    rectangle_t hit_box;
    renderer_t renderer;
    size_t x;
    size_t y;
} player_t;

#endif