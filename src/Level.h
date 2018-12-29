/**
 * @file Level.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-29
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>
#include <unistd.h>

#include "Player.h"
#include "Renderer.h"
#include "RenderWindow.h"
#include "Rectangle.h"

typedef struct level
{
    const size_t width;
    const size_t height;

    rectangle_t* floors;
} level_t;



#endif