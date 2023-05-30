/*check name and define*/
#ifndef PID_H
#define PID_H

/*khai báo c*/
#ifdef __cplusplus
extern "C" {
#endif
/*start code*/
#include "math.h"
#include "main.h"
#include "hexapod.h"

extern float pid(float set_angle, float angle, uint16_t sampletimePID);

/*end code*/
#ifdef __cplusplus
}
#endif

#endif