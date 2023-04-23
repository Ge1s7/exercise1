#include "queue.h"

void queue_init(Queue *q)
{
	q->front = NULL;
	q->rear = NULL;
	q->size = 0;
}

void push(Queue *q, void *data)
{
	q->size++;
	Node *new_node = (Node*) malloc(sizeof(Node));
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
