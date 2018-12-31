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

    game_t* game = game_create(10, terminal.ws_row, terminal.ws_col);



    rectangle_t floors[] = {
        rectangle_create(0, 22, 10, 3, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(12, 22, 10, 3, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(73, 22, 10, 3, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(0, 15, 10, 3, RECTANGLE_PROPERTY_BORDER_TOP | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
    };
    size_t floor_count = (sizeof(floors) / sizeof(*floors));
    level_t level = level_create(game->window.width, game->window.height, floors, floor_count);
    level_draw_parameter_t level_param = {&game->player, &level, &game->window};

    game_load_level(game, &level, &level_param);

    while (is_running)
    {
        game_update(game);
    }

    //Clean
    game_destroy(game);

    return 0;
}
