//This module does the analysis of light samples every 1 second
#ifndef ANALYSIS_H
#define ANALYSIS_H

#define THRESHOLD 0.1
#define HYSTERESIS 0.03
#define WEIGHT 0.999

int copyInfo(double* target);
void start_analysis();

#endif


