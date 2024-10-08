#include <stdio.h>
#include "ppos.h"
#include "ppos_data.h"

/* 
typedef struct task_t
{
  struct task_t *prev, *next ;		// ponteiros para usar em filas
  int id ;				// identificador da tarefa
  ucontext_t context ;			// contexto armazenado da tarefa
  short status ;			// pronta, rodando, suspensa, ...
  // ... (outros campos serão adicionados mais tarde)
} task_t ;
*/

int task_id () {
	return 1;
}

void ppos_init() {
	setvbuf (stdout, 0, _IONBF, 0) ;
}

int task_init (task_t *task, void (*start_routine)(void *),  void *arg) {	
	return 1;
}

void task_exit (int exit_code) {

	
}

int task_switch (task_t *task) {
	
	task

}


/*
Duas tarefas: Tarefa Ping e tarefa Pong.
---------------------------------------



*/



