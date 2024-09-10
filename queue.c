#include "queue.h"
#include <stdio.h>

//------------------------------------------------------------------------------
// Conta o numero de elementos na fila
// Retorno: numero de elementos na fila
int queue_size (queue_t * queue) {
	if(queue == NULL) return 0;
	int size = 1; queue_t *it = queue;
	while(it->next != queue){
		it = it->next;
		size++;
	}
	return size;
}

// Percorre a fila e imprime na tela seu conteúdo. A impressão de cada
// elemento é feita por uma função externa, definida pelo programa que
// usa a biblioteca. Essa função deve ter o seguinte protótipo:
//
// void print_elem (void *ptr) ; // ptr aponta para o elemento a imprimir
void queue_print (char *name, queue_t *queue, void print_elem (void*)){
		
}

int queue_append (queue_t **queue, queue_t *elem) {
	if(queue == NULL) {puts("queue don't exist"); return -1;}
	if(elem  == NULL) {puts("element don't exist"); return -1;}

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

//------------------------------------------------------------------------------
// Remove o elemento indicado da fila, sem o destruir.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir -- ok.
// - a fila nao deve estar vazia -- ok.
// - o elemento deve existir -- ok.
// - o elemento deve pertencer à fila indicada -- ok. 
// Retorno: 0 se sucesso, <0 se ocorreu algum erro
int queue_remove (queue_t **queue, queue_t *elem) {
	if(queue == NULL) {puts("queue don't exist"); return -1;}
	if(elem  == NULL) {puts("element don't exist"); return -1;}

	queue_t *it = (*queue);
	int counter = 0; int q_size = queue_size((*queue));
	while(it != (elem) && counter != q_size)
		{counter++; it = it->next;}
	
	if(it != elem)
		{puts("element don't belong to queue..."); return -1;}
	
	it->prev->next = it->next; 
	it->next->prev = it->prev;
	if(counter == 0) 
		(*queue) = it->next;
	it->next = NULL; it->prev = NULL;
	return 0;
}
