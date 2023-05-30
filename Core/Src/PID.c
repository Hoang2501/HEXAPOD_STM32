#include "PID.h"

float kp = 1, ki = 0.5, kd =12; 
float error = 0, prev_error = 0, integral = 0;
float output, last_output  = 0;

float pid(float set_angle, float angle, uint16_t sampletimePID)
{
		set_angle = set_angle/100;
	  angle = 2*PI*angle/3600;
    error = set_angle - angle;

    integral = integral + error;

    if (integral > 100) {
        integral = 100;
    } else if (integral < -100) {
        integral = -100;
    }

    output = kp * error + ki * integral*sampletimePID/1000 + kd * (error - prev_error)/sampletimePID/1000;

    if (output > 100) {
        output = 100;
    } else if (output < -100) {
        output = -100;
    }

    prev_error = error;
    last_output = output;

    return output;
}