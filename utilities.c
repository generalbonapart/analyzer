#include "utilities.h"

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