#ifndef __Serial_H
#define __Serial_H

#define RXBUFFERSIZE  1024     //最大接收字节数
#define MAX_ITEMS 4   // 最多的单词数量
#define MAX_LENGTH 10  // 单个字符串的最大长度

#include <stdbool.h>
#include "gpio.h"

extern char RxBuffer1[RXBUFFERSIZE];   //接收数据
extern char RxBuffer2[RXBUFFERSIZE];   //接收数据
extern char RxBuffer3[RXBUFFERSIZE];   //接收数据
extern uint8_t aRxBuffer1;			//接收中断缓冲
extern uint8_t aRxBuffer2;
extern uint8_t aRxBuffer3;
extern int Uart1_Rx_Cnt;		//接收缓冲计数
extern int Uart2_Rx_Cnt;
extern int Uart3_Rx_Cnt;
extern uint8_t UART;
extern uint8_t Uart1Flag;
extern uint8_t Uart2Flag;
extern uint8_t Uart3Flag;
extern uint8_t powerFlag;

void Serial_SendString(char *string);
void Serial2_SendString(char *string);
void split_into_arrays(const char *input, char output[][MAX_LENGTH], int *count);
int arrayToInt(char *arr);
float arrayToFloat(char *arr);
#endif

