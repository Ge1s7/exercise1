#include <stdlib.h>

typedef struct Node {
    void* data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

void queue_init(Queue *queue);
void push(Queue *queue, void *data);
void *pop(Queue *queue);