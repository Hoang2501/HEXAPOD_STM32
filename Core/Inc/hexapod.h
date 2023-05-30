/*check name and define*/
#ifndef HEXAPOD_H
#define HEXAPOD_H

/*khai báo c*/
#ifdef __cplusplus
extern "C" {
#endif
/*start code*/
#include "math.h"
#include "inverse_kinematic.h"
#include "control_servo.h"
#include "PID.h"

#define TIME_PHASE_T 0.7
#define TIME_PHASE_R 1
#define TIME_PHASE_W 2.1

#define ID_LEG_1 0
#define ID_LEG_2 1
#define ID_LEG_3 2
#define ID_LEG_4 3
#define ID_LEG_5 4
#define ID_LEG_6 5

extern theta theta_leg_1;
extern pos_leg pos_leg_1;
extern theta theta_leg_2;
extern pos_leg pos_leg_2;
extern theta theta_leg_3;
extern pos_leg pos_leg_3;
extern theta theta_leg_4;
extern pos_leg pos_leg_4;
extern theta theta_leg_5;
extern pos_leg pos_leg_5;
extern theta theta_leg_6;
extern pos_leg pos_leg_6;
	
extern theta theta_leg_1_last;
extern theta theta_leg_2_last;
extern theta theta_leg_3_last;
extern theta theta_leg_4_last;
extern theta theta_leg_5_last;
extern theta theta_leg_6_last;

extern float pos_leg_defaut[6][3];

extern pos_leg UPDATE_POS_LEG(float vx, float vy, float up_z, int LEG_ID, float TIME_PHASE);
extern pos_leg POS_DEFAUT(int LEG_ID);
extern void TRIPPLE_GAIT(float vx, float vy, float up_z, float alpha);
extern void WAVE_GAIT(float vx, float vy, float up_z, float alpha);
extern void RIPPLE_GAIT(float vx, float vy, float up_z, float alpha);
extern void RUN_HEXAPOD(float vx, float vy, float up_z, float alpha, int8_t gait_type);
/*end code*/
#ifdef __cplusplus
}
#endif

#endif