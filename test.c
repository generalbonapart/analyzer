#include "utilities.h"
#include "photoRes.h"
#include "joystick.h"
#include "led.h"
#include "digits.h"
#include "sampler.h"
#include "analysis.h"


int main()
{
	
	printf("init led:\n");
	LED_init();
	clearAll();
	Digits_initialize();

	Sampler_init();
	sleepForMs(1000);
	for(int i=0; i<20; i++)
	{
		start_analysis();
	}
	
	while(false){

		//char c = Joystick_position();
		//printf("x= %5.2fV \t y= %5.2fV \n", *x, *y);
		//printf("Position: %c\n", c);
		double res = PhotoRes_resistance();
		printf("Resistance: %f\n", res);
		sleepForMs(100);
	}
	return 0;
}
