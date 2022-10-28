#include "photoRes.h"
#include "utilities.h"
#define RESISTOR 10000

double PhotoRes_resistance(){

    int reading = getVoltageReading(1);
	double voltage = ((double)reading / A2D_MAX_READING) * A2D_VOLTAGE_REF_V;

    double res = A2D_VOLTAGE_REF_V*RESISTOR/voltage - RESISTOR;
    return res;

}