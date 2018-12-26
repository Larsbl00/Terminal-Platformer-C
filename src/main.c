#include "KeyReader.h"
#include "RenderQueue.h"
#include "RenderWindow.h"

uint8_t is_running = 1;

void key_press_handler(char pressed_char, void* arguments)
{
    printf("You pressed: %c\n", pressed_char);
}

void test_render(void* arg)
{
    printf("Rendering\n");
}


int main(int argc, char const *argv[])
{
    key_reader_t key_reader = key_reader_create(key_press_handler, NULL);

    render_queue_t queue = render_queue_create(5);

    renderer_t test = (renderer_t){test_render};
    renderer_t test2 = (renderer_t){test_render};
    renderer_t test3 = (renderer_t){test_render};

    printf("Add result: %i\n", render_queue_add_item(&queue, &test, NULL));
    printf("Add result: %i\n", render_queue_add_item(&queue, &test2, NULL));
    printf("Add result: %i\n", render_queue_add_item(&queue, &test3, NULL));
    printf("Remove result: %i\n", render_queue_remove_item(&queue, &test2));
    printf("Remove result: %i\n", render_queue_remove_item(&queue, &test2));
    printf("Add result: %i\n", render_queue_add_item(&queue, &test, NULL));

    render_queue_render(&queue);

    render_window_t window = render_window_create(10, 100);

    render_window_flush(&window);

    render_window_destroy(&window);

    key_reader_destroy(&key_reader);

    render_queue_destroy(&queue);

    return 0;
}
