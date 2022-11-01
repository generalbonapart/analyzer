#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "sampler.h"
#include "utilities.h"

static int totalSamples = 0;
static int writeIdx = 0;
static bool isDoneRunning = false;


static samplerDatapoint_t Buffer[BUFFER_SIZE];
static pthread_t idWrite;
static pthread_mutex_t bufferMutex = PTHREAD_MUTEX_INITIALIZER;



static void *fillBuffer(void *_)
{
    long long refTime = getTimeInMs();
    while (!isDoneRunning){
        int reading = getVoltageReading(1);
	    double voltage = ((double)reading / A2D_MAX_READING) * A2D_VOLTAGE_REF_V;
       
        pthread_mutex_lock(&bufferMutex);
        {
            Buffer[writeIdx].sampleInV = voltage;
            long long newTime = getTimeInMs();
            Buffer[writeIdx].IntervalInMilliS = (double)(newTime - refTime)/1000;
            refTime = newTime;
            writeIdx = (writeIdx + 1) % BUFFER_SIZE;           
        }
        pthread_mutex_unlock(&bufferMutex);
        totalSamples++;
        sleepForMs(1);

    }
    printf("Fill thread exiting...\n");
    return NULL;
}

void Sampler_init(void)
{
    pthread_create(&idWrite, NULL, &fillBuffer, NULL);
}

// Cause the module to stop, and then wait until thread is done.
void Sampler_stopSampling(void)
{
    isDoneRunning = true;
    pthread_join(idWrite, NULL);
}

samplerDatapoint_t* Sampler_extractAllValues(int *length)
{
    samplerDatapoint_t* targetBuff = malloc(sizeof(samplerDatapoint_t)*1000);
    int targBuffIdx = 0;
    pthread_mutex_lock(&bufferMutex);
    {
        while ((targBuffIdx + 1) % BUFFER_SIZE != writeIdx)
        {
            targetBuff[targBuffIdx] = Buffer[targBuffIdx];

            targBuffIdx++;
            if (targBuffIdx >= BUFFER_SIZE){
                break;
            }
        }
        writeIdx = 0;
    }
    pthread_mutex_unlock(&bufferMutex);

    // Return number of values copied
    *length = targBuffIdx;
    return targetBuff;
}

int Sampler_getNumSamplesInHistory()
{
    return writeIdx;
}
// Get the total number of light level samples taken so far.
long long Sampler_getNumSamplesTaken(void)
{
    return totalSamples;
}