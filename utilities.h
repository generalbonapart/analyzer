#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define A2D_VOLTAGE_REF_V  1.8
#define A2D_MAX_READING    4095
#define USER "/sys/class/gpio/gpio72/value"


void runCommand(char *command);
bool readUser();
long long getTimeInMs(void);
int getVoltageReading(int index);
void sleepForMs(long long delayInMs);

#endif