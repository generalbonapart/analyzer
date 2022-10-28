#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "utilities.h"
#include "photoRes.h"
#include "joystick.h"

static void sleepForMs(long long delayInMs)
{
	const long long NS_PER_MS = 1000 * 1000;
	const long long NS_PER_SECOND = 1000000000;
	long long delayNs = delayInMs * NS_PER_MS;
	int seconds = delayNs / NS_PER_SECOND;
	int nanoseconds = delayNs % NS_PER_SECOND;
	struct timespec reqDelay = {seconds, nanoseconds};
	nanosleep(&reqDelay, (struct timespec *) NULL);
}


int main()
{
	while(true){

		//char c = Joystick_position();
		//printf("x= %5.2fV \t y= %5.2fV \n", *x, *y);
		//printf("Position: %c\n", c);
		double res = PhotoRes_resistance();
		printf("Resistance: %f\n", res);
		sleepForMs(100);
	}
	return 0;
}
