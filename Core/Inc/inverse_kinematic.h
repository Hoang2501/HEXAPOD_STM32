/*check name and define*/
#ifndef INVERSE_KINEMATIC_H
#define INVERSE_KINEMATIC_H

/*khai báo c*/
#ifdef __cplusplus
extern "C" {
#endif
/*start code*/
#include "math.h"

#ifndef PI
#define PI           3.14159265358979323846  /* pi */
#endif

#define L1 5.9
#define L2 7.6
#define L3 15

typedef struct theta {
	float theta_1, theta_2, theta_3;
} theta;

typedef struct pos_leg {
	float x, y, z;
} pos_leg;

extern theta IK_LEG (pos_leg pos_leg_1);
extern pos_leg BODY_TO_LEG(pos_leg a, float alpha, float beta, float gamma, float angle);

/*end code*/
#ifdef __cplusplus
}
#endif

#endif