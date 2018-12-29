#include <sys/ioctl.h>

#include "KeyReader.h"
#include "Level.h"
#include "RenderQueue.h"
#include "RenderWindow.h"
#include "Rectangle.h"
#include "Player.h"

uint8_t is_running = 1;

void key_press_handler(char pressed_char, void* arguments)
{
    printf("You pressed: %c\n", pressed_char);
}


int main(int argc, char const *argv[])
{
    //Create a window with the current size of the temrinal
    struct winsize terminal;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &terminal);
    render_window_t window = render_window_create(terminal.ws_row, terminal.ws_col);

    key_reader_t key_reader = key_reader_create(key_press_handler, NULL);
    render_queue_t queue = render_queue_create(5);


    rectangle_t rect = rectangle_create(2, 0, 5, 5, RECTANGLE_PROPERTY_BORDER_FULL | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED);
    rectangle_draw_parameter_t rect_param = (rectangle_draw_parameter_t){&rect, &window};

    rectangle_t rect2 = rectangle_create(2, 5, 5, 5, RECTANGLE_PROPERTY_BORDER_FULL | RECTANGLE_PROPERTY_IS_COLLIDABLE);
    rectangle_draw_parameter_t rect_param2 = (rectangle_draw_parameter_t){&rect2, &window};

    player_t player = player_create(2, 19, 1, 1);
    player_draw_parameter_t player_param = (player_draw_parameter_t){&player, &window};

    rectangle_t floors[] = {
        rectangle_create(0, 22, 10, 3, RECTANGLE_PROPERTY_BORDER_FULL | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(12, 22, 10, 3, RECTANGLE_PROPERTY_BORDER_FULL | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(73, 22, 10, 3, RECTANGLE_PROPERTY_BORDER_FULL | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
        rectangle_create(0, 15, 10, 3, RECTANGLE_PROPERTY_BORDER_FULL | RECTANGLE_PROPERTY_IS_COLLIDABLE | RECTANGLE_PROPERTY_IS_FILLED),
    };

    size_t floor_count = (sizeof(floors) / sizeof(*floors));

    level_t level = level_create(window.width, window.height, floors, floor_count);
    level_draw_parameter_t level_param = {&player, &level, &window};

    printf("Add result: %i\n", render_queue_add_item(&queue, &level.renderer, &level_param));
    printf("Add result: %i\n", render_queue_add_item(&queue, &rect.renderer, &rect_param));
    printf("Add result: %i\n", render_queue_add_item(&queue, &rect2.renderer, &rect_param2));
    printf("Add result: %i\n", render_queue_add_item(&queue, &player.renderer, &player_param));
    


    printf("Collision: %i\n", rectangle_collides_with_rectangle(&rect2, &player.hit_box));

    level_update_player(&level, &player);

    //Calls the render function of each item in the queue
    render_queue_render(&queue);
    //Renders the window
    render_window_render(&window);

    //Clean
    render_window_destroy(&window);
    key_reader_destroy(&key_reader);
    render_queue_destroy(&queue);

    

    return 0;
}
