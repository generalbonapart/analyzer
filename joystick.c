#include "joystick.h"
#include "utilities.h"

static int digital_position(double* t){

    if((*t) > 1.35){ return 1;}
    else if((*t) < 0.45){ return -1;}
    else{ return 0;}
}

static void Joystick_readXY(double* x, double* y){
    
	int reading_x = getVoltageReading(2);
	double voltage_x = ((double)reading_x / A2D_MAX_READING) * A2D_VOLTAGE_REF_V;
    int reading_y = getVoltageReading(3);
	double voltage_y = ((double)reading_y / A2D_MAX_READING) * A2D_VOLTAGE_REF_V;
	
    *x = voltage_x;
    *y = voltage_y;
}

char Joystick_position(){

    double* x = malloc(sizeof(double));
	double* y = malloc(sizeof(double));

    
	Joystick_readXY(x, y);
    
    int x_dig = digital_position(x);
    int y_dig = digital_position(y);
    
    if(x_dig==0){ 
        if(y_dig == 0){
            return 'C';
        }
        if(y_dig == 1){
            return 'L';
        }
        else {
            return 'R';
        }
    }
    if(x_dig == 1){
        if((*y)>(*x)){
            return 'L';
        }
        else if((*y)<(1.8 - (*x))){
            return 'R';
        }
        else {
            return 'D';
        }
    }
    else{
        if((*y)<(*x)){
            return 'R';
        }
        else if((*y)>(1.8 - (*x))){
            return 'L';
        }
        else {
            return 'U';
        }
    }
    free(x);
    free(y);
}