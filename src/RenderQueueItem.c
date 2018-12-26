#include "RenderQueueItem.h"

render_queue_item_t render_queue_item_create(renderer_t* renderer, void* parameter)
{
    return (render_queue_item_t){parameter, renderer};
}