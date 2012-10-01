/* @ file: 		msched.h
 * @ brief:
 * 	1. The msched is a mini scheduler used especially for the task of porting 
 * 	6lowpan onto cc430.
 * 	2. It makes use of a task scheduling based on round robin algorithm.
 * 	3. Each task would run till completion (one entire while loop is allowed 
 * 	to be complete) before another task takes control.
 * 	4. The non real time timers run on the same philosophy, i.e. they are
 * 	processed only after a task is run to completion.
 * 	5. The tasks are maintained in a structure array.
 * 	6. The tasks should always be written in while(1) and use only
 * 	   static variables if retention is sought
 * 	7. The timer interrupts take priority over the normal tasks
 * 
 *
 * @ description: 	Header file for msched_main.c	
 * @ functions:		
 * @ author/ date: 	Bhaskar Pediredla 1/10/2012
 */
 


#ifndef __MSCHED_
#define __MSCHED_
#endif

#ifdef __MSCHED_

#include <stdio.h>

#define MSCHED_FAIL -1
#define MSCHED_SUCCESS 0

#define MSCHED_MAX_TASKS 5
#define MSCHED_USLEEP(x)
/*TODO: Add a usleep for the macro */

typedef enum {
	MSCHED_STATE_INIT =0,
	MSCHED_STATE_READY,
	MSCHED_STATE_SLEEP,
	MSCHED_STATE_BLOCK,
	MSCHED_STATE_TERMINATE
} taskState_t;

typedef enum {
	MSCHED_TASKTYPE_NORM,
	MSCHED_TASKTYPE_TIMER
} taskType_t;

/* Structure for the scheduler tasks */
typedef struct{
	unsigned char task_id;				/* Task ID. Useful while posting */
	taskState_t s;				/* State of the task */
	taskType_t t;				/* Type of the task */
	void (* task)(void *);	/* Actual Task. Function that runs while(1) */
} mschedTask_t;

/* This ID is updated by scheduler before allowing a task to run.
 * This ID can be used by tasks to start timers and timers to post
 * back timer events */
extern unsigned char currentTaskId;

extern mschedTask_t msched_tasks[MSCHED_MAX_TASKS];

/* This function gets the scheduler running.
 * All the tasks are saved to the msched_tasks
 * array in this function.
 * app_task is the single task that is to be scheduled
 * Retvalue MSCHED_FAIL or MSCHED_SUCCESS */
extern int msched_init(void (*app_task)(void *));

/* This function processes all the timers */
//extern void msched_proc_tmrs();

/* This function processes all the tasks */
extern void msched_proc_tasks();

#endif
