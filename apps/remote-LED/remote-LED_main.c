#include <stdio.h>
#include "msched.h"

void app_proc(void *data)
{
	while(1)
	{
	   /* TODO: Add code to toggle an LED */	
		MSCHED_USLEEP(1500);
	}
}

int main()
{
	//app_init();
	msched_init(app_proc);
	while(1);
}
