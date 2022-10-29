#include "utilities.h"

void sleepForMs(long long delayInMs)
{
	const long long NS_PER_MS = 1000 * 1000;
	const long long NS_PER_SECOND = 1000000000;
	long long delayNs = delayInMs * NS_PER_MS;
	int seconds = delayNs / NS_PER_SECOND;
	int nanoseconds = delayNs % NS_PER_SECOND;
	struct timespec reqDelay = {seconds, nanoseconds};
	nanosleep(&reqDelay, (struct timespec *) NULL);
}


int getVoltageReading(int index)
{
	// Open file
	char address[50];
	sprintf(address, "/sys/bus/iio/devices/iio:device0/in_voltage%d_raw", index);
	FILE *f = fopen(address,"r");
	if (!f) {
		printf("ERROR: Unable to open voltage input file. Cape loaded?\n");
		printf("       Check /boot/uEnv.txt for correct options.\n");
		exit(-1);
	}

	// Get reading
	int a2dReading = 0;
	int itemsRead = fscanf(f, "%d", &a2dReading);
	if (itemsRead <= 0) {
		printf("ERROR: Unable to read values from voltage input file.\n");
		exit(-1);
	}

	// Close file
	fclose(f);

	return a2dReading;
}