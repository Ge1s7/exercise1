#include <stdlib.h>

typedef struct Node {
	void *data;
	struct Node *next;
} Node;

typedef struct Queue {
	Node *front, *rear;
	int size;
} Queue;

void push(Queue *q, void *data);
void *pop(Queue *q);
Queue new_queue();