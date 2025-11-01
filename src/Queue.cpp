#include "Queue.hpp"


void queue_init(std::shared_ptr<queue_t> queue)
{
    queue->head = nullptr;
    queue->tail = nullptr;
    queue->numnodes = 0;
}

int queue_isempty(std::shared_ptr<queue_t> queue)
{
    return queue->numnodes == 0;
}

int queue_size(std::shared_ptr<queue_t> queue)
{
    return queue->numnodes;
}

void queue_enqueue(std::shared_ptr<queue_t> queue, queue_item item)
{
    std::shared_ptr<queue_node> newnode = std::make_shared<queue_node>();

    newnode->data = item;
    newnode->next = nullptr;

    if(queue->tail == nullptr)
        queue->head = newnode;
    else
        queue->tail->next = newnode;

    queue->tail = newnode;
    queue->numnodes += 1;
}

queue_item queue_pop(std::shared_ptr<queue_t> queue)
{
    queue_item res;
    std::shared_ptr<queue_node> node;

    if (queue->head == nullptr)
    {
        std::cout << "Error cannot pop from empty queue...\n";
    }

    node = queue->head;
    res = node->data;

    queue->head = queue->head->next;
    if (queue->head == nullptr)
        queue->tail = nullptr;
    
    return res;
}
