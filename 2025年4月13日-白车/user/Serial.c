#include "MyHeader.h"
char RxBuffer1[RXBUFFERSIZE];   //接收数据
char RxBuffer2[RXBUFFERSIZE];   //接收数据
char RxBuffer3[RXBUFFERSIZE];   //接收数据
uint8_t aRxBuffer1;			//接收中断缓冲
uint8_t aRxBuffer2;			//接收中断缓冲
uint8_t aRxBuffer3;			//接收中断缓冲
int Uart1_Rx_Cnt = 0;		//接收缓冲计数
int Uart2_Rx_Cnt = 0;
int Uart3_Rx_Cnt = 0;
uint8_t Uart1Flag = 0;
uint8_t Uart2Flag = 0;
uint8_t Uart3Flag = 0;
uint8_t UART = 1;  //默认串口1

void UART_Transmit(int ch){
	if (UART == 1){
			HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
	}
	else if(UART == 2){
			HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xffff);
	}
	else if(UART == 3){
			HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xffff);
	}
}

void Serial_SendString(char *string){
		UART = 1;
		printf("%s",string);
}
void Serial2_SendString(char *string){
		UART = 2;
		printf("%s",string);
}
//printf重定义
int fputc(int ch, FILE *f){
	UART_Transmit(ch);
  return ch;
}
/**************************************************************************
Function: Refresh the OLED screen
Input   : none
Output  : none
函数功能：串口解析函数
入口参数：无
返回  值：无
**************************************************************************/
void split_into_arrays(const char *input, char output[][MAX_LENGTH], int *count) {
    char temp_input[MAX_LENGTH * MAX_ITEMS];
    strncpy(temp_input, input, sizeof(temp_input) - 1); // 防止修改原始输入
    temp_input[sizeof(temp_input) - 1] = '\0';

    char *token = strtok(temp_input, " ");
    while (token != NULL) {
        strncpy(output[*count], token, MAX_LENGTH - 1);
        output[*count][MAX_LENGTH - 1] = '\0'; // 确保字符串以 '\0' 结束
        (*count)++;
        token = strtok(NULL, " "); // 获取下一个子字符串
    }
}
int arrayToInt(char *arr) {
    int result = 0;
    int sign = 1;  // 默认正数

    // 判断符号位
    if (arr[0] == '-') {
        sign = -1;
        arr++;  // 跳过负号
    }

    // 遍历字符数组，将字符转换为数字
    while (*arr != '\0') {
        result = result * 10 + (*arr - '0');  // 将字符转为整数并累加
        arr++;  // 移动到下一个字符
    }
    return result * sign;
}
float arrayToFloat(char *arr) {
    unsigned integer_part = 0;
    float fraction = 0.0f;
    int sign = 1;
    int is_decimal = 0;
    float weight = 0.1f;

    // 处理符号位
    if (*arr == '-' || *arr == '+') {
        sign = (*arr == '-') ? -1 : 1;
        arr++;
    }

    while (*arr != '\0') {
        if (*arr == '.') {
            is_decimal = 1;
            arr++;
            continue;
        }

        int digit = *arr - '0'; 

        if (!is_decimal) {
            integer_part = integer_part * 10 + digit;
        } else {
            fraction += digit * weight;
            weight *= 0.1f;
        }

        arr++;
    }

    return sign * ((float)integer_part + fraction);
}
/*
		串口中断回调函数
		串口1
		串口2和openMv通讯
*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
   */
	if(huart == &huart1){
			static uint8_t RxState = 0; 
			if(RxState == 0){
					if(aRxBuffer1 == '+'){
							RxState = 1;
					}
			}
			else if (RxState == 1){
					if(aRxBuffer1 == 0x0D){
							RxState = 2;
					}
					else{
						RxBuffer1[Uart1_Rx_Cnt++] = aRxBuffer1;   //接收数据转存
					}
			}
			else if(RxState == 2){
					if(aRxBuffer1 == 0x0A){
							RxState = 0;
							RxBuffer1[Uart1_Rx_Cnt++] = '\0';
					}
					else{
							RxState = 0;
							Uart1_Rx_Cnt = 0;   //不符合要求 清空 重新读取
					}
			}
			HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer1, 1);   //再开启接收中断
	}
		else if(huart == &huart2){
				if(Uart2Flag == 0){
						static uint8_t RxState2 = 0;    
						if(RxState2 == 0 && Uart2Flag == 0){
								if(aRxBuffer2 == 'W'){
										RxState2 = 1;
								}
						}
						else if(RxState2 == 1){
								if(aRxBuffer2 == 'L'){
										RxState2 = 0;
										RxBuffer2[Uart2_Rx_Cnt++] = '\0';
										Uart2Flag = 1;
								}
								else{
										RxBuffer2[Uart2_Rx_Cnt++] = aRxBuffer2;   //接收数据转存	
								}
						}
				}		
				HAL_UART_Receive_IT(&huart2, (uint8_t *)&aRxBuffer2, 1);   //再开启接收中断
		}
		else if(huart == &huart3 && Uart3Flag == 0){
				RxBuffer3[Uart3_Rx_Cnt++] = aRxBuffer3;   //接收数据转存
				if((RxBuffer3[Uart3_Rx_Cnt-1] == 0x0A)&&(RxBuffer3[Uart3_Rx_Cnt-2] == 0x0D)) //判断结束位
				{
						RxBuffer3[Uart3_Rx_Cnt-2] = '\0';
						Uart3Flag = 1;
				}
				HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer3, 1);   //再开启接收中断
		}

}

