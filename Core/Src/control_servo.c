/*include thu vien control_servo*/
#include "control_servo.h"


float convert_deg_to_plu (float degree) {
	float pulse_len;
	pulse_len = (PULSE_LEN_MAX - PULSE_LEN_MIN)*degree/180 +PULSE_LEN_MIN;
	return pulse_len/20;
}

void LEG_1(float degree_1,float degree_2,float degree_3) {
	float duty_cycle_1, duty_cycle_2, duty_cycle_3;
	
	duty_cycle_1 = convert_deg_to_plu(degree_1);
	duty_cycle_2 = convert_deg_to_plu(degree_2);
	duty_cycle_3 = convert_deg_to_plu(degree_3);
	
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, duty_cycle_1);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, duty_cycle_2);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, duty_cycle_3);
}

void LEG_2(float degree_1,float degree_2,float degree_3) {
	float duty_cycle_1, duty_cycle_2, duty_cycle_3;
	
	duty_cycle_1 = convert_deg_to_plu(degree_1);
	duty_cycle_2 = convert_deg_to_plu(degree_2);
	duty_cycle_3 = convert_deg_to_plu(degree_3);
	
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, duty_cycle_1);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, duty_cycle_2);
	__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, duty_cycle_3);
}

void LEG_3(float degree_1,float degree_2,float degree_3) {
	float duty_cycle_1, duty_cycle_2, duty_cycle_3;
	
	duty_cycle_1 = convert_deg_to_plu(degree_1);
	duty_cycle_2 = convert_deg_to_plu(degree_2);
	duty_cycle_3 = convert_deg_to_plu(degree_3);
	
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, duty_cycle_1);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, duty_cycle_2);
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, duty_cycle_3);
}

void LEG_4(float degree_1,float degree_2,float degree_3) {
	float duty_cycle_1, duty_cycle_2, duty_cycle_3;
	
	duty_cycle_1 = convert_deg_to_plu(degree_1);
	duty_cycle_2 = convert_deg_to_plu(degree_2);
	duty_cycle_3 = convert_deg_to_plu(degree_3);
	
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, duty_cycle_1);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, duty_cycle_2);
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, duty_cycle_3);
}

void LEG_5(float degree_1,float degree_2,float degree_3) {
	float duty_cycle_1, duty_cycle_2, duty_cycle_3;
	
	duty_cycle_1 = convert_deg_to_plu(degree_1);
	duty_cycle_2 = convert_deg_to_plu(degree_2);
	duty_cycle_3 = convert_deg_to_plu(degree_3);
	
	__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_1, duty_cycle_1);
	__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_2, duty_cycle_2);
	__HAL_TIM_SetCompare(&htim5, TIM_CHANNEL_3, duty_cycle_3);
}

void LEG_6(float degree_1,float degree_2,float degree_3) {
	float duty_cycle_1, duty_cycle_2, duty_cycle_3;
	
	duty_cycle_1 = convert_deg_to_plu(degree_1);
	duty_cycle_2 = convert_deg_to_plu(degree_2);
	duty_cycle_3 = convert_deg_to_plu(degree_3);
	
	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_1, duty_cycle_1);
	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_2, duty_cycle_2);
	__HAL_TIM_SetCompare(&htim8, TIM_CHANNEL_3, duty_cycle_3);
}