#include "Queue.hpp"


void queue_init(queue_t* queue)
{
    queue->head = nullptr;
    queue->tail = nullptr;
    queue->numnodes = 0;
}

int queue_isempty(queue_t* queue)
{
    return queue->numnodes == 0;
}

int queue_size(queue_t* queue)
{
    return queue->numnodes;
}

int queue_enqueue(queue_t* queue, queue_item item)
{
    queue_node* newnode = (queue_node*)malloc(sizeof(queue_node));

    newnode->data = item;
    newnode->next = nullptr;

    if(queue->tail == nullptr)
        queue->head = newnode;
    else
        queue->tail->next = newnode;

    queue->tail = newnode;
    queue->numnodes += 1;
}

queue_item queue_pop(queue_t* queue)
{
    queue_item res;
    queue_node* node;

    if (queue->head == nullptr)
    {
        std::cout << "Error cannot pop from empty queue...\n";
    }

    node = queue->head;
    res = node->data;

    queue->head = queue->head->next;
    if (queue->head == nullptr)
        queue->tail == nullptr;
    
    free(node);
    return res;
}

