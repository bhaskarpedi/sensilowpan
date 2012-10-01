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

signed char app_init()
{
#ifdef LOWPAN_COORDINATOR

#else

#endif
	return 0;
}

int main()
{
	signed char appRet = (signed char)-1;

	/* app_init is done before initializing our micro scheduler.
	 * The app_init ensures IP connectivity before we start
	 */
	appRet = app_init();
	if((unsigned char)-1 == appRet)
	{
		/*TODO: Add a warning indicator code.
		 * Maybe flash LEDs to indicate restart-needed
		 */
	}
	else
	{
		msched_init(app_proc);
	}
	while(1);
}
