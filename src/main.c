#include "KeyReader.h"

uint8_t is_running = 1;

void key_press_handler(char pressed_char, void* arguments)
{
    printf("You pressed: %c\n", pressed_char);
}


int main(int argc, char const *argv[])
{
    key_reader_t key_reader = key_reader_create(key_press_handler, NULL);


    while(is_running) key_reader_poll(&key_reader);

    key_reader_destroy(&key_reader);

    return 0;
}
