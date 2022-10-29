#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define A2D_VOLTAGE_REF_V  1.8
#define A2D_MAX_READING    4095


int getVoltageReading(int index);
void sleepForMs(long long delayInMs);

#endif