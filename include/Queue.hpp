#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdlib.h>
#include <iostream>

/*
    Using this queue structure as a frame buffer.
*/

typedef void* queue_item;

typedef struct queue_node
{
    queue_item data;
    struct queue_node* next;

} queue_node;

typedef struct queue_t
{
    queue_node* head;
    queue_node* tail;
    int numnodes;
} queue_t;

/*Initializes data structure*/
void queue_init(queue_t* queue);

/* Return 1 if empty, 0 otherwise */
int queue_isempty(queue_t* queue);

/* Return size of queue */
int queue_size(queue_t* queue);

/* Add an item to the back of queue */
int queue_enqueue(queue_t* queue, queue_item item);

/* Removes an element from front of queue */
queue_item queue_pop(queue_t* queue);


#endif // QUEUE_HPP