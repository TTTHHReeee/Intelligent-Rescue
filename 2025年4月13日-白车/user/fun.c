#include "MyHeader.h"
uint8_t FindFlag = 0; //0代表没有找到球 1代表找到球

uint8_t single_moveDistance = 0;
uint8_t moveDistance(float distance) {
		if(single_moveDistance == 0) {
				finishFlag = 0;
				CarMode = 2;
				Drive_Motor_To_Distance(distance);
				single_moveDistance = 1;
		}
		if(finishFlag == 2) {
				finishFlag = 0;
				single_moveDistance = 0;
				return 1;
		}
		return 0;
}
uint8_t single_turnAngle = 0;
uint8_t turnAngle(float angle) {
		if(single_turnAngle == 0) {
				finishFlag = 0;
				CarMode = 3;
				target_z = angle;
				single_turnAngle = 1;
		}
		if(finishFlag == 3) {
				finishFlag = 0;
				single_turnAngle = 0;
				return 1;
		}
		return 0;
}
void GetAngle(void) {
		if(Uart3Flag == 1) {
				Uart3Flag = 0;
				Uart3_Rx_Cnt = 0;
				yaw = arrayToFloat(RxBuffer3);
				memset(RxBuffer3,0x00,sizeof(RxBuffer3)); //清空数组
		}
}

uint8_t E0_state;
uint8_t E0_last_state;
uint8_t keyNum = 0;
void key_scan(void)
{
	 E0_state = HAL_GPIO_ReadPin (GPIOE,GPIO_PIN_0);
	 if(E0_state == 0 && E0_last_state == 1)
	 {
			keyNum = 1;
	 }
	 else {
			keyNum = 0;
	 }
	 
	 E0_last_state = E0_state ;
}
void Buzz(int Buzzms){
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
		HAL_Delay(Buzzms);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
}

