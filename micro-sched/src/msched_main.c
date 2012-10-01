/* @ file: 		msched_main.c
 * @ description: 	This is used to define the main scheduler functionalities
 * @ functions:		
 * 	msched_init
 * 	msched_proc_tasks
 * @ author/ date: 	Bhaskar Pediredla 1/10/2012
 */

#include <stdio.h>
#include "msched.h"

#define MSCHED_NEXT_TSK_ID(x) {\
	(x)=(((x)+1) % MSCHED_MAX_TASKS);\
	if(0==(x)) (x)=1;\
	}\

#define MSCHED_TASK_INIT(id1,type1,task1) {\
	msched_tasks[id1].task_id=id1;\
	msched_tasks[id1].t = type1;\
	msched_tasks[id1].task = task1;\
	}\

/* All tasks initialized to MSCHED_STATE_INIT */
mschedTask_t msched_tasks[MSCHED_MAX_TASKS];
unsigned char currentTaskId;

void msched_proc_tasks(void *input)
{
	currentTaskId = 0;
	static unsigned tskIdx = 1;
	while(1)
	{
		if(MSCHED_STATE_READY == msched_tasks[tskIdx].s)
		{
			if(!msched_tasks[tskIdx].task)
				msched_tasks[tskIdx].task(NULL);
		}
		MSCHED_NEXT_TSK_ID(tskIdx);
	}
}

int msched_init(void (*app_task)(void *))
{

	/* The scheduler is the first task */
	MSCHED_TASK_INIT(0, MSCHED_TASKTYPE_NORM, msched_proc_tasks);
	//msched_tasks[0] = msched_proc_tasks;

	/* The timer is the second task */
	MSCHED_TASK_INIT(1, MSCHED_TASKTYPE_TIMER, NULL);
	//msched_tasks[1] = timer_task;

	/* Other tasks follow */
	MSCHED_TASK_INIT(2, MSCHED_TASKTYPE_NORM, app_task);
	//msched_tasks[2] = app_task;

	msched_proc_tasks(NULL);

	return 0;
}


