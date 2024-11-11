#include "queue.h"
#include <stdio.h>

int queue_size (queue_t * queue) {
	if(queue == NULL) return 0;
	int size = 1; queue_t *it = queue;
	while(it->next != queue){
		it = it->next;
		size++;
	}
	return size;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*)){
	printf("%s: ", name);
	if(queue == NULL) {printf("[]\n"); return;} 
	queue_t *it = queue;
	printf("[");
	do {
		print_elem(it);
		it = it->next;
		if(it != queue) printf(" ");
	} while(it != queue);
	printf("]");
	printf("\n");
}

int cantAppendElem(queue_t *elem) {
	if(elem->next != NULL || elem->prev != NULL) return 1;
	return 0;
}

int queue_append (queue_t **queue, queue_t *elem) {
	if(queue == NULL) {puts("queue don't exist"); return -1;}
	if(elem  == NULL) {puts("element don't exist"); return -1;}

	if(cantAppendElem(elem)) {puts("element is in another queue"); return -1;}

	if(queue_size(*queue) == 0) {
		elem->next = elem; 
		elem->prev = elem;
		*queue = elem;
	}else{
		elem->prev = (*queue)->prev;
		elem->next = (*queue);
		(*queue)->prev->next = elem;
		(*queue)->prev = elem;
	}

	return 0;
}

int inRightQueue(queue_t *it, queue_t *elem) {
	queue_t *first_elem = it;
	do{
		if(it == elem) return 1;
		it = it->next;
	} while(it != first_elem);
	return 0;
}

int cantRemove(queue_t **queue, queue_t *elem) {
	if(queue == NULL) {puts("queue don't exist"); return 1;}
	if(*queue == NULL) {puts("empty queue"); return 1;}
	if(elem  == NULL) {puts("element don't exist"); return 1;}
	return 0;
}

void eliminateQueue(queue_t **queue) {
	(*queue)->next = (*queue)->prev = NULL;
	(*queue) = NULL;
}

void cutQueue(queue_t **queue, queue_t *elem){
	if((*queue) == elem) (*queue) = elem->next;

	queue_t *nextIt = elem->next;
	queue_t *prevIt = elem->prev;

	nextIt->prev = prevIt;
	prevIt->next = nextIt;
	elem->next = elem->prev = NULL;
}

int queue_remove (queue_t **queue, queue_t *elem) {
	if(cantRemove(queue, elem)) {return -1;}

	if (!inRightQueue((*queue), elem)) {
		puts("The element doesn't belong to the right queue");	
		return 0;
	}

	if(queue_size(*queue) > 1) 
		cutQueue(queue, elem);
	else 
		eliminateQueue(queue);
	
	return 0;
}

queue_t* rotate_queue(queue_t** q) {
	queue_t* first_val = (*q);	
	cutQueue(q, first_val);	
	return first_val;					
}

