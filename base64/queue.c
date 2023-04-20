
#include "queue.h"

void queue_init(Queue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
}

void push(Queue *queue, void *data)
{
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    
    if(queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
        return;
    }
    
    queue->rear->next = new_node;
    queue->rear = new_node;
}

void *pop(Queue *queue)
{
    if (queue->front == NULL) {
        return NULL;
    }

    Node *temp_node = queue->front;
    void *data = temp_node->data;
    queue->front = temp_node->next;

    if (queue->front == NULL)
        queue->rear = NULL;

    free(temp_node);
    return data;
}
