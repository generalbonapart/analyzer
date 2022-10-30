#include "analysis.h"
#include "sampler.h"
#include "utilities.h"

double averageVoltage = 0;
double minV, maxV;
double minInt, maxInt, averageInt;
bool firstSample = 0;

bool currentDip = 0;
int numDips = 0;

void handleDips(double sample)
{
    if(currentDip == 0)
    {
        if(sample < 0.87*averageVoltage){
            currentDip = 1;
            numDips++;
        }
    }
    else
    {
        if(sample > 0.93*averageVoltage){
            currentDip = 0;
        }
    }
}

void analysis(samplerDatapoint_t* Buffer, int length){
	maxV = maxInt = 0;
	minInt = minV = 100.0;
	double totalTime = 0;
    currentDip = 0;
    numDips = 0;

	for (int i=0; i<length; i++){
		samplerDatapoint_t sample = Buffer[i];
		if(sample.sampleInV > maxV){ 
			maxV = sample.sampleInV;
		}
		if(sample.sampleInV < minV){ 
			minV = sample.sampleInV;
		}
        handleDips(sample.sampleInV);
		if(sample.IntervalInMilliS > maxInt){ 
			maxInt = sample.IntervalInMilliS;
		}
		if(sample.IntervalInMilliS < minInt){ 
			minInt = sample.IntervalInMilliS;
		}
		totalTime += sample.IntervalInMilliS;
		averageVoltage = 0.999*averageVoltage + 0.001*sample.sampleInV;
	}

	averageInt = totalTime/length;

}

void start_analysis(){
	long long startTime = getTimeInMs();
	samplerDatapoint_t* Buffer;
	int* length = malloc(4);
	Buffer = Sampler_extractAllValues(length);
	//int total = Sampler_getNumSamplesTaken();
	if(firstSample == 0){
		averageVoltage = Buffer[0].sampleInV;
		firstSample = 1;
	}
	analysis(Buffer, (*length));

	printf("Interval ms(%f, %f) avg=%f   Samples V (%f, %f) avg=%f Dips: %d  # Samples: %d \n", minInt, maxInt, averageInt, minV, maxV, averageVoltage, numDips, (*length) );
	long long tookTime = getTimeInMs() - startTime;
	if(tookTime < 1000000){
		printf("Took time: %d\n", (int)tookTime/1000);
		sleepForMs(1000 - tookTime/1000);
	}
}