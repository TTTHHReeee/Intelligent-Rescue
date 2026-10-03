#ifndef __FUN_H
#define __FUN_H
#include "gpio.h"

extern uint8_t FindFlag;
extern uint8_t keyNum;
uint8_t moveDistance(float distance);
uint8_t turnAngle(float angle);
void GetAngle(void);
void key_scan(void);
void Buzz(int Buzzms);
#endif
