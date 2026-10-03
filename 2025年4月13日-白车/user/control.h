#ifndef __CONTROL_H
#define __CONTROL_H
#include "gpio.h"
#include <stdbool.h>
#define  frame_pos_speed  0.4  //定距离的速度
#define  ball_pos_speed  0.2

#define frame_adc_time 400  //框ADC触发以后旋转的时间

//#define ball_target_x 180
#define ball_target_x 145
#define frame_target_x 505

#define ball_en_err_y 40
#define frame_en_err_y 20

#define ball_en_err_x 20
#define frame_en_err_x 20

extern uint16_t WatingTask ;
extern uint16_t WatingCount;
extern uint8_t  WatingFlag;
extern bool WatingStart;
extern int enMoveErrX ;
extern int enMoveErrY;
extern float target_cord_x;  //找到球时的X
extern float target_cord_y;  //找到球时的Y
extern uint8_t CarMode;  //1找球模式 2移动指定距离 3旋转指定角度
extern uint8_t finishFlag;
extern float target_z;
extern float roll, yaw, pitch, gyro_yaw;

#endif
