//This module starts and stops sampling thread
#ifndef _SAMPLER_H_
#define _SAMPLER_H_


#define BUFFER_SIZE 1000

typedef struct {
    double sampleInV;
    double IntervalInMilliS;
} samplerDatapoint_t;

// Begin/end the background thread which samples light levels.
void Sampler_init(void);
void Sampler_stopSampling(void);
// Get a copy of the samples in the sample history, removing values
// from our history here.
// Returns a newly allocated array and sets `length` to be the
// number of elements in the returned array (output-only parameter).
// The calling code must call free() on the returned pointer.
// Note: function provides both data and size to ensure consistency.
samplerDatapoint_t* Sampler_extractAllValues(int *length);
// Returns how many valid samples are currently in the history.
int Sampler_getNumSamplesInHistory();
// Get the total number of light level samples taken so far.
long long Sampler_getNumSamplesTaken(void);
#endif