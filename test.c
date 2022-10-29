#include "utilities.h"
#include "photoRes.h"
#include "joystick.h"
#include "led.h"
#include "digits.h"

int main()
{
	printf("init led:\n");
	LED_init();
	clearAll();
	Digits_initialize();

	for(int i=0; i<20; i++)
	{
		display_int(i);
		sleepForMs(500);
	}

	display_double(9.9);
	getchar();
	display_double(100);
	getchar();
	display_double(9.76);
	getchar();
	for(int i=20; i<30; i++)
	{
		display_int(i);
		sleepForMs(500);
	}
	display_double(0.9);
	getchar();
	display_double(7.9);
	getchar();
	for(int i=30; i<40; i++)
	{
		display_int(i);
		sleepForMs(500);
	}
	display_double(0);
	getchar();
	
	
	
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
