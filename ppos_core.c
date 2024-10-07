#include <stdio.h>
#include "ppos.h"
#include "ppos_data.h"


void ppos_init() {
	setvbuf (stdout, 0, _IONBF, 0) ;
	printf("PingPongOs\n");
}


/* 
Task Control Block (TCB).



*/


int task_init (task_t *task, void (*start_routine)(void *),  void *arg) {
	


}
