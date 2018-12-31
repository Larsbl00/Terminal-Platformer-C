#include <sys/ioctl.h>

#include "Game.h"
#include "KeyReader.h"
#include "Level.h"
#include "Rectangle.h"
#include "Player.h"

uint8_t is_running = 1;

int main(int argc, char const *argv[])
{
    //Create a window with the current size of the temrinal
    struct winsize terminal;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &terminal);
    const size_t game_height = terminal.ws_row;
    const size_t game_width = terminal.ws_col;

    game_t* game = game_create(10, game_width, game_height);


    rectangle_t floors[] = {
        rectangle_create(0, game_height - 5, 10, 5, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(12, game_height - 5, 10, 3, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(24, game_height - 5, 10, 3, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(0, game_height - 20, 10, 3, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(70, game_height - 5, 10, 5, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
    };
    const size_t floor_count = (sizeof(floors) / sizeof(*floors));
    level_t level = level_create(game->window.width, game->window.height, floors, floor_count);
    level_draw_parameter_t level_param = {&game->player, &level, &game->window};

    game_load_level(game, &level, &level_param);


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

    return 0;
}
