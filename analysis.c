#include "analysis.h"
#include "sampler.h"
#include "utilities.h"
#include "led.h"


static double minMax[4]; 
//= malloc(sizeof(double)*4);
static int dipStore[1];


static double averageVoltage = 0;
static double minV, maxV;
static double minInt, maxInt, averageInt;
static bool firstSample = 0;

static bool currentDip = 0;
static int numDips = 0;

static void store_vars()
{
	minMax[0] = maxV;
	minMax[1] = minV;
	minMax[2] = maxInt;
	minMax[3] = minInt;
	dipStore[0] = numDips;
}

int copyInfo(double* target)
{
	for(int i=0; i<4;i++){
		target[i] = minMax[i];
	}
	return (*dipStore);
}

static void handleDips(double sample)
{
    if(currentDip == 0)
    {
        if(sample < averageVoltage - (THRESHOLD + HYSTERESIS)){
            currentDip = 1;
            numDips++;
        }
    }
    else
    {
        if(sample > averageVoltage - (THRESHOLD - HYSTERESIS)){
            currentDip = 0;
        }
    }
}


static void analysis(samplerDatapoint_t* Buffer, int length){
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
		averageVoltage = WEIGHT*averageVoltage + 0.001*sample.sampleInV;
	}

	averageInt = totalTime/length;

}

void start_analysis(){
	//long long startTime = getTimeInMs();
	samplerDatapoint_t* Buffer;
	int* length = malloc(4);
	Buffer = Sampler_extractAllValues(length);
	//int total = Sampler_getNumSamplesTaken();
	if(firstSample == 0){
		averageVoltage = Buffer[0].sampleInV;
		firstSample = 1;
	}
	int size = (*length);
	free(length);
	analysis(Buffer, size);
	store_vars();
	printf("Interval ms(%.3f, %.3f) avg=%.3f   Samples V (%.3f, %.3f) avg=%.3f	Dips: %d  # Samples: %d \n", minInt, maxInt, averageInt, minV, maxV, averageVoltage, numDips, size );
	free(Buffer);
	//long long tookTime = getTimeInMs() - startTime;
	//printf("Took time: %d\n", (int)tookTime/1000);	
}

