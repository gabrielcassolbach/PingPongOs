// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.5 -- Março de 2023

// Teste do task dispatcher e escalonador FCFS

#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"

task_t Pang, Peng, Ping, Pong, Pung ;

// corpo das threads
void Body (void * arg)
{
   int i ;

   printf ("%s: inicio\n", (char *) arg) ;
   for (i=0; i<5; i++)
   {
      printf ("%s: %d\n", (char *) arg, i) ;
      task_yield ();
   }
   printf ("%s: fim\n", (char *) arg) ;
   task_exit (0) ;
}

int main (int argc, char *argv[])
{
   printf ("main: inicio\n");

   ppos_init () ;

   task_init (&Pang, Body, "    Pang") ;
   task_init (&Peng, Body, "        Peng") ;
   task_init (&Ping, Body, "            Ping") ;
   task_init (&Pong, Body, "                Pong") ;
   task_init (&Pung, Body, "                    Pung") ;

   printf ("main: fim\n");
   task_exit (0);
}

#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"
#include "ppos_data.h"

/*
--------------------------------------------------------------------------------------
1 - O dispatcher deve ser implementado como uma tarefa, a ser iniciada usando 
a chamada task_init durante a inicialização do sistema (execução de ppos_init).
2 - O programa principal inicia todas as tarefas de usuário e passa o controle 
para a tarefa dispatcher, que só encerra quandon não existirem mais tarefas de 
usuário a executar.
3 - Será necessário implementar uma fila de tarefas prontas, usando a biblioteca 
de filas genéricas desenvolvida anteriormente.
4 - A política de escalonamento será definida por uma função scheduler(), chamada 
pelo dispatcher para decidir qual é a próxima tarefa a ativar, First come, first served).
5 - Quando uma tarefa encerrar, o controle volta ao dispatcher e este libera 
estruturas de dados alocadas para a tarefa. 
6 - Quando o dispatcher encerrar, a chamada task_exit deve encerrar o programa chamando
exit.
---------------------------------------------------------------------------------------
*/
queue_t* ready; 

task_t main_task, dispatcher_t;
task_t *current_task;
int id_task;

void ppos_init() {
	getcontext(&(main_task.context));	
	current_task = &main_task;
	task_init(&dispatcher_t, dispatcher, "");
	id_task = 0;
	setvbuf (stdout, 0, _IONBF, 0) ;
}

void task_yield() {
	queue_append(&ready, (queue_t*)  &(dispatcher_t));
	task_switch(&dispatcher_t);
}

task_t* scheduler() {
	if(queue_size(ready) == 0) return NULL;
	if(queue_size(ready) == 1) return ready;
	return rotate_queue(&ready);					 
}

void dispatcher() {
	queue_remove(&ready, (queue_t *) &dispatcher_t);
	while(queue_size(ready)) {
		task_t *next_task = scheduler();
		if(next_task != NULL) {
			task_switch(next_task);
		}					
	}		
}

int set_task_stack(task_t *task) {
	char *stack;
	stack = malloc (STACKSIZE);
	if(stack) {
		task->context.uc_stack.ss_sp = stack;
		task->context.uc_stack.ss_size = 64*1024;
		task->context.uc_stack.ss_flags = 0;
		task->context.uc_link = 0;
		id_task++;
		task->id = id_task;	
	}else {
		return 0;
	}
	return 
}

int task_init (task_t *task, void (*start_routine)(void *),  void *arg) {	
	if(!set_task_stack(task)) return -1;	
	getcontext(&(task->context)); 
	makecontext(&(task->context), (void *)(*start_routine), 1, arg);			
	return task->id;
}

int task_switch (task_t *task) {
	task_t *aux_t = current_task;
	current_task = task;
	swapcontext(&aux_t->context, &task->context); 	
	return 0;
}

void task_exit(int exit_code) {
	task_switch(&main_task);			
}

int task_id() {
	return (current_task->id);
}

