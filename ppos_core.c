#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"
#include "ppos_data.h"

void ppos_init() {
	getcontext(&(main_task.context));	
	current_task = &main_task;
	id_task = 0;
	setvbuf (stdout, 0, _IONBF, 0) ;
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
	return 1;
}

int task_init (task_t *task, void (*start_routine)(void *),  void *arg) {	
	if(!set_task_stack(task)) return -1;	
	
	getcontext(&(task->context)); 
	makecontext(&(task->context), (void *)(*start_routine), 1, arg);			
		
	return task->id;
}

int task_switch (task_t *task) {		 
	swapcontext(&current_task->context, &task->context); 	
	current_task = task;
	return 0;
}

void task_exit(int exit_code) {
			
}
