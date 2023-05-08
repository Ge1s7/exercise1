#include <stdlib.h>

typedef struct Node {
	void *data;
	struct Node *next;
} Node;

typedef struct Queue {
	Node *front;
	Node *rear;
	int size;
} Queue;

void queue_init(Queue *q);
void push(Queue *q, void *data);
void *pop(Queue *q);