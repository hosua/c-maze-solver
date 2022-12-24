#include "priority_queue.h"

void PQ_push(PriorityQueue *pq, int data, int priority) {
	if (pq->size >= PQ_LIMIT) {
		fprintf(stderr, "Error: Priority queue is full.\n");
		return;
	}

	PQ_Node new_node;
	new_node.data = data;
	new_node.priority = priority;

	int i = pq->size;
	pq->queue[i] = new_node;
	pq->size++;

	while (i > 0 && pq->queue[(i-1)/2].priority > pq->queue[i].priority) {
		swap(pq->queue[(i-1)/2], pq->queue[i]);
		i = (i-1)/2;
	}
}

int PQ_pop(PriorityQueue *pq) {
	if (pq->size == 0) {
		fprintf(stderr, "Error: Priority queue is empty.\n");
		return -1;
	}

	int data = pq->queue[0].data;
	pq->queue[0] = pq->queue[pq->size - 1];
	pq->size--;

	int i = 0;
	while (true) {
		int left = (2*i)+1;
		int right = (2*i)+2;
		int min_index = i;

		if (left < pq->size && pq->queue[left].priority < pq->queue[min_index].priority) {
			min_index = left;
		}
		if (right < pq->size && pq->queue[right].priority < pq->queue[min_index].priority) {
			min_index = right;
		}
		if (min_index == i) {
			break;
		}

		swap(pq->queue[i], pq->queue[min_index]);
		i = min_index;
	}

	return data;
}

// int main() {
// 	PriorityQueue pq;
// 	pq.size = 0;
// 
// 	PQ_push(&pq, 1, 3);
// 	PQ_push(&pq, 2, 2);
// 	printf("%i\n", PQ_pop(&pq)); 
// 
// 	return 0;
// }

