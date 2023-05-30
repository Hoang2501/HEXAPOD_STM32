#include "inverse_kinematic.h"

theta IK_LEG (pos_leg pos_leg_1)
{
	theta theta_conv;
	
	float LL = sqrtf(powf(pos_leg_1.x, 2) + powf(pos_leg_1.y, 2));
	float LFT = sqrtf(powf(LL - L1, 2) + powf(pos_leg_1.z, 2));
	
	float alpha_1 = acosf((powf(L2, 2) + powf(LFT, 2) - powf(L3, 2))/(2*L2*LFT));
	float alpha_2 = atan2f(LL-L1 ,pos_leg_1.z);
	
	theta_conv.theta_1 = 90 + atan2f(pos_leg_1.y, pos_leg_1.x)*180/PI;
	theta_conv.theta_2 = 180 - (alpha_1 + alpha_2)*180/PI;
	theta_conv.theta_3 = acosf((powf(L2, 2) + powf(L3, 2) - pow(LFT, 2))/(2*L2*L3))*180/PI;
	
	return theta_conv;
}

pos_leg BODY_TO_LEG(pos_leg a, float alpha, float beta, float gamma, float angle)
{
	pos_leg pos_leg_conv;
	pos_leg pos_leg_conv1;
	//angle = angle*PI/180;
	
	pos_leg_conv.x = cosf(alpha)*a.x - sinf(alpha)*a.y;
	pos_leg_conv.y = sinf(alpha)*a.x + cosf(alpha)*a.y;
	pos_leg_conv.z = a.z;
	
	pos_leg_conv1.x = cosf(angle)*pos_leg_conv.x - sinf(angle)*pos_leg_conv.y;
	pos_leg_conv1.y = sinf(angle)*pos_leg_conv.x + cosf(angle)*pos_leg_conv.y;
	pos_leg_conv1.z = pos_leg_conv.z;
	
	return pos_leg_conv1;
}