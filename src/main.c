#include "KeyReader.h"
#include "RenderQueue.h"

uint8_t is_running = 1;

void key_press_handler(char pressed_char, void* arguments)
{
    printf("You pressed: %c\n", pressed_char);
}


int main(int argc, char const *argv[])
{
    key_reader_t key_reader = key_reader_create(key_press_handler, NULL);

    render_queue_t queue = render_queue_create(60);



    key_reader_destroy(&key_reader);

    render_queue_destroy(&queue);

    return 0;
}
