/**
 * @file Rednerer.h
 * @author Lars Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-12-26
 * 
 * @copyright Copyright (c) 2018
 * 
 */

#ifndef RENDERER_H
#define RENDERER_H

typedef struct renderer
{
    void (*render)(void*);
} renderer_t;

#endif