#ifndef __TASK_H
#define __TASK_H
#include "gpio.h"

#define MAX_ITEMS 4   // 最多的单词数量
#define MAX_LENGTH 10  // 单个字符串的最大长度
extern char arrays[MAX_ITEMS][MAX_LENGTH]; 
extern float pos_speed;
void open(int ms);
void close(void);
void TS(void);
void HT(void);
void CatchBall(int ms);
void ADC_OLED(void);
uint8_t task_WinBall(uint8_t task_ball);
uint8_t ADC_get(void);

#endif

