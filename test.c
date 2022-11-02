#include "utilities.h"
#include "photoRes.h"
#include "joystick.h"
#include "led.h"
#include "digits.h"
#include "sampler.h"
#include "analysis.h"

static bool isDoneRunning = false;

static pthread_t idJoystick;
//static pthread_mutex_t someMutex = PTHREAD_MUTEX_INITIALIZER;
static void *listenToJoystick(void *_)
{
	while (!isDoneRunning){
		sleepForMs(20);
		double minMax[4];
		int dips = copyInfo(minMax);
		char js = Joystick_position();
		if(js == 'C'){
			display_int(dips);
		}
		else if(js == 'U'){
			display_double(minMax[0]);
		}
		else if(js == 'D'){
			display_double(minMax[1]);
		}
		else if(js == 'R'){
			display_double(minMax[2]);
		}
		else if(js == 'L'){
			display_double(minMax[3]);
		}
	}
	return NULL;

}

void runApp()
{
	Sampler_init();
	sleepForMs(1000);
	pthread_create(&idJoystick, NULL, &listenToJoystick, NULL);
	while (true)
	{
		bool end = 0;
		start_analysis();
		for(int i=0; i<10; i++){
			if(readUser()){
				printf("Here");
				end = 1;
				break;
			}
			sleepForMs(100);
		}
		if(end){
			break;
		}
	}
	isDoneRunning = 1;
	pthread_join(idJoystick, NULL);
	Sampler_stopSampling();

}

int main()
{
	Digits_initialize();
	LED_init();
	clearAll();
	runCommand("config-pin p8.43 gpio");
	runApp();
	clearAll();

	return 0;
}
