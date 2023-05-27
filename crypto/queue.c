#include <stdlib.h>
#include "queue.h"

Queue new_queue()
{
	return (Queue) { .front = NULL, .rear = NULL, .size = 0 };
}

void push(Queue *q, void *data)
{
	Node *new_node = (Node*) malloc(sizeof(Node));
	if (new_node) {
		q->size++;
	}
	new_node->data = data;
	new_node->next = NULL;

	if(q->rear == NULL) {
		q->front = new_node;
		q->rear = new_node;
		return;
	}

	q->rear->next = new_node;
	q->rear = new_node;
}

void *pop(Queue *q)
{
	if (q->front == NULL) {
		return NULL;
	}

	Node *temp_node = q->front;
	void *data = temp_node->data;
	q->front = temp_node->next;

	if (q->front == NULL) {
		q->rear = NULL;
	}

	q->size--;
	free(temp_node);
	return data;
}
