#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <memory>

/*
    Using this queue structure as a frame buffer.
*/

typedef void* queue_item;

typedef struct queue_node
{
    queue_item data;
    std::shared_ptr<queue_node> next;

} queue_node;

typedef struct queue_t
{
    std::shared_ptr<queue_node> head;
    std::shared_ptr<queue_node> tail;
    int numnodes;
} queue_t;

/*Initializes data structure*/
void queue_init(std::shared_ptr<queue_t> queue);

/* Return 1 if empty, 0 otherwise */
int queue_isempty(std::shared_ptr<queue_t> queue);

/* Return size of queue */
int queue_size(std::shared_ptr<queue_t> queue);

/* Add an item to the back of queue */
int queue_enqueue(std::shared_ptr<queue_t> queue, queue_item item);

/* Removes an element from front of queue */
queue_item queue_pop(std::shared_ptr<queue_t> queue);


#endif // QUEUE_HPP