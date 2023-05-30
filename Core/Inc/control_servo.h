/*check name header control servo and define*/
#ifndef CONTROL_SERVO_H
#define CONTROL_SERVO_H

/*khai báo c*/
#ifdef __cplusplus
extern "C" {
#endif
/*start code*/
/*khai bao thu vien*/
#include "stm32f4xx_hal.h"
#include "tim.h"

/*khai bao pulse lenght max, min ung voi goc 180 va 0 */
#ifndef PULSE_LEN_MAX
#define PULSE_LEN_MAX 2500
#endif

#ifndef PULSE_LEN_MIN
#define PULSE_LEN_MIN 500
#endif

extern float convert_deg_to_plu (float degree);
extern void LEG_1(float degree_1,float degree_2,float degree_3);
extern void LEG_2(float degree_1,float degree_2,float degree_3);
extern void LEG_3(float degree_1,float degree_2,float degree_3);
extern void LEG_4(float degree_1,float degree_2,float degree_3);
extern void LEG_5(float degree_1,float degree_2,float degree_3);
extern void LEG_6(float degree_1,float degree_2,float degree_3);
/*end code*/
#ifdef __cplusplus
}
#endif

/*end control servo */
#endif