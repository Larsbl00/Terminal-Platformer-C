#include <sys/ioctl.h>
#include <unistd.h>

#include "Game.h"
#include "KeyReader.h"
#include "Level.h"
#include "Rectangle.h"
#include "Player.h"

uint8_t is_running = 1;

#define MICROS_PER_SECOND (1000000)
#define SECONDS_TO_MICROS(SECONDS) (SECONDS * MICROS_PER_SECOND)

int main(int argc, char const *argv[])
{
    //Create a window with the current size of the temrinal
    struct winsize terminal;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &terminal);
    const size_t window_height = terminal.ws_row;
    const size_t window_width = terminal.ws_col;

    game_t* game = game_create(10, window_width, window_height);

    ///////////////////////////////////
    //Create level
    rectangle_t floors[] = {
        //Bottom Line
        rectangle_create(0, window_height - 1, window_width - 1, 1, RECTANGLE_PROPERTY_BORDER_TOP),

        //Top line
        rectangle_create(0, 1, window_width - 1, 1, RECTANGLE_PROPERTY_BORDER_BOTTOM | RECTANGLE_PROPERTY_IS_COLLIDABLE),


        //Platforms
        rectangle_create(0, window_height - 5, 10, 5, RECTANGLE_PROPERTY_BORDER_FULL | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(16, window_height - 8, 10, 8, RECTANGLE_PROPERTY_BORDER_FULL | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(30, window_height - 13, 10, 2, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(16, window_height - 17, 10, 2, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(16, window_height - 23, 10, 2, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED), 
        rectangle_create(60, window_height - 7, 10, 5, RECTANGLE_PROPERTY_BORDER_FULL | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),

    };
    const size_t floor_count = (sizeof(floors) / sizeof(*floors));
    level_t level = level_create(game->window.width * 2, game->window.height * 2, floors, floor_count);
    level_draw_parameter_t level_param = {&game->player, &level, &game->window};
    ///////////////////////////////////
    
    //Load the created level
    game_load_level(game, &level, &level_param);

    //Play the game
    while (game->game_status & GAME_STATUS_GAME_ACTIVE)
    {
        game_update(game);
    }


    //Print results
    printf("\n\n----------------\n\n Game Over!\n ");
    if (game->game_status & GAME_STATUS_GAME_WON)
    {
        printf("You won!\n");
    }
    else 
    {
        printf("You lost\n");
    }
    printf("\n----------------\n");

    //Clean
    game_destroy(game);
    free(game);

    //Wait a second so you don't directly type in the terminal
    usleep(SECONDS_TO_MICROS(1.2));

    return 0;
}
